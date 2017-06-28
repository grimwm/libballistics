/**
 * Copyright 2017 William Grim
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ballistics/ballistics.h"

#include <stdlib.h>
#include <math.h>

/**
 * A description of a solution to point-blank-range calculations.
 */
struct PBR {
  int near_zero_yards; // nearest scope/projectile intersection
  int far_zero_yards;  // furthest scope/projectile intersection

  int min_PBR_yards;   // nearest target can be for a vitals hit when aiming at center of vitals
  int max_PBR_yards;   // furthest target can be for a vitals hit when aiming at center of vitals

  // Sight-in at 100 yards, in 100ths of an inch.  Positive is above center; negative is below.
  int sight_in_at_100yards;
};

int PBR_get_near_zero_yards(struct PBR* pbr) {
  return pbr->near_zero_yards;
}

int PBR_get_far_zero_yards(struct PBR* pbr) {
  return pbr->far_zero_yards;
}

int PBR_get_min_PBR_yards(struct PBR* pbr) {
  return pbr->min_PBR_yards;
}

int PBR_get_max_PBR_yards(struct PBR* pbr) {
  return pbr->max_PBR_yards;
}

int PBR_get_sight_in_at_100yards(struct PBR* pbr) {
  return pbr->sight_in_at_100yards;
}

void PBR_free(struct PBR* pbr) {
  free(pbr);
}

int PBR_solve(struct PBR** pbr, DragFunction drag_function, double drag_coefficient, double vi,
              double sight_height, double vital_size) {

  double t=0;
  double dt=0.5/vi;
  double v=0;
  double vx=0, vx1=0, vy=0, vy1=0;
  double dv=0, dvx=0, dvy=0;
  double x=0, y=0;
  double ShootingAngle=0;
  double ZAngle=0;
  double Step=10;

  int quit=0;

  double zero=-1;
  double farzero=0;

  int vertex_keep=0;
  double y_vertex=0;
  double x_vertex=0;

  double min_PBR_range=0;
  int min_PBR_keep=0;

  double max_PBR_range=0;
  int max_PBR_keep=0;

  int tin100=0;

  double Gy=GRAVITY*cos(deg_to_rad((ShootingAngle + ZAngle)));
  double Gx=GRAVITY*sin(deg_to_rad((ShootingAngle + ZAngle)));

  int status = 0;

  while (quit==0){

    Gy=GRAVITY*cos(deg_to_rad((ShootingAngle + ZAngle)));
    Gx=GRAVITY*sin(deg_to_rad((ShootingAngle + ZAngle)));

    vx=vi*cos(deg_to_rad(ZAngle));
    vy=vi*sin(deg_to_rad(ZAngle));

    y=-sight_height/12;

    x=0;y=-sight_height/12;

    int keep=0;
    int keep2=0;
    int tinkeep=0;
    min_PBR_keep=0;
    max_PBR_keep=0;
    vertex_keep=0;

    tin100=0;
    tinkeep=0;

    int n=0;
    for (t=0;;t=t+dt) {

      status = 0;

      vx1=vx, vy1=vy;
      v=pow(pow(vx,2)+pow(vy,2),0.5);
      dt=0.5/v;

      // Compute acceleration using the drag function retardation
      dv = retard(drag_function,drag_coefficient,v);
      dvx = -(vx/v)*dv;
      dvy = -(vy/v)*dv;

      // Compute velocity, including the resolved gravity vectors.
      vx=vx + dt*dvx + dt*Gx;
      vy=vy + dt*dvy + dt*Gy;

      // Compute position based on average velocity.
      x=x+dt*(vx+vx1)/2;
      y=y+dt*(vy+vy1)/2;

      if (y>0 && keep==0 && vy>=0) {
        zero=x;
        keep=1;
      }

      if (y<0 && keep2==0 && vy<=0){
        farzero=x;
        keep2=1;
      }

      if ((12*y)>-(vital_size/2) && min_PBR_keep==0){
        min_PBR_range=x;
        min_PBR_keep=1;
      }

      if ((12*y)<-(vital_size/2) && min_PBR_keep==1 && max_PBR_keep==0){
        max_PBR_range=x;
        max_PBR_keep=1;
      }

      if (x>=300 && tinkeep==0){
        tin100=(int)((float)100*(float)y*(float)12);
        tinkeep=1;
      }


      if (fabs(vy)>fabs(3*vx)) {
        status = PBR_E_TOO_FAST_VY;
        break;
      }
      if (n>=BALLISTICS_COMPUTATION_MAX_YARDS+1) {
        status = PBR_E_OUT_OF_RANGE;
        break;
      }

      // The PBR will be maximum at the point where the vertex is 1/2 vital zone size.
      if (vy<0 && vertex_keep==0){
        y_vertex=y;
        x_vertex=x;
        vertex_keep=1;
      }

      if (keep==1 && keep2==1 && min_PBR_keep==1 && max_PBR_keep==1 && vertex_keep==1 && tinkeep==1) {
        break;
      }
    }

    if ((y_vertex*12)>(vital_size/2)){
      if (Step>0) Step=-Step/2; // Vertex too high.  Go downwards.
    }

    else if ((y_vertex*12)<=(vital_size/2)){ // Vertex too low.  Go upwards.
      if (Step<0) Step =-Step/2;
    }

    ZAngle+=Step;

    if (fabs(Step)<(0.01/60)) quit=1;
  }

  if (status) {
    return status;
  }

  *pbr = malloc(sizeof(struct PBR));
  (*pbr)->near_zero_yards = (int)(zero/3);
  (*pbr)->far_zero_yards = (int)(farzero/3);
  (*pbr)->min_PBR_yards = (int)(min_PBR_range/3);
  (*pbr)->max_PBR_yards = (int)(max_PBR_range/3);
  (*pbr)->sight_in_at_100yards = tin100;

  return 0;
}
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
 * A ballistics solution for a projectile at a certain yardage.
 */
struct Point {
  double range_yards;
  double path_inches;
  double moa_correction;
  double seconds;
  double windage_inches;
  double windage_moa;
  double velocity; // total velocity -> vector product of vx and vy
  double vx; // velocity of projectile in the bore direction
  double vy; // velocity of projectile perpendicular to the bore direction
};

struct Ballistics {
  struct Point *yardages;
  int max_yardage;
};

struct Ballistics* Ballistics_alloc() {
  struct Ballistics* sln = malloc(sizeof(struct Ballistics));
  sln->yardages = malloc(sizeof(struct Point) * BALLISTICS_COMPUTATION_MAX_YARDS);
  return sln;
}

void Ballistics_free(struct Ballistics* ballistics) {
  free(ballistics->yardages);
  free(ballistics);
}

double Ballistics_get_range(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].range_yards;
  }
  else return 0;
}

double Ballistics_get_path(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].path_inches;
  }
  else return 0;
}

double Ballistics_get_moa(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].moa_correction;
  }
  else return 0;
}


double Ballistics_get_time(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].seconds;
  }
  else return 0;
}

double Ballistics_get_windage(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].windage_inches;
  }
  else return 0;
}

double Ballistics_get_windage_moa(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].windage_moa;
  }
  else return 0;
}

double Ballistics_get_velocity(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].velocity;
  }
  else return 0;
}

double Ballistics_get_vx(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].vx;
  }
  else return 0;
}

double Ballistics_get_vy(struct Ballistics* ballistics, int yardage) {
  if (yardage < ballistics->max_yardage) {
    return ballistics->yardages[yardage].vy;
  }
  else return 0;
}

int Ballistics_solve(struct Ballistics** ballistics, DragFunction drag_function, double drag_coefficient, double vi,
                     double sight_height, double shooting_angle, double zero_angle, double wind_speed, double wind_angle) {

	double t=0;
	double dt=0.5/vi;
	double v=0;
	double vx=0, vx1=0, vy=0, vy1=0;
	double dv=0, dvx=0, dvy=0;
	double x=0, y=0;
	
	double hwind = headwind(wind_speed, wind_angle);
	double cwind = crosswind(wind_speed, wind_angle);
	
	double Gy=GRAVITY*cos(deg_to_rad((shooting_angle + zero_angle)));
	double Gx=GRAVITY*sin(deg_to_rad((shooting_angle + zero_angle)));

  *ballistics = Ballistics_alloc();

	vx=vi*cos(deg_to_rad(zero_angle));
	vy=vi*sin(deg_to_rad(zero_angle));

	y=-sight_height/12;

	int n=0;
	for (t=0;;t=t+dt) {

		vx1=vx, vy1=vy;	
		v=pow(pow(vx,2)+pow(vy,2),0.5);
		dt=0.5/v;
	
		// Compute acceleration using the drag function retardation	
		dv = retard(drag_function,drag_coefficient,v+hwind);
		dvx = -(vx/v)*dv;
		dvy = -(vy/v)*dv;

		// Compute velocity, including the resolved gravity vectors.	
		vx=vx + dt*dvx + dt*Gx;
		vy=vy + dt*dvy + dt*Gy;



		if (x/3>=n) {
      struct Point* s = &(*ballistics)->yardages[n];
      s->range_yards = x/3;
      s->path_inches = y*12;
      s->moa_correction = -rad_to_moa(atan(y / x));
      s->seconds = t+dt;
      s->windage_inches = windage(cwind, vi, x, t + dt);
      s->windage_moa = rad_to_moa(atan((s->windage_inches/12) / x));
      s->velocity = v;
      s->vx = vx;
      s->vy = vy;
			n++;
		}	
		
		// Compute position based on average velocity.
		x=x+dt*(vx+vx1)/2;
		y=y+dt*(vy+vy1)/2;
		
		if (fabs(vy)>fabs(3*vx)) break;
		if (n>=BALLISTICS_COMPUTATION_MAX_YARDS) break;
	}

  (*ballistics)->max_yardage = n;
	return n;
}
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

// Used to solve ballistic problems
#include "ballistics.h"

/**
 * A ballistics solution for a projectile at a certain yardage.
 */
struct Ballistics {
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

struct BallisticsSolutions {
  struct Ballistics *yardages;
  int max_yardage;
};

struct BallisticsSolutions* solution_alloc() {
  struct BallisticsSolutions* sln = malloc(sizeof(struct BallisticsSolutions));
  sln->yardages = malloc(sizeof(struct Ballistics) * BALLISTICS_COMPUTATION_MAX_YARDS);
  return sln;
}

void solution_free(struct BallisticsSolutions* solution) {
  free(solution->yardages);
  free(solution);
}

double solution_get_range(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].range_yards;
  }
  else return 0;
}

double solution_get_path(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].path_inches;
  }
  else return 0;
}

double solution_get_moa(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].moa_correction;
  }
  else return 0;
}


double solution_get_time(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].seconds;
  }
  else return 0;
}

double solution_get_windage(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].windage_inches;
  }
  else return 0;
}

double solution_get_windage_moa(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].windage_moa;
  }
  else return 0;
}

double solution_get_velocity(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].velocity;
  }
  else return 0;
}

double solution_get_vx(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].vx;
  }
  else return 0;
}

double solution_get_vy(struct BallisticsSolutions* solution, int yardage) {
  if (yardage < solution->max_yardage) {
    return solution->yardages[yardage].vy;
  }
  else return 0;
}

int solve(struct BallisticsSolutions** solution, DragFunction drag_function, double drag_coefficient, double vi,
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

  *solution = solution_alloc();

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
      struct Ballistics* s = &(*solution)->yardages[n];
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

  (*solution)->max_yardage = n;
	return n;
}

/**
 * A description of a solution to point-blank-range calculations.
 */
struct PBRSolution {
  int near_zero_yards; // nearest scope/projectile intersection
  int far_zero_yards;  // furthest scope/projectile intersection

  int min_pbr_yards;   // nearest target can be for a vitals hit when aiming at center of vitals
  int max_pbr_yards;   // furthest target can be for a vitals hit when aiming at center of vitals

  // Sight-in at 100 yards, in 100ths of an inch.  Positive is above center; negative is below.
  int sight_in_at_100yards;
};

int pbr_get_near_zero_yards(struct PBRSolution* solution) {
  return solution->near_zero_yards;
}

int pbr_get_far_zero_yards(struct PBRSolution* solution) {
  return solution->far_zero_yards;
}

int pbr_get_min_pbr_yards(struct PBRSolution* solution) {
  return solution->min_pbr_yards;
}

int pbr_get_max_pbr_yards(struct PBRSolution* solution) {
  return solution->max_pbr_yards;
}

int pbr_sight_in_at_100yards(struct PBRSolution* solution) {
  return solution->sight_in_at_100yards;
}

int pbr(struct PBRSolution* solution, DragFunction drag_function, double drag_coefficient, double vi, double sight_height,
        double vital_size) {

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

	double min_pbr_range=0;
	int min_pbr_keep=0;

	double max_pbr_range=0;
	int max_pbr_keep=0;

	int tin100=0;

	double Gy=GRAVITY*cos(deg_to_rad((ShootingAngle + ZAngle)));
	double Gx=GRAVITY*sin(deg_to_rad((ShootingAngle + ZAngle)));

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
		min_pbr_keep=0;
		max_pbr_keep=0;
		vertex_keep=0;

		tin100=0;
		tinkeep=0;

		int n=0;
		for (t=0;;t=t+dt){

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

			if ((12*y)>-(vital_size/2) && min_pbr_keep==0){
				min_pbr_range=x;
				min_pbr_keep=1;
			}

			if ((12*y)<-(vital_size/2) && min_pbr_keep==1 && max_pbr_keep==0){
				max_pbr_range=x;
				max_pbr_keep=1;
			}

			if (x>=300 && tinkeep==0){
				tin100=(int)((float)100*(float)y*(float)12);
				tinkeep=1;
			}


			if (fabs(vy)>fabs(3*vx) || n>=BALLISTICS_COMPUTATION_MAX_YARDS+1) {
        return -1;
      }

			// The PBR will be maximum at the point where the vertex is 1/2 vital zone size.
			if (vy<0 && vertex_keep==0){
				y_vertex=y;
				x_vertex=x;
				vertex_keep=1;
			}

			if (keep==1 && keep2==1 && min_pbr_keep==1 && max_pbr_keep==1 && vertex_keep==1 && tinkeep==1) {
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

  solution->near_zero_yards = (int)(zero/3);
	solution->far_zero_yards = (int)(farzero/3);
	solution->min_pbr_yards = (int)(min_pbr_range/3);
	solution->max_pbr_yards = (int)(max_pbr_range/3);
	solution->sight_in_at_100yards = tin100;

	return 0;
}
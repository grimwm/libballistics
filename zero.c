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

// Used to determine bore angle
#include "ballistics.h"

double zero_angle(int drag_function, double drag_coefficient, double vi, double sight_height, double zero_range,
									double y_intercept) {

	// Numerical Integration variables
	double t=0;
	double dt=1/vi; // The solution accuracy generally doesn't suffer if its within a foot for each second of time.
	double y=-sight_height/12;
	double x=0;
	double da; // The change in the bore angle used to iterate in on the correct zero angle.

	// State variables for each integration loop.
	double v=0, vx=0, vy=0; // velocity
	double vx1=0, vy1=0; // Last frame's velocity, used for computing average velocity.
	double dv=0, dvx=0, dvy=0; // acceleration
	double Gx=0, Gy=0; // Gravitational acceleration

	double angle=0; // The actual angle of the bore.

	int quit=0; // We know it's time to quit our successive approximation loop when this is 1.

	// Start with a very coarse angular change, to quickly solve even large launch angle problems.
	da= deg_to_rad(14);


	// The general idea here is to start at 0 degrees elevation, and increase the elevation by 14 degrees
	// until we are above the correct elevation.  Then reduce the angular change by half, and begin reducing
	// the angle.  Once we are again below the correct angle, reduce the angular change by half again, and go
	// back up.  This allows for a fast successive approximation of the correct elevation, usually within less
	// than 20 iterations.
	for (angle=0;quit==0;angle=angle+da) {
		vy=vi*sin(angle);
		vx=vi*cos(angle);
		Gx=GRAVITY*sin(angle);
		Gy=GRAVITY*cos(angle);

		for (t=0,x=0,y=-sight_height/12;x<=zero_range*3;t=t+dt) {
			vy1=vy;
			vx1=vx;
			v=pow((pow(vx,2)+pow(vy,2)),0.5);
			dt=1/v;
			
			dv = retard(drag_function, drag_coefficient, v);
			dvy = -dv*vy/v*dt;
			dvx = -dv*vx/v*dt;

			vx=vx+dvx;
			vy=vy+dvy;
			vy=vy+dt*Gy;
			vx=vx+dt*Gx;
			
			x=x+dt*(vx+vx1)/2;
			y=y+dt*(vy+vy1)/2;
			// Break early to save CPU time if we won't find a solution.
			if (vy<0 && y<y_intercept) {
				break;
			}
			if (vy>3*vx) { 
				break;
			}
		}
	
		if (y>y_intercept && da>0) {
			da=-da/2;
		}

		if (y<y_intercept && da<0) {
			da=-da/2;
		}

		if (fabs(da) < moa_to_rad(0.01)) quit=1; // If our accuracy is sufficient, we can stop approximating.
		if (angle > deg_to_rad(45)) quit=1; // If we exceed the 45 degree launch angle, then the projectile just won't get there, so we stop trying.
	}

	return rad_to_deg(angle); // Convert to degrees for return value.
}



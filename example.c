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

//The following is all you need to compile this example: 
//gcc -o example example.c -lm

#include <stdio.h>
#include "ballistics.c"
#include "angle.c"
#include "atmosphere.c"

//The values below are from winchester 147 gr FMJ .308 out of a 20" barrel
//The sight height is typical for scopes mounted on AR platforms.
int main(void) {
	int k=0;
	Ballistics* solution;
	double G1_bc=0.415; // The ballistic coefficient for the projectile.
	double v=2804; // Intial velocity, in ft/s
	double sh=1.6; // The Sight height over bore, in inches.
	double angle=0; // The shooting angle (uphill / downhill), in degrees.
	double zero=100; // The zero range of the rifle, in yards.
	double windspeed=0; // The wind speed in miles per hour.
	double windangle=0; // The wind angle (0=headwind, 90=right to left, 180=tailwind, 270/-90=left to right)
	
	// If we wish to use the weather correction features, we need to 
	// Correct the BC for any weather conditions.  If we want standard conditions,
	// then we can just leave this commented out.

	G1_bc = atmosphere_correction(G1_bc, 0, 29.59, 59, .58);
	
	
	// First find the angle of the bore relative to the sighting system.
	// We call this the "zero angle", since it is the angle required to 
	// achieve a zero at a particular yardage.  This value isn't very useful
	// to us, but is required for making a full ballistic solution.
	// It is left here to allow for zero-ing at altitudes (bc) different from the
	// final solution, or to allow for zero's other than 0" (ex: 3" high at 100 yds)
	double zeroangle = zero_angle(G1, G1_bc, v, sh, zero, 0);
	
	// Now we have everything needed to generate a full solution.
	// So we do.  The solution is stored in the pointer "sln" passed as the last argument.
	// k has the number of yards the solution is valid for, also the number of rows in the solution.
	k = Ballistics_solve(&solution, G1, G1_bc, v, sh, angle, zeroangle, windspeed, windangle);
	
	// Now print a simple chart of X / Y trajectory spaced at 100yd increments
	for (int s=0; s<=1000; s+=100) {
		printf("Distance (yards): %.0f     Vertical Correction (inches): %.2f\n", Ballistics_get_range(solution, s), Ballistics_get_path(solution, s));
	}

    Ballistics_free(solution);
	
	return 0;
}
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

// GNU Ballistics Library
// Originally created by Derek Yates

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define BALLISTICS_COMPUTATION_MAX_YARDS 50000
#define GRAVITY (-32.194)

//#include <math.h>
//#include <stdlib.h>

#include "pbr.h"

struct BallisticsSolutions;

// Angular conversion functions to make things a little easier.
double deg_to_moa(double deg); // Converts degrees to minutes of angle
double deg_to_rad(double deg); // Converts degrees to radians
double moa_to_deg(double moa); // Converts minutes of angle to degrees
double moa_to_rad(double moa); // Converts minutes of angle to radians
double rad_to_deg(double rad); // Converts radians to degrees
double rad_to_moa(double rad); // Converts radiants to minutes of angle

/**
 * A function to calculate ballistic retardation values based on standard drag functions.
 * @param drag_function    G1, G2, G3, G4, G5, G6, G7, or G8
 * @param drag_coefficient The coefficient of drag for the projectile for the given drag function.
 * @param vp               The Velocity of the projectile.
 * @return The function returns the projectile drag retardation velocity, in ft/s per second.
 */
double retard(DragFunction drag_function, double drag_coefficient, double vp);

/**
 * A function to correct a "standard" Drag Coefficient for differing atmospheric conditions.
 * @param drag_coefficient  G1, G2, G3, G4, G5, G6, G7, or G8
 * @param altitude          The altitude above sea level in feet.  Standard altitude is 0 feet above sea level.
 * @param barometer         The barometric pressure in inches of mercury (in Hg).
 *                          This is not "absolute" pressure, it is the "standardized" pressure reported in the papers and news.
 *                          Standard pressure is 29.53 in Hg.
 * @param temperature       The temperature in Fahrenheit.  Standard temperature is 59 degrees.
 * @param relative_humidity The relative humidity fraction.  Ranges from 0.00 to 1.00, with 0.50 being 50% relative humidity.
 *                          Standard humidity is 78%
 * @return The corrected drag coefficient for the supplied drag coefficient and atmospheric conditions.
 */
double atmosphere_correction(double drag_coefficient, double altitude, double barometer, double temperature,
                             double relative_humidity);

/**
 * A function to compute the windage deflection for a given crosswind speed,
 * given flight time in a vacuum, and given flight time in real life.
 * @param wind_speed The wind velocity in mi/hr.
 * @param vi         The initial velocity of the projectile (muzzle velocity).
 * @param x          The range at which you wish to determine windage, in feet.
 * @param t          The time it has taken the projectile to traverse the range x, in seconds.
 * @return The amount of windage correction, in inches, required to achieve zero on a target at the given range.
 */
double windage(double wind_speed, double vi, double x, double t);

/**
 * Resolve any wind / angle combination into headwind.
 * @param wind_speed The wind velocity, in mi/hr.
 * @param wind_angle The angle from which the wind is coming, in degrees.
 *                   0 degrees is from straight ahead
 *                   90 degrees is from right to left
 *                   180 degrees is from directly behind
 *                   270 or -90 degrees is from left to right.
 * @return the headwind or crosswind velocity component, in mi/hr.
 */
double headwind(double wind_speed, double wind_angle);

/**
 * Resolve any wind / angle combination into crosswind.
 * @param wind_speed The wind velocity, in mi/hr.
 * @param wind_angle The angle from which the wind is coming, in degrees.
 *                   0 degrees is from straight ahead
 *                   90 degrees is from right to left
 *                   180 degrees is from directly behind
 *                   270 or -90 degrees is from left to right.
 * @return the headwind or crosswind velocity component, in mi/hr.
 */
double crosswind(double wind_speed, double wind_angle);

/**
 * A function to determine the bore angle needed to achieve a target zero at Range yards
 * (at standard conditions and on level ground.)
 * @param drag_function    G1, G2, G3, G5, G6, G7, or G8
 * @param drag_coefficient The coefficient of drag for the projectile, for the supplied drag function.
 * @param vi               The initial velocity of the projectile, in feet/s
 * @param sight_height     The height of the sighting system above the bore centerline, in inches.
 *                         Most scopes fall in the 1.6 to 2.0 inch range.
 * @param zero_range       The range in yards, at which you wish the projectile to intersect yIntercept.
 * @param y_intercept      The height, in inches, you wish for the projectile to be when it crosses ZeroRange yards.
 *                         This is usually 0 for a target zero, but could be any number.  For example if you wish
 *                         to sight your rifle in 1.5" high at 100 yds, then you would set yIntercept to 1.5, and ZeroRange to 100
 * @return The angle of the bore relative to the sighting system, in degrees.
 */
double zero_angle(DragFunction drag_function, double drag_coefficient, double vi, double sight_height, double zero_range,
                  double y_intercept);

// Functions for retrieving data from a solution generated with solve()
void solution_free(struct BallisticsSolutions* solution);

// Returns range, in yards.
double solution_get_range(struct BallisticsSolutions* solution, int yardage);
// Returns projectile path, in inches, relative to the line of sight.
double solution_get_path(struct BallisticsSolutions* solution, int yardage);
// Returns an estimated elevation correction for achieving a zero at this range.
// this is useful for "click charts" and the like.
double solution_get_moa(struct BallisticsSolutions* solution, int yardage);
// Returns the projectile's time of flight to this range.
double solution_get_time(struct BallisticsSolutions* solution, int yardage);
// Returns the windage correction in inches required to achieve zero at this range.
double solution_get_windage(struct BallisticsSolutions* solution, int yardage);
// Returns an approximate windage correction in MOA to achieve a zero at this range.
double solution_get_windage_moa(struct BallisticsSolutions* solution, int yardage);
// Returns the projectile's total velocity (Vector product of Vx and Vy)
double solution_get_velocity(struct BallisticsSolutions* solution, int yardage);
// Returns the velocity of the projectile in the bore direction.
double solution_get_vx(struct BallisticsSolutions* solution, int yardage);
// Returns the velocity of the projectile perpendicular to the bore direction.
double solution_get_vy(struct BallisticsSolutions* solution, int yardage);

// For very steep shooting angles, vx can actually become what you would think of as vy relative to the ground,
// because vx is referencing the bore's axis.  All computations are carried out relative to the bore's axis, and
// have very little to do with the ground's orientation.

/**
 * A function to generate a ballistic solution table in 1 yard increments, up to BCOMP_MAXRANGE.
 * @param drag_function    G1, G2, G3, G5, G6, G7, or G8
 * @param drag_coefficient The coefficient of drag for the projectile you wish to model.
 * @param vi               The projectile initial velocity.
 * @param sight_height     The height of the sighting system above the bore centerline.
 *                         Most scopes are in the 1.5"-2.0" range.
 * @param shooting_angle   The uphill or downhill shooting angle, in degrees.  Usually 0, but can be anything from
 *                         90 (directly up), to -90 (directly down).
 * @param zero_angle       The angle of the sighting system relative to the bore, in degrees.  This can be easily computed
 *                         using the ZeroAngle() function documented above.
 * @param wind_speed       The wind velocity, in mi/hr
 * @param wind_angle       The angle at which the wind is approaching from, in degrees.
 *                         0 degrees is a straight headwind
 *                         90 degrees is from right to left
 *                         180 degrees is a straight tailwind
 *                         -90 or 270 degrees is from left to right.
 * @param solution         A pointer provided for accessing the solution after it has been generated.
 *                         Memory for this pointer is allocated in the function, so the user does not need
 *                         to worry about it.  This solution can be passed to the retrieval functions to get
 *                         useful data from the solution.
 * @return This function returns an integer representing the maximum valid range of the
 *         solution.  This also indicates the maximum number of rows in the solution matrix,
 *         and should not be exceeded in order to avoid a memory segmentation fault.
 */
int solve(struct BallisticsSolutions** solution, DragFunction drag_function, double drag_coefficient, double vi,
          double sight_height, double shooting_angle, double zero_angle, double wind_speed, double wind_angle);

#ifdef __cplusplus
} // extern "C"
#endif
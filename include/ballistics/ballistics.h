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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "constants.h"
#include "angle.h"
#include "atmosphere.h"
#include "windage.h"
#include "pbr.h"

struct Ballistics;

// Functions for retrieving data from a solution generated with solve()
void Ballistics_free(struct Ballistics* ballistics);

// Returns range, in yards.
double Ballistics_get_range(struct Ballistics* ballistics, int yardage);
// Returns projectile path, in inches, relative to the line of sight.
double Ballistics_get_path(struct Ballistics* ballistics, int yardage);
// Returns an estimated elevation correction for achieving a zero at this range.
// this is useful for "click charts" and the like.
double Ballistics_get_moa(struct Ballistics* ballistics, int yardage);
// Returns the projectile's time of flight to this range.
double Ballistics_get_time(struct Ballistics* ballistics, int yardage);
// Returns the windage correction in inches required to achieve zero at this range.
double Ballistics_get_windage(struct Ballistics* ballistics, int yardage);
// Returns an approximate windage correction in MOA to achieve a zero at this range.
double Ballistics_get_windage_moa(struct Ballistics* ballistics, int yardage);
// Returns the projectile's total velocity (Vector product of Vx and Vy)
double Ballistics_get_velocity(struct Ballistics* ballistics, int yardage);
// Returns the velocity of the projectile in the bore direction.
double Ballistics_get_vx(struct Ballistics* ballistics, int yardage);
// Returns the velocity of the projectile perpendicular to the bore direction.
double Ballistics_get_vy(struct Ballistics* ballistics, int yardage);

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
 * @param ballistics       A pointer provided for accessing the solution after it has been generated.
 *                         Memory for this pointer is allocated in the function, so the user does not need
 *                         to worry about it.  This solution can be passed to the retrieval functions to get
 *                         useful data from the solution.
 * @return This function returns an integer representing the maximum valid range of the
 *         solution.  This also indicates the maximum number of rows in the solution matrix,
 *         and should not be exceeded in order to avoid a memory segmentation fault.
 */
int Ballistics_solve(struct Ballistics** ballistics, DragFunction drag_function, double drag_coefficient, double vi,
                     double sight_height, double shooting_angle, double zero_angle, double wind_speed, double wind_angle);

#ifdef __cplusplus
} // extern "C"
#endif
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

#include "drag.h"

#ifdef __cplusplus
extern "C" {
#endif

// Angular conversion functions to make things a little easier.
double deg_to_moa(double deg); // Converts degrees to minutes of angle
double deg_to_rad(double deg); // Converts degrees to radians
double moa_to_deg(double moa); // Converts minutes of angle to degrees
double moa_to_rad(double moa); // Converts minutes of angle to radians
double rad_to_deg(double rad); // Converts radians to degrees
double rad_to_moa(double rad); // Converts radiants to minutes of angle

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

#ifdef __cplusplus
}
#endif
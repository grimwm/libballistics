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
 * Headwind is positive at {@code wind_angle=0}
 * @param wind_speed The wind velocity, in mi/hr.
 * @param wind_angle The angle from which the wind is coming, in degrees.
 *                   0 degrees is from straight ahead
 *                   90 degrees is from right to left
 *                   180 degrees is from directly behind
 *                   270 or -90 degrees is from left to right.
 * @return the headwind velocity component, in mi/hr.
 */
double headwind(double wind_speed, double wind_angle);

/**
 * Resolve any wind / angle combination into crosswind.
 * Positive is from Shooter's Right to Left (Wind from 90 degree)
 * @param wind_speed The wind velocity, in mi/hr.
 * @param wind_angle The angle from which the wind is coming, in degrees.
 *                   0 degrees is from straight ahead
 *                   90 degrees is from right to left
 *                   180 degrees is from directly behind
 *                   270 or -90 degrees is from left to right.
 * @return the crosswind velocity component, in mi/hr.
 */
double crosswind(double wind_speed, double wind_angle);

#ifdef __cplusplus
}
#endif
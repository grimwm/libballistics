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

#include <math.h>

double windage(double wind_speed, double vi, double xx, double t) {
	double vw = wind_speed*17.60; // Convert to inches per second.
	return (vw*(t-xx/vi));
}

// Headwind is positive at wind_angle=0
double headwind(double wind_speed, double wind_angle) {
	double w_angle = deg_to_rad(wind_angle);
	return (cos(w_angle) * wind_speed);
}

// Positive is from Shooter's Right to Left (Wind from 90 degree)
double crosswind(double wind_speed, double wind_angle) {
	double w_angle = deg_to_rad(wind_angle);
	return (sin(w_angle) * wind_speed);
}
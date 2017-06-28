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

// Specialty angular conversion functions
#include <math.h>

double deg_to_moa(double deg) {
	return deg*60;
}
double deg_to_rad(double deg) {
	return deg*M_PI/180;
}
double moa_to_deg(double moa) {
	return moa/60;
}
double moa_to_rad(double moa) {
	return moa/60*M_PI/180;
}
double rad_to_deg(double rad) {
	return rad*180/M_PI;
}
double rad_to_moa(double rad) {
	return rad*60*180/M_PI;
}
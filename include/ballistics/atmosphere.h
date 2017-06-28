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

#ifdef __cplusplus
}
#endif
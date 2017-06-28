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

typedef enum {
  G1 = 1, G2, G3, G4, G5, G6, G7, G8
} DragFunction;

/**
 * A function to calculate ballistic retardation values based on standard drag functions.
 * @param drag_function    G1, G2, G3, G4, G5, G6, G7, or G8
 * @param drag_coefficient The coefficient of drag for the projectile for the given drag function.
 * @param vp               The Velocity of the projectile.
 * @return The function returns the projectile drag retardation velocity, in ft/s per second.
 */
double retard(DragFunction drag_function, double drag_coefficient, double vp);

#ifdef __cplusplus
} // extern "C"
#endif
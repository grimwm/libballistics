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

#define PBR_E_OUT_OF_RANGE -1
#define PBR_E_TOO_FAST_VY  -2

struct PBR;

/**
 * The near-side of the ballistic trajectory where scope and projectile meet (center-mass).
 * @param pbr
 * @return near zero in yards
 */
int PBR_get_near_zero_yards(struct PBR* pbr);

/**
 * The far-side of the ballistic trajectory where scope and projectile meet (center-mass).
 * @param pbr
 * @return far zero in yards
 */
int PBR_get_far_zero_yards(struct PBR* pbr);

/**
 * The minimum distance your target can be for you to hit the target area.
 * @param pbr
 * @return
 */
int PBR_get_min_PBR_yards(struct PBR* pbr);

/**
 * The maximum distance your target can be for you to hit the target area.
 * @param pbr
 * @return max distance in yards
 */
int PBR_get_max_PBR_yards(struct PBR* pbr);

/**
 * Tells you how to sight in your scope at 100 yards to make the PBR work.
 * @param pbr
 * @return positive values are how many inches above center your bullets should land; negative values are below center
 */
int PBR_get_sight_in_at_100yards(struct PBR* pbr);

void PBR_free(struct PBR* pbr);

/**
 * Solves for the maximum Point blank range and associated details.
 * @param pbr              a pointer to the pbr's results
 * @param drag_function    G1, G2, G3, G5, G6, G7, or G8
 * @param drag_coefficient The coefficient of drag for the projectile you wish to model.
 * @param vi               The projectile initial velocity.
 * @param sight_height     The height of the sighting system above the bore centerline.
                           Most scopes are in the 1.5"-2.0" range.
 * @param vital_size
 * @return 0 if pbr exists, -1 for any errors
 */
int PBR_solve(struct PBR** pbr, DragFunction drag_function, double drag_coefficient, double vi,
              double sight_height, double vital_size);

#ifdef __cplusplus
} // extern "C"
#endif
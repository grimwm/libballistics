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

#include <math.h>

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
static inline double retard(DragFunction drag_function, double drag_coefficient, double vp) {
  double acceleration = -1;
  double mass = -1;

  switch(drag_function) {
    case G1:
      if (vp > 4230) {     acceleration = 1.477404177730177e-04; mass = 1.9565; }
      else if (vp> 3680) { acceleration = 1.920339268755614e-04; mass = 1.925 ; }
      else if (vp> 3450) { acceleration = 2.894751026819746e-04; mass = 1.875 ; }
      else if (vp> 3295) { acceleration = 4.349905111115636e-04; mass = 1.825 ; }
      else if (vp> 3130) { acceleration = 6.520421871892662e-04; mass = 1.775 ; }
      else if (vp> 2960) { acceleration = 9.748073694078696e-04; mass = 1.725 ; }
      else if (vp> 2830) { acceleration = 1.453721560187286e-03; mass = 1.675 ; }
      else if (vp> 2680) { acceleration = 2.162887202930376e-03; mass = 1.625 ; }
      else if (vp> 2460) { acceleration = 3.209559783129881e-03; mass = 1.575 ; }
      else if (vp> 2225) { acceleration = 3.904368218691249e-03; mass = 1.55  ; }
      else if (vp> 2015) { acceleration = 3.222942271262336e-03; mass = 1.575 ; }
      else if (vp> 1890) { acceleration = 2.203329542297809e-03; mass = 1.625 ; }
      else if (vp> 1810) { acceleration = 1.511001028891904e-03; mass = 1.675 ; }
      else if (vp> 1730) { acceleration = 8.609957592468259e-04; mass = 1.75  ; }
      else if (vp> 1595) { acceleration = 4.086146797305117e-04; mass = 1.85  ; }
      else if (vp> 1520) { acceleration = 1.954473210037398e-04; mass = 1.95  ; }
      else if (vp> 1420) { acceleration = 5.431896266462351e-05; mass = 2.125 ; }
      else if (vp> 1360) { acceleration = 8.847742581674416e-06; mass = 2.375 ; }
      else if (vp> 1315) { acceleration = 1.456922328720298e-06; mass = 2.625 ; }
      else if (vp> 1280) { acceleration = 2.419485191895565e-07; mass = 2.875 ; }
      else if (vp> 1220) { acceleration = 1.657956321067612e-08; mass = 3.25  ; }
      else if (vp> 1185) { acceleration = 4.745469537157371e-10; mass = 3.75  ; }
      else if (vp> 1150) { acceleration = 1.379746590025088e-11; mass = 4.25  ; }
      else if (vp> 1100) { acceleration = 4.070157961147882e-13; mass = 4.75  ; }
      else if (vp> 1060) { acceleration = 2.938236954847331e-14; mass = 5.125 ; }
      else if (vp> 1025) { acceleration = 1.228597370774746e-14; mass = 5.25  ; }
      else if (vp>  980) { acceleration = 2.916938264100495e-14; mass = 5.125 ; }
      else if (vp>  945) { acceleration = 3.855099424807451e-13; mass = 4.75  ; }
      else if (vp>  905) { acceleration = 1.185097045689854e-11; mass = 4.25  ; }
      else if (vp>  860) { acceleration = 3.566129470974951e-10; mass = 3.75  ; }
      else if (vp>  810) { acceleration = 1.045513263966272e-08; mass = 3.25  ; }
      else if (vp>  780) { acceleration = 1.291159200846216e-07; mass = 2.875 ; }
      else if (vp>  750) { acceleration = 6.824429329105383e-07; mass = 2.625 ; }
      else if (vp>  700) { acceleration = 3.569169672385163e-06; mass = 2.375 ; }
      else if (vp>  640) { acceleration = 1.839015095899579e-05; mass = 2.125 ; }
      else if (vp>  600) { acceleration = 5.71117468873424e-05 ; mass = 1.950 ; }
      else if (vp>  550) { acceleration = 9.226557091973427e-05; mass = 1.875 ; }
      else if (vp>  250) { acceleration = 9.337991957131389e-05; mass = 1.875 ; }
      else if (vp>  100) { acceleration = 7.225247327590413e-05; mass = 1.925 ; }
      else if (vp>   65) { acceleration = 5.792684957074546e-05; mass = 1.975 ; }
      else if (vp>    0) { acceleration = 5.206214107320588e-05; mass = 2.000 ; }
      break;

    case G2:
      if (vp> 1674 ) {      acceleration = 0.0079470052136733  ;  mass = 1.36999902851493; }
      else if (vp> 1172 ) { acceleration = 1.00419763721974e-03;  mass = 1.65392237010294; }
      else if (vp> 1060 ) { acceleration = 7.15571228255369e-23;  mass = 7.91913562392361; }
      else if (vp>  949 ) { acceleration = 1.39589807205091e-10;  mass = 3.81439537623717; }
      else if (vp>  670 ) { acceleration = 2.34364342818625e-04;  mass = 1.71869536324748; }
      else if (vp>  335 ) { acceleration = 1.77962438921838e-04;  mass = 1.76877550388679; }
      else if (vp>    0 ) { acceleration = 5.18033561289704e-05;  mass = 1.98160270524632; }
      break;

    case G5:
      if (vp> 1730 ) {      acceleration = 7.24854775171929e-03; mass = 1.41538574492812; }
      else if (vp> 1228 ) { acceleration = 3.50563361516117e-05; mass = 2.13077307854948; }
      else if (vp> 1116 ) { acceleration = 1.84029481181151e-13; mass = 4.81927320350395; }
      else if (vp> 1004 ) { acceleration = 1.34713064017409e-22; mass = 7.8100555281422 ; }
      else if (vp>  837 ) { acceleration = 1.03965974081168e-07; mass = 2.84204791809926; }
      else if (vp>  335 ) { acceleration = 1.09301593869823e-04; mass = 1.81096361579504; }
      else if (vp>    0 ) { acceleration = 3.51963178524273e-05; mass = 2.00477856801111; }
      break;

    case G6:
      if (vp> 3236 ) {      acceleration = 0.0455384883480781   ; mass = 1.15997674041274; }
      else if (vp> 2065 ) { acceleration = 7.167261849653769e-02; mass = 1.10704436538885; }
      else if (vp> 1311 ) { acceleration = 1.66676386084348e-03 ; mass = 1.60085100195952; }
      else if (vp> 1144 ) { acceleration = 1.01482730119215e-07 ; mass = 2.9569674731838 ; }
      else if (vp> 1004 ) { acceleration = 4.31542773103552e-18 ; mass = 6.34106317069757; }
      else if (vp>  670 ) { acceleration = 2.04835650496866e-05 ; mass = 2.11688446325998; }
      else if (vp>    0 ) { acceleration = 7.50912466084823e-05 ; mass = 1.92031057847052; }
      break;

    case G7:
      if (vp> 4200 ) {      acceleration = 1.29081656775919e-09; mass = 3.24121295355962; }
      else if (vp> 3000 ) { acceleration = 0.0171422231434847  ; mass = 1.27907168025204; }
      else if (vp> 1470 ) { acceleration = 2.33355948302505e-03; mass = 1.52693913274526; }
      else if (vp> 1260 ) { acceleration = 7.97592111627665e-04; mass = 1.67688974440324; }
      else if (vp> 1110 ) { acceleration = 5.71086414289273e-12; mass = 4.3212826264889 ; }
      else if (vp>  960 ) { acceleration = 3.02865108244904e-17; mass = 5.99074203776707; }
      else if (vp>  670 ) { acceleration = 7.52285155782535e-06; mass = 2.1738019851075 ; }
      else if (vp>  540 ) { acceleration = 1.31766281225189e-05; mass = 2.08774690257991; }
      else if (vp>    0 ) { acceleration = 1.34504843776525e-05; mass = 2.08702306738884; }
      break;

    case G8:
      if (vp> 3571 ) {      acceleration = 0.0112263766252305  ; mass = 1.33207346655961; }
      else if (vp> 1841 ) { acceleration = 0.0167252613732636  ; mass = 1.28662041261785; }
      else if (vp> 1120 ) { acceleration = 2.20172456619625e-03; mass = 1.55636358091189; }
      else if (vp> 1088 ) { acceleration = 2.0538037167098e-16 ; mass = 5.80410776994789; }
      else if (vp>  976 ) { acceleration = 5.92182174254121e-12; mass = 4.29275576134191; }
      else if (vp>    0 ) { acceleration = 4.3917343795117e-05 ; mass = 1.99978116283334; }
      break;

    default:
      break;
  }

  if (acceleration != -1 && mass != -1 && vp > 0 && vp < 10000) {
    return acceleration * pow(vp,mass)/drag_coefficient;
  }
  else {
    return -1;
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
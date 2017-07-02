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

// Drag coefficient atmospheric corrections
static inline double calcFR(double temperature, double pressure, double relative_humidity) {
	double VPw=4e-6*pow(temperature,3) - 0.0004*pow(temperature,2)+0.0234*temperature-0.2517;
	double frh=0.995*(pressure/(pressure-(0.3783)*(relative_humidity)*VPw));
	return frh;
}

static inline double calcFP(double pressure) {
	double p_std = 29.53; // in-hg; standard pressure at sea level
	double fp=0;
	fp = (pressure - p_std)/(p_std);
	return fp;
}

static inline double calcFT(double temperature, double altitude) {
	double t_std=-0.0036*altitude+59;
	double FT = (temperature-t_std)/(459.6+t_std);
	return FT;
}

static inline double calcFA(double altitude) {
	double fa=0;
	fa=-4e-15*pow(altitude,3)+4e-10*pow(altitude,2)-3e-5*altitude+1;
	return (1/fa);
}

double atmosphere_correction(double drag_coefficient, double altitude, double barometer, double temperature,
														 double relative_humidity) {

	double fa = calcFA(altitude);
	double ft = calcFT(temperature, altitude);
	double fr = calcFR(temperature, barometer, relative_humidity);
	double fp = calcFP(barometer);

	// Calculate the atmospheric correction factor
	double cd = (fa*(1+ft-fp)*fr);
	return drag_coefficient*cd;
}
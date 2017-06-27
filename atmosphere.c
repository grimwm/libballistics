// Drag coefficient atmospheric corrections
#include "ballistics.h"

double calcFR(double Temperature, double Pressure, double RelativeHumidity) {
	double VPw=4e-6*pow(Temperature,3) - 0.0004*pow(Temperature,2)+0.0234*Temperature-0.2517;
	double FRH=0.995*(Pressure/(Pressure-(0.3783)*(RelativeHumidity)*VPw));
	return FRH;
}

double calcFP(double Pressure) {
	double Pstd=29.53; // in-hg
	double FP=0;
	FP = (Pressure-Pstd)/(Pstd);
	return FP;
}

double calcFT(double Temperature,double Altitude) {
	double Tstd=-0.0036*Altitude+59;
	double FT = (Temperature-Tstd)/(459.6+Tstd);
	return FT;
}

double calcFA(double Altitude) {
	double fa=0;
	fa=-4e-15*pow(Altitude,3)+4e-10*pow(Altitude,2)-3e-5*Altitude+1;
	return (1/fa);
}

double atmosphere_correction(double drag_coefficient, double altitude, double barometer, double temperature,
														 double relative_humidity) {

	double FA = calcFA(altitude);
	double FT = calcFT(temperature, altitude);
	double FR = calcFR(temperature, barometer, relative_humidity);
	double FP = calcFP(barometer);

	// Calculate the atmospheric correction factor
	double CD = (FA*(1+FT-FP)*FR);
	return drag_coefficient*CD;
}


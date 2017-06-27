// Crosswind correction functions
#include "ballistics.h"

double windage(double wind_speed, double vi, double xx, double t) {
	double vw = wind_speed*17.60; // Convert to inches per second.
	return (vw*(t-xx/vi));
}

// Headwind is positive at WindAngle=0
double headwind(double wind_speed, double wind_angle) {
	double w_angle = deg_to_rad(wind_angle);
	return (cos(w_angle)*wind_speed);
}

// Positive is from Shooter's Right to Left (Wind from 90 degree)
double crosswind(double wind_speed, double wind_angle) {
	double w_angle = deg_to_rad(wind_angle);
	return (sin(w_angle)*wind_speed);
}



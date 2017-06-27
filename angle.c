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


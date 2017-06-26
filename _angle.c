// Specialty angular conversion functions
double DegtoMOA(double deg){
	return deg*60;
}
double DegtoRad(double deg){
	return deg*M_PI/180;
}
double MOAtoDeg(double moa){
	return moa/60;
}
double MOAtoRad(double moa){
	return moa/60*M_PI/180;
}
double RadtoDeg(double rad){
	return rad*180/M_PI;
}
double RadtoMOA(double rad){
	return rad*60*180/M_PI;
}


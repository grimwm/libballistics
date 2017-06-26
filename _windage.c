double Windage(double WindSpeed, double Vi, double xx, double t){
	double Vw = WindSpeed*17.60; // Convert to inches per second.
	return (Vw*(t-xx/Vi));
}


// Headwind is positive at WindAngle=0
double HeadWind(double WindSpeed, double WindAngle){
	double Wangle = DegtoRad(WindAngle);
	return (cos(Wangle)*WindSpeed);
}

// Positive is from Shooter's Right to Left (Wind from 90 degree)
double CrossWind(double WindSpeed, double WindAngle){
	double Wangle = DegtoRad(WindAngle);
	return (sin(Wangle)*WindSpeed);
}



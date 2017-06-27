// Used to make retrieving solution data easier.
#include "ballistics.h"

double GetRange(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage];
	}
	else return 0;
}

double GetPath(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+1];
	}
	else return 0;
}

double GetMOA(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+2];
	}
	else return 0;
}


double GetTime(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+3];
	}
	else return 0;
}

double GetWindage(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+4];
	}
	else return 0;
}

double GetWindageMOA(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+5];
	}
	else return 0;
}

double GetVelocity(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+6];
	}
	else return 0;
}

double GetVx(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+7];
	}
	else return 0;
}

double GetVy(double* sln, int yardage) {
	double size=sln[__BCOMP_MAXRANGE__*10+1];
	if (yardage<size) {
		return sln[10*yardage+8];
	}
	else return 0;
}


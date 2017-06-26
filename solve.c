// Used to solve ballistic problems 
#include "ballistics.h"

int SolveAll(int DragFunction, double DragCoefficient, double Vi, double SightHeight, \
double ShootingAngle, double ZAngle, double WindSpeed, double WindAngle, double** Solution){

	double* ptr = malloc(10*__BCOMP_MAXRANGE__*sizeof(double)+2);
	
	double t=0;
	double dt=0.5/Vi;
	double v=0;
	double vx=0, vx1=0, vy=0, vy1=0;
	double dv=0, dvx=0, dvy=0;
	double x=0, y=0;
	
	double headwind=HeadWind(WindSpeed, WindAngle);
	double crosswind=CrossWind(WindSpeed, WindAngle);
	
	double Gy=GRAVITY*cos(DegtoRad((ShootingAngle + ZAngle)));
	double Gx=GRAVITY*sin(DegtoRad((ShootingAngle + ZAngle)));

	vx=Vi*cos(DegtoRad(ZAngle));
	vy=Vi*sin(DegtoRad(ZAngle));

	y=-SightHeight/12;

	int n=0;
	for (t=0;;t=t+dt){

		vx1=vx, vy1=vy;	
		v=pow(pow(vx,2)+pow(vy,2),0.5);
		dt=0.5/v;
	
		// Compute acceleration using the drag function retardation	
		dv = retard(G1,DragCoefficient,v+headwind);		
		dvx = -(vx/v)*dv;
		dvy = -(vy/v)*dv;

		// Compute velocity, including the resolved gravity vectors.	
		vx=vx + dt*dvx + dt*Gx;
		vy=vy + dt*dvy + dt*Gy;



		if (x/3>=n){
			ptr[10*n+0]=x/3;							// Range in yds
			ptr[10*n+1]=y*12;							// Path in inches
			ptr[10*n+2]=-RadtoMOA(atan(y/x));			// Correction in MOA
			ptr[10*n+3]=t+dt;							// Time in s
			ptr[10*n+4]=Windage(crosswind,Vi,x,t+dt); 	// Windage in inches
			ptr[10*n+5]=RadtoMOA(atan(ptr[10*n+4]));	// Windage in MOA
			ptr[10*n+6]=v;								// Velocity (combined)
			ptr[10*n+7]=vx;							// Velocity (x)
			ptr[10*n+8]=vy;							// Velocity (y)
			ptr[10*n+9]=0;								// Reserved
			n++;	
		}	
		
		// Compute position based on average velocity.
		x=x+dt*(vx+vx1)/2;
		y=y+dt*(vy+vy1)/2;
		
		if (fabs(vy)>fabs(3*vx)) break;
		if (n>=__BCOMP_MAXRANGE__) break;
	}
	*Solution = ptr;
	ptr[10*__BCOMP_MAXRANGE__+1]=(double)n;
	return n;
}

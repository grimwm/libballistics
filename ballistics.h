// GNU Ballistics Library
// Originally created by Derek Yates
// Now available free under the GNU GPL



#ifndef __lib_ballistics__
#define __lib_ballistics__
#define __BCOMP_MAXRANGE__ 5000
#define GRAVITY (-32.194)
#include <math.h>
#include <stdlib.h>

enum DragFunctions {G1=1,G2,G3,G4,G5,G6,G7,G8};

// Angular conversion functions to make things a little easier. 
double DegtoMOA(double deg); // Converts degrees to minutes of angle
double DegtoRad(double deg); // Converts degrees to radians
double MOAtoDeg(double moa); // Converts minutes of angle to degrees
double MOAtoRad(double moa); // Converts minutes of angle to radians
double RadtoDeg(double rad); // Converts radians to degrees
double RadtoMOA(double rad); // Converts radiants to minutes of angle


// A function to calculate ballistic retardation values based on standard drag functions.
double retard(int DragFunction, double DragCoefficient, double Vi);
/* Arguments:
		DragFunction:  G1, G2, G3, G4, G5, G6, G7, or G8.  All are enumerated above.
		DragCoefficient:  The coefficient of drag for the projectile for the given drag function.
		Vi:  The Velocity of the projectile.
	
	Return Value: 
		The function returns the projectile drag retardation velocity, in ft/s per second.
		
*/


// A function to correct a "standard" Drag Coefficient for differing atmospheric conditions.
// Returns the corrected drag coefficient for supplied drag coefficient and atmospheric conditions.
double AtmCorrect(double DragCoefficient, double Altitude, double Barometer, double Temperature, double RelativeHumidity);
/* Arguments:
		DragCoefficient:  The coefficient of drag for a given projectile.
		Altitude:  The altitude above sea level in feet.  Standard altitude is 0 feet above sea level.
		Barometer:  The barometric pressure in inches of mercury (in Hg).
					This is not "absolute" pressure, it is the "standardized" pressure reported in the papers and news.
					Standard pressure is 29.53 in Hg.
		Temperature:  The temperature in Fahrenheit.  Standard temperature is 59 degrees.
		RelativeHumidity:  The relative humidity fraction.  Ranges from 0.00 to 1.00, with 0.50 being 50% relative humidity.
							Standard humidity is 78%

	Return Value:
		The function returns a ballistic coefficient, corrected for the supplied atmospheric conditions.
*/


// A function to compute the windage deflection for a given crosswind speed,
// given flight time in a vacuum, and given flight time in real life.
// Returns the windage correction needed in inches.
double Windage(double WindSpeed, double Vi, double x, double t);
/* Arguments:
		WindSpeed:  The wind velocity in mi/hr.
		Vi:  The initial velocity of the projectile (muzzle velocity).
		x:  The range at which you wish to determine windage, in feet.
		t:  The time it has taken the projectile to traverse the range x, in seconds.
	
	Return Value:
		Returns the amount of windage correction, in inches, required to achieve zero on a target at the given range.
		
*/

// Functions to resolve any wind / angle combination into headwind and crosswind components.
double HeadWind(double WindSpeed, double WindAngle);
double CrossWind(double WindSpeed, double WindAngle);
/* Arguments:
		WindSpeed:  The wind velocity, in mi/hr.
		WindAngle:  The angle from which the wind is coming, in degrees.
					0 degrees is from straight ahead
					90 degrees is from right to left
					180 degrees is from directly behind
					270 or -90 degrees is from left to right.
	
	Return value:
		Returns the headwind or crosswind velocity component, in mi/hr.
*/


// A function to determine the bore angle needed to achieve a target zero at Range yards
// (at standard conditions and on level ground.)
double ZeroAngle(int DragFunction, double DragCoefficient, double Vi, double SightHeight, double ZeroRange, double yIntercept); 
/*  Arguments: 
		DragFunction:  The drag function to use (G1, G2, G3, G5, G6, G7, G8)
		DragCoefficient:  The coefficient of drag for the projectile, for the supplied drag function.
		Vi:  The initial velocity of the projectile, in feet/s
		SightHeight:  The height of the sighting system above the bore centerline, in inches. 
					  Most scopes fall in the 1.6 to 2.0 inch range.
		ZeroRange:  The range in yards, at which you wish the projectile to intersect yIntercept.
		yIntercept:  The height, in inches, you wish for the projectile to be when it crosses ZeroRange yards.
					This is usually 0 for a target zero, but could be any number.  For example if you wish
					to sight your rifle in 1.5" high at 100 yds, then you would set yIntercept to 1.5, and ZeroRange to 100
					
	Return Value:
		Returns the angle of the bore relative to the sighting system, in degrees.
*/


// A function to generate a ballistic solution table in 1 yard increments, up to __BCOMP_MAXRANGE__.
int SolveAll(int DragFunction, double DragCoefficient, double Vi, double SightHeight, \
			double ShootingAngle, double ZeroAngle, double WindSpeed, double WindAngle, double** Solution);
/* Arguments:
		DragFunction:  The drag function you wish to use for the solution (G1, G2, G3, G5, G6, G7, or G8)
		DragCoefficient:  The coefficient of drag for the projectile you wish to model.
		Vi:  The projectile initial velocity.
		SightHeight:  The height of the sighting system above the bore centerline.  
						Most scopes are in the 1.5"-2.0" range.
		ShootingAngle:  The uphill or downhill shooting angle, in degrees.  Usually 0, but can be anything from
						90 (directly up), to -90 (directly down).
		ZeroAngle:  The angle of the sighting system relative to the bore, in degrees.  This can be easily computed
					using the ZeroAngle() function documented above.
		WindSpeed:  The wind velocity, in mi/hr
		WindAngle:  The angle at which the wind is approaching from, in degrees.
					0 degrees is a straight headwind
					90 degrees is from right to left
					180 degrees is a straight tailwind
					-90 or 270 degrees is from left to right.
		Solution:	A pointer provided for accessing the solution after it has been generated.
					Memory for this pointer is allocated in the function, so the user does not need
					to worry about it.  This solution can be passed to the retrieval functions to get
					useful data from the solution.
	Return Value:
					This function returns an integer representing the maximum valid range of the
					solution.  This also indicates the maximum number of rows in the solution matrix,
					and should not be exceeded in order to avoid a memory segmentation fault.

*/


// Functions for retrieving data from a solution generated with SolveAll()
double GetRange(double* sln, int yardage); // Returns range, in yards.
double GetPath(double* sln, int yardage); // Returns projectile path, in inches, relative to the line of sight.
double GetMOA(double* sln, int yardage); // Returns an estimated elevation correction for achieving a zero at this range.
											// this is useful for "click charts" and the like.
double GetTime(double* sln, int yardage);// Returns the projectile's time of flight to this range.
double GetWindage(double* sln, int yardage); // Returns the windage correction in inches required to achieve zero at this range.
double GetWindageMOA(double* sln, int yardage); // Returns an approximate windage correction in MOA to achieve a zero at this range.
double GetVelocity(double* sln, int yardage); // Returns the projectile's total velocity (Vector product of Vx and Vy)
double GetVx(double* sln, int yardage); // Returns the velocity of the projectile in the bore direction.
double GetVy(double* sln, int yardage); // Returns the velocity of the projectile perpendicular to the bore direction.

// For very steep shooting angles, Vx can actually become what you would think of as Vy relative to the ground, 
// because Vx is referencing the bore's axis.  All computations are carried out relative to the bore's axis, and
// have very little to do with the ground's orientation.
#endif

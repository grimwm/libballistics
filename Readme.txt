GNU Ballistics Library v 1.0 - Originally created by Derek Yates

The GNU Ballistics Library is a C library created to solve exterior ballistics problems through numerical integration.  It is a lightweight, optimized library for general purpose ballistics solutions.  It is targeted in general at small arms exterior ballistics, at ranges under 5000 yards.

This library supports the standard Drag Functions (G1, G2, G3, G5, G6, G7, and G8 drag functions).


Exterior Ballistics Primer for Small Arms

Exterior ballistic problems do not generally have algebraic solutions.  The models are step-wise models, developed using complex doppler radar ranges.  Exterior ballistic models attempt to describe how a projectile behaves at a particular velocity by relating it to a "standard" projectile, which was tested i depth.

The most common drag function in use is the G1 drag function.  Virtually all published "ballistic coefficient" data in reloading manuals and product literature are G1 drag coefficients.


How to use this library:

Step 1:  Link to the library.
	#include "ballistics.h"

Step 2:  Declare a pointer for accessing solution data.
	double* solution;

Step 3 (Optional):  Use the weather correction functions to correct a standard ballistic coefficient for non-standard conditions.
	double bc=AtmCorrect(bc, 0, 29.59, 100,.7);

Step 4:  Determine initial "zero" condition for the model using ZeroAngle() function.  This is required for establishing
		a sight-in range for a rifle.  If you just wish to examine ballistics without regard to a sighting system,
		it is fine to set this to zero and directly alter the shooting angle in step 5.
		This function is provided because it is not trivial to find a good zero solution for ballistics models,
		and a highly optimized function is needed to avoid bogging down the computer.
	double zeroangle=0;
	zeroangle=ZeroAngle(G1,0.465,2750,1.6,100,0);

Step 5:  Generate a solution matrix tied to the pointer created in step 2.
	k=SolveAll(G1,bc,v,sh,angle,zeroangle,windspeed,windangle,&sln);

Step 6:  Access the solution using one of the access functions provided.
	printf("\nX: %.0f     Y: %.2f",GetRange(sln,10), GetPath(sln,10));

Step 7:  When you are done with the solution, free the memory.
	free(sln);



It is possible to have dozens of solutions open at once for comparing loads or different scenarios.  Using this library it should be fairly easy to create an excellent end-user ballistic software GUI.  The high speed solution and excellent accuracy are better than many commercial offerings.

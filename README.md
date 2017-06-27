GNU Ballistics Library
======================

Created by Derek Yates

Updated by William Grim

The GNU Ballistics Library is a C library to solve exterior ballistics problems
through numerical integration.  It is a lightweight, optimized library for
general purpose ballistics solutions.  In general, it is targeted at small
arms exterior ballistics at ranges under 5000 yards.

This library supports the standard Drag Functions: G1, G2, G3, G5, G6, G7, and G8

It is possible to have dozens of solutions in memory at once for comparing loads or
different scenarios, and using this library, it should be fairly easy to create an
excellent end-user ballistic software GUI.  The high speed solution and excellent
accuracy are better than many commercial offerings.

Exterior Ballistics Primer for Small Arms
-----------------------------------------
Exterior ballistic problems do not generally have algebraic solutions.
The models are step-wise models, developed using complex doppler radar ranges.
Exterior ballistic models attempt to describe how a projectile behaves at a
particular velocity by relating it to a "standard" projectile, which was
tested in depth.

The most common drag function in use is the G1 drag function.  Virtually all
published "ballistic coefficient" data in reloading manuals and product
literature are G1 drag coefficients.

Install
-------

Assuming you start in the directory containing the library source code, the most
basic way to build and install is with these steps:

    srcdir=$(pwd)
    mkdir ../build
    cd ../build
    cmake $srcdir
    make
    sudo make install

How to use this library
-----------------------

1. Include the library header.

	`#include <ballistics.h>`

1. Declare storage for accessing solution data.

    `struct BallisticsSolutions* solution;`

1. **Optional**: Use the weather correction functions to correct a standard ballistic
   coefficient for non-standard conditions.

    `double bc = atmosphere_correction(bc, 0, 29.59, 100,.7);`

1. Determine initial "zero" condition for the model using zero_angle() function.
   This is required for establishing a sight-in range for a rifle.  If you just
   wish to examine ballistics without regard to a sighting system, it is fine
   to set this to zero and directly alter the shooting angle in step 5.
   This function is provided because it is not trivial to find a good zero solution
   for ballistics models, and a highly optimized function is needed to avoid bogging
   down the computer.

    `double zeroangle = zero_angle(G1, 0.465, 2750, 1.6, 100, 0);`

1. Generate a solution matrix tied to the pointer created earlier.  Memory is allocated in solve().

    `k = solve(&solution, G1, bc, v, sh, angle, zeroangle, windspeed, windangle);`

1. Access the solution using one of the access functions provided.

    `printf("\nX: %.0f     Y: %.2f",solution_get_range(solution, 10), solution_get_path(solution, 10));`

1. When you are done with the solution, free the memory.

    `solution_free(solution);`

1. When building, be sure to link against *libballistics.a*.  On many linkers, this is done
   with `-lballistics`.
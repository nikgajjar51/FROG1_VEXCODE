/*
 * Include Header Files:
 *  When you want to reference a function from another file, the program will
 *  look for a "#include" inclusion of a file to search for a function
 *  But when you have several files, it can be a pain to include them all, EVERY
 *  SINGLE TIME!
 */
/*
 * #include <file.h>
 *  The brackets indicate that this is a native C++ file and should not be
 *  edited by the user.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  #include "file.h"
 *   The quotes indicate that this is a user file, not natively in C++. It also
 *   means the file is in the project directory and can be edited by the user
 *   easily.
 */

#include "v5.h"
#include "v5_vcs.h"
#include "robot-config.h"
#include "autonomous.h"
#include "user-control.h"
/*
 * Custom Defined Functions:
 *  These have been added in for the V5 project by VEXcode.
 */
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
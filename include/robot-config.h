using namespace vex;
/*
 * Including .cpp files into main.cpp:
 *  When you want to use funtions written in a .cpp file, that say has an
 *  Autonomous routine or extra functions, you first create a .h file with the
 *  same name as your .cpp (just to organize everything)
 *
 *  Then, reference classes and voids without their configuration or code: just
 *  their reference:
 *   extern device Device_Name;
 *   void function_name(void);
 *
 *  If you are wondering where "robotconfig.h" is referenced, it is in "vex.h"
 *  along with other files.
 */
extern brain Brain;
extern controller Controller1;
extern inertial inertial_sensor;
extern motor frontLeft;
extern motor backLeft;
extern motor frontRight;
extern motor backRight;
extern motor intake;
extern motor indexer;
extern motor flywheel;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern drivetrain fullDrive();
void vexcodeInit(void);
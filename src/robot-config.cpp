#include "vex.h"

using namespace vex;

/*
 * Robot Configuration
 *
 * Conventions:
 *  device Device_name = device(PORT#...);
 *
 *  device:
 *   This is the type of device you are configuring, such as a motor, vision
 *   sensor, rotation sensor, potentiometer, etc. The device is referenced in
 *   all lowercase, and is usually one string, with underscores (_) seperating
 *   words in the reference: motor, motor_group, vision, etc...
 *
 *  Device Name:
 *   Each device you configure needs a name that you can call when you want to
 *   use it. The device name cannot match the device that it is referencing,
 *   even it it is capitalized. (Exceptions are the brain and controller).
 *
 *  PORT#:
 *   Each device configured needs a Port. V5 devices,
 *   such as motors, vision sensors, and other sensors use the one of the 21 V5
 *   Smart Ports on the brain: PORT1, PORT2... PORT21
 *
 * Basics:
 *  Each robot will need an instance of the brain:
 *   brain Brain:
 *  This is a global instance of brain used for printing to the V5 brain screen.
 *
 *  Each robot will also need a controller:
 *   controller Controller# = controller(controller_ID);
 *  Since the V5 system supports 2 possible controllers, you can denote them by
 *  appending "1" and "2" to your controller name and "primary" to your main
 *  controller and "secondary" to your second controller.
 */
brain Brain;
controller Controller1 = controller(primary);

/*
 * Sensors:
 *  Most sensors just declare the port to which they are connected, such as the
 *  Inertial and Rotation sensors.
 *
 *  Some sensors, such as the Vision sensor, need extra configuration and should
 *  be configured in the "Normal" robot configuration menu.
 */
inertial inertial_sensor = inertial(PORT2);
/*
 * Motors:
 *  motor Motor_Name = motor(PORT#, Cartridge, Direction);
 *
 *  Cartridges: This sets the cartridge value in your code. Not only does this
 *  help your motors run at a set speed, but it also helps with encoders.
 *   Red (torque): ratio36_1
 *   Green (normal): ratio18_1
 *   Blue (speed): ratio6_1
 *
 *  Direction: This sets the direction for the motor. Change this if your motor
 *  does not run in it's intended direction.
 *   Forward: false
 *   Reverse: true
 */
motor frontLeft = motor(PORT1, ratio6_1, false);
motor backLeft = motor(PORT10, ratio6_1, false);
motor frontRight = motor(PORT11, ratio6_1, true);
motor backRight = motor(PORT20, ratio6_1, true);
motor intake = motor(PORT1, ratio6_1, false);
motor indexer = motor(PORT1, ratio18_1, false);
motor flywheel = motor(PORT1, ratio6_1, false);

/*
 * Motor Groups:
 *  motor_group Motor_Group_Name = motor_group(Motor_1, Motor_2, Motor_3 ...);
 *
 *  Motor groups are helpful when configuring 2 motors geared together, such as
 *  in a drivetrain or 2 motor flywheel, or even a 2 motor intake.
 *  In addition, you can group as many motors as you would like.
 */
motor_group leftDrive = motor_group(frontLeft, backLeft);
motor_group rightDrive = motor_group(frontRight, backRight);

/*
 * vexcodeInit:
 *  Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *  This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
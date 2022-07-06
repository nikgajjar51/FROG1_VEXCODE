#include "vex.h"
using namespace vex;
competition Competition;
int selectedAuton = 1;
const int SCALE = 120;
void set_tank(int l, int r) {
  frontLeft.spin(fwd, l * SCALE, voltageUnits::mV);
  backLeft.spin(fwd, l * SCALE, voltageUnits::mV);
  backRight.spin(fwd, r * SCALE, voltageUnits::mV);
  frontRight.spin(fwd, r * SCALE, voltageUnits::mV);
}
const int THRESH = 5;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  int x1 = 5;
  int y1 = 50;
  int x2 = 50;
  int y2 = 175;
  int spacing = 60;
  color selected = red;
  color unselected = blue;

  // Print 8 rectangles
  for (int i = 0; i < total_autons; i++) {
    color current_color;
    // Check if i is selectedAuton to change current_color
    if (i + 1 == selectedAuton) {
      current_color = selected;
    } else {
      current_color = unselected;
    }
    Brain.Screen.setPenColor(current_color);
    Brain.Screen.drawRectangle(x1 + (spacing * i), y1, x2, y2, current_color);
  }

  // Set font to monoM
  Brain.Screen.setFont(monoM);

  while (true) {
    int x = Brain.Screen.xPosition(); // X position of finger
    int y = Brain.Screen.yPosition(); // Y position of finger

    // Check if finger is within vertical selection of the boxes
    if (y1 < y && y < y1 + y2) {
      for (int i = 0; i < total_autons; i++) {
        // Check which x value the finger is within
        if (x1 + (spacing * i) < x && x < (spacing * (i + 1)) - x1) {
          // Change color of previously selected box to unselected
          Brain.Screen.setPenColor(unselected);
          Brain.Screen.drawRectangle(x1 + (spacing * (selectedAuton - 1)), y1,
                                     x2, y2, unselected);
          selectedAuton = i + 1; // Update selectedAuton
          // Change color of new box to selected
          Brain.Screen.setPenColor(selected);
          Brain.Screen.drawRectangle(x1 + (spacing * (selectedAuton - 1)), y1,
                                     x2, y2, selected);
        }
      }
    }

    // Print selectedAuton to brain
    Brain.Screen.setPenColor(selected);
    Brain.Screen.printAt(5, 30, "Current Auto: %d",
                         selectedAuton); // %d is a formatting character that
                                         // gets replaced with selectedAuton
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  int l_joy =
        abs(Controller1.Axis3.value()) > THRESH ? Controller1.Axis3.value() : 0;
    int r_joy =
        abs(Controller1.Axis2.value()) > THRESH ? Controller1.Axis2.value() : 0;
    set_tank(l_joy, r_joy);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

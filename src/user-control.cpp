#include "vex.h"
using namespace vex;
/*
 * drawAutonSelection():
 *  This function will draw an autonmonous selection screen on the V5 brain
 *  before autonomous and allow you to choose between as many autons as you
 *  would like.
 *
 * runSelectedAuton():
 *  checks the selected auton for a match and runs that autonomous routine.
 *
 * selectedAuton:
 *  A global variable that holds which auton should be used.
 *  It should always have a value indexing a known auton so that if the above
 *  function is skipped, it still performs an autonomous routine without
 *  selection.
 *
 * totalAutons:
 *  the total number of autons you would like to chose from.
 */
double turnStick = Controller1.Axis1.position(percent);
double driveStick = Controller1.Axis3.position(percent);
void joystickArcade() {
  if (abs(Controller1.Axis1.position()) > 10 ||
      abs(Controller1.Axis3.position()) > 10) {
    double driveVolts = Controller1.Axis3.position()*1;
    double turnVolts = Controller1.Axis1.position()*1;
    leftDrive.spin(forward, driveVolts + turnVolts, velocityUnits::pct);
    rightDrive.spin(forward, driveVolts - turnVolts, velocityUnits::pct);
  } else {
    leftDrive.spin(forward, 0, voltageUnits::volt);
    rightDrive.spin(forward, 0, voltageUnits::volt);
  }
}
void flywheelControl() {
  if (Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()) {
    indexer.spinToPosition(35, degrees, 90, velocityUnits::pct);
    indexer.spinToPosition(-110, degrees, 90, velocityUnits::pct);
  } else if (Controller1.ButtonR1.pressing()) {
    flywheel.spin(forward, 75, percent);
  } else if (Controller1.ButtonR2.pressing()) {
    flywheel.spin(forward, 100, percent);
  } else {
    flywheel.spin(fwd, 0, percent);
  }
}
void intakeControl() {
  if (Controller1.ButtonL1.pressing()) {
    intake.spin(forward, 100, percent);
  } else if (Controller1.ButtonL2.pressing()) {
    intake.spin(reverse, 100, percent);
  } else {
    intake.spin(fwd, 0, percent);
  }
}
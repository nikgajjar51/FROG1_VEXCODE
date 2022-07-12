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
int driveCurveScale = 10;
int turnCurveScale = 10;
// https://www.desmos.com/calculator/sdcgzah5ya
int curveCalculation(int input, double curveScale) {
  if (curveScale != 0) {
    return exp(-curveScale / 10) +
           exp((abs(input) - 100) / 10) * (1 - exp(-curveScale / 10)) * input;
  }
  return input;
}
void joystickArcadeCurve() {
  if (abs(Controller1.Axis1.position()) > 10 ||
      abs(Controller1.Axis3.position()) > 10) {
    double driveVolts = curveCalculation(driveStick, driveCurveScale) * 0.12;
    double turnVolts = curveCalculation(turnStick, turnCurveScale) * 0.12;
    leftDrive.spin(forward, driveVolts + turnVolts, voltageUnits::volt);
    rightDrive.spin(forward, driveVolts - turnVolts, voltageUnits::volt);
  } else {
    leftDrive.spin(fwd, 0, voltageUnits::volt);
    rightDrive.spin(fwd, 0, voltageUnits::volt);
  }
}
void joystickArcade() {
  if (abs(Controller1.Axis1.position()) > 10 ||
      abs(Controller1.Axis3.position()) > 10) {
    double driveVolts = Controller1.Axis3.position() * 0.12;
    double turnVolts = Controller1.Axis1.position() * 0.12;
    leftDrive.spin(forward, driveVolts + turnVolts, voltageUnits::volt);
    rightDrive.spin(forward, driveVolts - turnVolts, voltageUnits::volt);
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
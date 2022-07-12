#include "vex.h"
using namespace vex;
void autonomous1() {
  fullDrive.driveFor(fwd, 10, inches, 80, velocityUnits::pct);
  intake.spinFor(5, sec, 100, velocityUnits::pct);
  flywheel.spinFor(5, sec, 100, velocityUnits::pct);
  fullDrive.turnFor(45, degrees, 80, velocityUnits::pct);
  indexer.spinToPosition(30, degrees, 90, velocityUnits::pct);
}
void autonomous2() {
  // Auton here
}
void autonomous3() {
  // Auton here
}
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
 *  It should always have a value indexing a known auton so that if the
 * above function is skipped, it still performs an autonomous routine
 * without selection.
 *
 * totalAutons:
 *  the total number of autons you would like to chose from.
 */
int selectedAuton = 1;
int totalAutons = 3;
void drawAutonSelection() {
  /*
   * Variables for drawing the boxes:
   *  x1: starting x-position of rectangles
   *  y1: starting y-position of rectangles
   *  x2: length of drawn box
   *  y2: width of drawn box
   *  spacing: far apart the boxes are drawn (should be larger than x2 to
   *   prevent overlapping)
   *  color selected: color of the selected autonomous
   *  color unselected: color of the unselected autonomi
   */
  int x1 = 5;
  int y1 = 50;
  int x2 = 50;
  int y2 = 175;
  int spacing = x2 + 10;
  color selected = red;
  color unselected = blue;
  for (int i = 0; i < totalAutons; i++) {
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
    /*
     * Outputs the vertical (y) and horizontal (x) coordinates of where the
     * screen is being touched
     */
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    // Check if finger is within vertical selection of the boxes
    if (y1 < y && y < y1 + y2) {
      for (int i = 0; i < totalAutons; i++) {
        // Check which x value the finger is within
        if (x1 + (spacing * i) < x && x < (spacing * (i + 1)) - x1) {
          // Change color of previously selected box to unselected
          Brain.Screen.setPenColor(unselected);
          Brain.Screen.drawRectangle(x1 + (spacing * (selectedAuton - 1)), y1,
                                     x2, y2, unselected);
          selectedAuton = i + 1;
          // Update selectedAuton
          // Change color of new box to selected
          Brain.Screen.setPenColor(selected);
          Brain.Screen.drawRectangle(x1 + (spacing * (selectedAuton - 1)), y1,
                                     x2, y2, selected);
        }
      }
    }
    // Print selectedAuton to brain
    Brain.Screen.setPenColor(white);
    Brain.Screen.printAt(5, 30, "Current Autonomous: %d", selectedAuton);
    // %d is a formatting character that gets replaced with selectedAuton
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}
/*
 * calibrateSensors():
 *  This function holds any calibrations that need to be done
 *  They will be run at the beginning of Auton and Driver Control
 */
void calibrateSensors() {
  inertial_sensor.calibrate();
  while (indexer.torque() < .6) {
    indexer.spin(fwd, 90, velocityUnits::pct);
  }
  indexer.resetPosition();
  indexer.spinToPosition(-90, degrees, 50, velocityUnits::pct);
}
void runSelectedAuton() {
  if (selectedAuton == 1) {
    autonomous1();
  } else if (selectedAuton == 2) {
    autonomous2();
  } else if (selectedAuton == 3) {
    autonomous3();
  }
}
#include "vex.h"
using namespace vex;
void inertialPID(int finalDegrees) {
  inertial_sensor.resetHeading();
  waitUntil(!inertial_sensor.isCalibrating());
  while (finalDegrees != inertial_sensor.heading()) {
  }
}
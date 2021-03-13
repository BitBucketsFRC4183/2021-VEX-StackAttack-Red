/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sajo                                             */
/*    Created:      Wed Mar 10 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2, 3, 4      
// Vision5              vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

float DEADBAND_F = 10.01f;
float JOYSTICK_PERCENTAGE_CONVERSION_F = 1.0f;


void driveRobot() {
  if (Controller1.Axis3.position(percent) >= DEADBAND_F) {
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(forward);

  } else if (Controller1.Axis3.position(percent) <= -DEADBAND_F) {
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(reverse);

  } else {
    Drivetrain.stop();
  }
}

void turnRobot() {
  if (Controller1.Axis4.position(percent) >= DEADBAND_F) {
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(left);

  } else if (Controller1.Axis4.position(percent) <= -DEADBAND_F) {
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(right);

  } else {
    Drivetrain.stop();
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Controller1.Axis3.changed(driveRobot);
  Controller1.Axis4.changed(turnRobot);
}
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Vision5              vision        5               
// Drivetrain           drivetrain    10, 1           
// ArmMotor             motor         8               
// IntakeMotor0         motor         11              
// IntakeMotor1         motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Vision5              vision        5               
// Drivetrain           drivetrain    10, 1           
// ArmMotor             motor         8               
// IntakeMotor0         motor         3               
// IntakeMotor1         motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Vision5              vision        5               
// Drivetrain           drivetrain    10, 1           
// ArmMotor             motor         8               
// IntakeMotor0         motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Vision5              vision        5               
// Drivetrain           drivetrain    10, 1           
// ArmMotor             motor         8               
// ClawMotor            motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;
float DEADBAND_F = 10.0f;
float JOYSTICK_PERCENTAGE_CONVERSION_F = 1.0f;
float CLAW_OPEN_DEG = 45.0f;
float armSpeed = 0.5f;
bool clawOpen = false;


void driveRobot() {
  if (Controller1.Axis3.position(percent) >= DEADBAND_F) {
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(forward);

  } else if (Controller1.Axis3.position(percent) <= -DEADBAND_F) {
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(reverse);

  } else {
    Drivetrain.stop();
  }
}

void turnRobot() {
  if (Controller1.Axis4.position(percent) >= DEADBAND_F) {
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(right);

  } else if (Controller1.Axis4.position(percent) <= -DEADBAND_F) {
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(left);

  } else {
    Drivetrain.stop();
  }
}

void moveArm() {
  if (Controller1.Axis2.position(percent) >= DEADBAND_F) {
    ArmMotor.spinToPosition(ArmMotor.position(degrees) + (Controller1.Axis2.position(percent) * armSpeed), degrees);

  } else if (Controller1.Axis2.position(percent) <= -DEADBAND_F) {
    ArmMotor.spinToPosition(ArmMotor.position(degrees) + (Controller1.Axis2.position(percent) *  armSpeed), degrees);
  }
}

void useIntake() {
  if (Controller1.Axis1.position(percent) >= DEADBAND_F) {
    IntakeMotor0.setVelocity(Controller1.Axis1.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    IntakeMotor0.spin(forward);

    IntakeMotor1.setVelocity(Controller1.Axis1.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    IntakeMotor1.spin(reverse);

  } else if (Controller1.Axis1.position(percent) <= -DEADBAND_F) {
    IntakeMotor0.setVelocity(Controller1.Axis1.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    IntakeMotor0.spin(reverse);

    IntakeMotor1.setVelocity(Controller1.Axis1.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    IntakeMotor1.spin(forward);

  } else {
    IntakeMotor0.stop();
  }
}

void auton()
{
  Drivetrain.setDriveVelocity(25,percent);
  Drivetrain.drive(forward);
  wait(1, seconds);
  Drivetrain.drive(reverse);
  wait(1, seconds);
  Drivetrain.stop();
}

void manual()
{
  Controller1.Axis2.changed(moveArm);
  Controller1.Axis3.changed(driveRobot);
  Controller1.Axis4.changed(turnRobot);
  Controller1.Axis1.changed(useIntake);
}

int main() {
// Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(auton);
  Competition.drivercontrol(manual);
  while(true){
    wait(0.1, seconds);
  }
}
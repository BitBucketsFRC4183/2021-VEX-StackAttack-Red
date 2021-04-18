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
#include "vision-config.h"
#include <iostream>

using namespace vex;

competition Competition;

// The minimum distance the joystick must be from its center for the code to register it as pressed.
float DEADBAND_F = 10.0f;

// The value the joystick outputs is multiplied by this number to ensure it is on a scale of 0-100.
float JOYSTICK_PERCENTAGE_CONVERSION_F = 1.0f;

// The speed of the arm's rotation in percent
float armSpeed = 30.0f;

// The speed of the intake motors in percent
float intakeSpeed = 100.0f;

//158
double const VISION_OUTPUT_CENTER = 158;

void driveRobot() {
  // If the left joystick is pushed forward...
  if (Controller1.Axis3.position(percent) >= DEADBAND_F) {
    // Drive the robot forward.
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(forward);

  // If the left joystick is pushed backward...
  } else if (Controller1.Axis3.position(percent) <= -DEADBAND_F) {
    // Drive the robot backward.
    Drivetrain.setDriveVelocity(Controller1.Axis3.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.drive(reverse);

  } else {
    Drivetrain.stop();
  }
}

void turnRobot() {
  // If the left joystick is pushed right...
  if (Controller1.Axis4.position(percent) >= DEADBAND_F) {
    // Turn the robot right.
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(right);

  // If the left joystick is pushed left...
  } else if (Controller1.Axis4.position(percent) <= -DEADBAND_F) {
    // Turn the robot left.
    Drivetrain.setTurnVelocity(Controller1.Axis4.position(percent) * -JOYSTICK_PERCENTAGE_CONVERSION_F, percent);
    Drivetrain.turn(left);

  } else {
    Drivetrain.stop();
  }
}

void moveArm() {
  if (Controller1.ButtonL2.pressing()) {

    ArmMotor.setVelocity(armSpeed, percent);
    ArmMotor.spin(forward);

  } else if (Controller1.ButtonR2.pressing()) {
    ArmMotor.setVelocity(armSpeed, percent);
    ArmMotor.spin(reverse);
  } else {
    ArmMotor.stop(hold);
  }
}

void useIntake() {
  if (Controller1.ButtonL1.pressing()) {
    IntakeMotor0.setVelocity(intakeSpeed, percent);
    IntakeMotor0.spin(forward);

    IntakeMotor1.setVelocity(intakeSpeed, percent);
    IntakeMotor1.spin(reverse);

  } else if (Controller1.ButtonR1.pressing()) {
    IntakeMotor0.setVelocity(intakeSpeed, percent);
    IntakeMotor0.spin(reverse);

    IntakeMotor1.setVelocity(intakeSpeed, percent);
    IntakeMotor1.spin(forward);

  } else {
    IntakeMotor0.stop();
    IntakeMotor1.stop();
  }
}

// bool GreenOnRight()
// {
//   Vision13.takeSnapshot(Vision13__SIG_1);
//   // bool isGreen = Vision13.objects[0].exists;
//   double position = Vision13.objects[0].centerX;
//   return Vision13.objects[0].exists && position > VISION_OUTPUT_CENTER;
// }

void SetTheTable(){
  wait(0.001, seconds);
  Vision13.takeSnapshot(Vision13__SIG_1);
  double error = VISION_OUTPUT_CENTER - Vision13.objects[0].centerX;
  error*=0.193;
  //Green cube is on the right
  Drivetrain.turnFor(error, degrees);
  Drivetrain.driveFor(24, inches);
  Drivetrain.driveFor(reverse, 24, inches);
  Drivetrain.turnFor(right, 90-error, degrees);
  Drivetrain.driveFor(20, inches);
}

void Contingency(){
  wait(0.001, seconds);
  Drivetrain.turnFor(right, 90, degrees);
  Drivetrain.driveFor(10, inches);
}
void auton()
{
  std::cout<<"Hi"<<std::endl;
  //assume starting cube is in the middle of the eastern side of HOME, directly across recycling can (maybe one inch above recycling can sqaure?)
  //assume robot is directly to the west of the starting cube (and facing starting cube)
  // Drivetrain.setDriveVelocity(60, percent);
  Drivetrain.driveFor(forward, 27, inches);
  IntakeMotor0.setVelocity(100, percent);
  IntakeMotor0.spinFor(forward, 1, seconds);
  // Drivetrain.setDriveVelocity(50, percent);
  //should get starting cube in recycling can, completing TAKE OUT THE RECYCLING
  // IntakeMotor0.setVelocity(100, percent);
  // IntakeMotor0.spinFor(forward, 1, seconds);
  Drivetrain.driveFor(reverse, 5, inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward, 28, inches);
  Drivetrain.turnFor(right, 90, degrees);
  //originally it's 24inches, 28 for our contingency plan
  Drivetrain.driveFor(24, inches);
  //if we don't use vision:
  // Contingency();
  SetTheTable();
  //should complete GET HOME FOR DINNER
}

void manual()
{
  Controller1.Axis3.changed(driveRobot);
  Controller1.Axis4.changed(turnRobot);
  while(true){
  wait(0.01, seconds);
  moveArm();
  useIntake();
  } 
}

int main() {
// Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(auton);
  Competition.drivercontrol(manual);
  while (true){
    wait(1, seconds);
  }
}
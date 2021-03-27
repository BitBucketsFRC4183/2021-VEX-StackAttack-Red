using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern signature Vision5__SIG_1;
extern signature Vision5__SIG_2;
extern signature Vision5__SIG_3;
extern signature Vision5__SIG_4;
extern signature Vision5__SIG_5;
extern signature Vision5__SIG_6;
extern signature Vision5__SIG_7;
extern vision Vision5;
extern drivetrain Drivetrain;
extern motor ArmMotor;
extern motor IntakeMotor0;
extern motor IntakeMotor1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
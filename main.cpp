/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor2               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"


//Field definition
using namespace vex;

vex::competition    Competition;

bool reverseMode = false;
bool platformMode = false;
int deadzone = 15;
bool pEx = false;
int axis3 = 0;
int axis1 = 0;

int counter = 0;

// define your global instances of motors and other devices here

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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  rightSideAuton();
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
  // User control code here, inside the loop
  while (1) {
    //Pnuematics code
    if (Yeetroller.ButtonA.pressing()){
      counter++;
      if (counter == 1 ){
        pEx = !pEx;
        p1.set(pEx);
        p2.set(pEx);
      }
      this_thread::sleep_for(200);
    }
  
    /*
    * DRIVETRAIN CALCULATIONS
    */

    //getting controller values
    axis3 = Yeetroller.Axis3.position();
    axis1 = Yeetroller.Axis1.position();




    //reverse mode calculations
    if (Yeetroller.ButtonX.pressing()){
      reverseMode = !reverseMode;
      if (reverseMode){
        printTextCont("Reverse Mode: ON", 1);
      } else {
        printTextCont("Reverse Mode: OFF", 1);
      }
      this_thread::sleep_for(400);
    }
    if (reverseMode){
      axis3 = -axis3;
    }




    //platform mode
    if (Yeetroller.ButtonY.pressing()){
      platformMode = !platformMode;
      if (platformMode){
        printTextCont("Platform Mode: ON", 10);
      } else {
        printTextCont("Platform Mode: OFF", 10);
      }
      this_thread::sleep_for(400);
    }
    

  

    /*
    * calculating speed
    */
    // Get the velocity percentage of the left motor. (Axis3 + Axis1)
    int leftMotorSpeed =  axis3 + axis1;
    // Get the velocity percentage of the right motor. (Axis3 - Axis1)
    int rightMotorSpeed = axis3 - axis1;




    //Deadzone calculations
    if (abs(leftMotorSpeed) < deadzone){
      leftMotorSpeed = 0;
    }
    if (abs(rightMotorSpeed) < deadzone){
      rightMotorSpeed = 0;
    }




    //DRIVETRAIN CODE

    if (platformMode){
      if (leftMotorSpeed == 0 && rightMotorSpeed == 0){
        leftDriveMotor.stop(vex::brakeType::hold);
        rightDriveMotor.stop(vex::brakeType::hold);
        leftDriveMotor2.stop(vex::brakeType::hold);
        rightDriveMotor2.stop(vex::brakeType::hold);

      } else {
        leftDriveMotor.spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
        leftDriveMotor2.spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
        rightDriveMotor.spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
        rightDriveMotor2.spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
      }
    } 
    else {
      if (leftMotorSpeed == 0 && rightMotorSpeed == 0){
        leftDriveMotor.stop(vex::brakeType::brake);
        rightDriveMotor.stop(vex::brakeType::brake);
        leftDriveMotor2.stop(vex::brakeType::brake);
        rightDriveMotor2.stop(vex::brakeType::brake);

      } else {
        leftDriveMotor.spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
        leftDriveMotor2.spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
      

        rightDriveMotor.spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
        rightDriveMotor2.spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);
      }
    }
    


    //4-BAR CODE

    if (Yeetroller.ButtonR2.pressing() ) {
      leftLift.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
      rightLift.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);

    }
    else if (Yeetroller.ButtonR1.pressing()){
      leftLift.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
      rightLift.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
    }
    else {
      leftLift.stop(vex::brakeType::brake);
      rightLift.stop(vex::brakeType::brake);

    }
    if (Yeetroller.ButtonUp.pressing() ) {
    leftLift.setVelocity(50, percent);
    rightLift.setVelocity(50, percent);
    leftLift.spin(vex::directionType::fwd);
    rightLift.spin(vex::directionType::fwd);
    vex::task::sleep(200);
    leftLift.stop();
    rightLift.stop();
    }


    //FORKLIFT CODE

    if (Yeetroller.ButtonL2.pressing() ) {
      forkliftLeft.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
      forkliftRight.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
    }
    else if (Yeetroller.ButtonL1.pressing()){
      forkliftLeft.spin(vex::directionType::rev, 75, vex::velocityUnits::pct);
      forkliftRight.spin(vex::directionType::rev, 75, vex::velocityUnits::pct);
    }
    else {
      forkliftLeft.stop(vex::brakeType::brake);
      forkliftRight.stop(vex::brakeType::brake);
    }

    

    
    

    
    wait(20,msec);
    counter = 0;
  
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

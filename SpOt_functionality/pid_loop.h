// ----------------------------------------
//      pid_loop.h
//      ME14 Spring 2019
//      Author: Brittany Wylie
// ----------------------------------------
// This file includes function definitions and global variables for using the
// encoder position for the SpOt board as a process variable for PID control. It
// is general enough to accept IMU data for this process variable in producing
// a linear position.
//
//  The public functions are:
//    
//
//  Global Variables:
//    
//

//Local Includes
#include <arduino.h>


//Program Constants
#define REFRESH_PERIOD    200   //in ms
#define KP_INCREMENT      0.01
#define KI_INCREMENT      0.01
#define KD_INCREMENT      0.01

// Function Prototype Declarations
void Compute();
void SetTunings(double Kp, double Ki, double Kd);
void SetSampleTime(int NewSampleTime);
void SetOutputLimits(double Min, double Max);
void SetMode(int Mode);
void Initialize();
void SetControllerDirection(int Direction);
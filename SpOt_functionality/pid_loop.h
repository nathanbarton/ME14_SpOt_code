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
//    	  get_kp - return the current kp value (returns float)
//        get_ki - return the current ki value (returns float)
//        get_kd - return the current kd value (returns float)
//        get_setpoint - return the current setpoint value (returns float)
//
//  Global Variables:
//
//

//Local Includes
#include <arduino.h>
#include "kill_switch.h"
#include "pid_loop.h"

//Program Constants

#define KP_INCREMENT      0.01
#define KI_INCREMENT      0.01
#define KD_INCREMENT      0.01
#define REFRESH_PERIOD 	  200 //ms

#define MANUAL 0
#define AUTOMATIC 1

#define DIRECT 0
#define REVERSE 1

// Function Prototype Declarations
float Compute();
void SetTunings(float Kp, float Ki, float Kd);
void Setpoint_set(float newpoint);
void SetOutputLimits(float Min, float Max);
void SetMode(int Mode);
void Initialize(float currentState);
void Setpoint_set(float newpoint);

float get_kp(void);
float get_ki(void);
float get_kd(void);
float get_setpoint(void);

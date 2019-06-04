// ----------------------------------------
//      pid_loop.cpp
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
//  Global Variables:


//Local Includes
#include "pid_loop.h"
// Global Variables
extern volatile long encoderPosition; //current pulse count
float linearPosition = 0; //Normalized linear position along a ramp

// Procedure:			
// Description:		
// Special Notes:		
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

void linear_position_set()
{
  linearPosition = ((((encoderPosition / PULSES_PER_ROTATION)
                        /INTERNAL_MOTOR_GEARING)/PULLEY_GEAR_RATIO)
                         * 2 * PI * SPOOL_RADIUS);
}
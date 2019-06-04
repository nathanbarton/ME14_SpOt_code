// ----------------------------------------
//      linear_position.cpp
//      ME14 Spring 2019
//      Author: Maheck Jerez Terceros
// ----------------------------------------
// This file includes function definitions and global variables for using the
// encoder position for the SpOt board as a process variable for PID control. It
// is general enough to accept IMU data for this process variable in producing
// a linear position.
//
//  The public functions are:
//		encoder_init - configure encoder pins for input and attach encoder pin ISR
//		encoder_position_set - set encoder position to a specified value
//
//  Global Variables:
//		encoderPosition (long) - absolute encoder position in terms of encoder pulses
//								 (16 pulses per motor revolution, before gearbox)
//
//
//  Revision History:
//     2019-06-02   Maheck Jerez Terceros      Initial revision
//     2019-06-03   Maheck Jerez Terceros      Legibility changes
//     2019-06-03   Maheck Jerez Terceros      get function changes

//Local Includes
#include "linear_position.h"
// Global Variables
extern volatile long encoderPosition; //current pulse count


// Procedure:			linear_position_set
// Description:		calculates the linear position to be used in PID (flaot)
// Special Notes:		None.
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-06-02

void linear_position_get()
{
  return (((((float)encoderPosition / PULSES_PER_ROTATION)
                        /INTERNAL_MOTOR_GEARING)/PULLEY_GEAR_RATIO)
                         * 2 * PI * SPOOL_RADIUS);
  }

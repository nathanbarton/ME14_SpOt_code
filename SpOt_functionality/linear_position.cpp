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
//    linPosition (long) - process variable to be used for the PID control loop,
//                 linear position along ramp to be maintained
//
//
//  Revision History:
//     2019-06-02   Maheck Jerez Terceros      Initial revision

//Local Includes
#include <arduino.h>
#include "linear_position.h"

//Program Constants
#define spool_Radius = 5   // The radius of the wheels for SpOt
#define maximum_Position = 200 // The total length of the ramp

// Global Variables
extern volatile long encoderPosition; //current pulse count
long linearPosition = 0; //Normalized linear position along a ramp

// Procedure:			linear_position_set
// Description:		Sets the linear position to be used in PID
// Special Notes:		None.
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-05-28
void linear_position_set()
{
  linearPosition = ((encoderPosition / 16) * 2 * PI * spool_Radius)/maximum_Position
}

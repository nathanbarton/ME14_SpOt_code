// ----------------------------------------
//      linear_position.h
//      ME14 Spring 2019
//      Author: Maheck Jerez Terceros
// ----------------------------------------
// This file includes function prototype declarations for monitoring the motor encoder
//   on the SpOt drive PCB for the ME14 spool robot project.
//
//  The public functions are:
//		linear_position_set - set linear position to a specified value based on
//                          encoder/IMU
//
//  Global Variables:
//		encoderPosition (long) - absolute encoder position in terms of encoder pulses
//								 (16 pulses per motor revolution, before gearbox)
//
//  Known Bugs/Limitations:	Encoder only reads 1/4 of max encoder resolution by only
//							looking at rising edge of one encoder pin A
//
//  Revision History:
//     2019-05-28   Nathan T Barton      Initial revision

//Local Includes
#include <arduino.h>


//Program Constants
#define spool_Radius = 5   // The radius of the wheels for SpOt
#define maximum_Position = 200 // The total length of the ramp

// Function Prototype Declarations
void linear_position_set()

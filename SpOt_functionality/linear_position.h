// ----------------------------------------
//      linear_position.h
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
//     2019-06-03   Maheck Jerez Terceros      Legibility revision

//Local Includes
#include <arduino.h>


//Program Constants
#define SPOOL_RADIUS		 5     // The radius of the wheels for SpOt (inches)
#define INTERNAL_MOTOR_GEARING	 30   // Gear Ratio inside Pololu motor (30:1)
#define PULLEY_GEAR_RATIO   3   // Pulley Ratio (3:1)
#define MAXIMUM_LENGTH    200   // Maximum Length of ramp
#define PULSES_PER_ROTATION   16 // Number of pulses registered by encoder for a
//                                 full rotation
// Function Prototype Declarations
void linear_position_set();

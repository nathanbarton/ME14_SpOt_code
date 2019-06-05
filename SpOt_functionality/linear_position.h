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
//
//		linear_position_get - caluclates and returns the linear positoin of SpOt
//
//  Global Variables:

//
//
//  Revision History:
//     2019-06-02   Maheck Jerez Terceros      Initial revision
//     2019-06-03   Maheck Jerez Terceros      Legibility revision
//     2019-06-04   Maheck Jerez Terceros      function name change

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
float linear_position_get();

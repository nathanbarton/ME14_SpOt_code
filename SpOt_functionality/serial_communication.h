// ----------------------------------------
//      serial_communication.h
//      ME14 Spring 2019
//      Author: Mike Brown
// ----------------------------------------
//  This file includes function definitions for reading SpOt's serial communication.
//
//  The public functions are:
//		parse_serial - Read communication from the serial port
//
//  The public variables are:
//
//  Known Bugs/Limitations:	
//
//  Revision History:
//     2019-06-03   Mike Brown      Initial revision
//     2019-06-04   Mike Brown      Added changing PID setpoint

//local includes
#include <arduino.h>
#include "SpOt_board.h"
#include "pid_loop.h"
#include "kill_switch.h"

// -------------------------------
// Program Constants
// -------------------------------
// list of SpOt commands
#define INCREASE_KP 'p'
#define DECREASE_KP 'o'
#define INCREASE_KI 'i'
#define DECREASE_KI 'u'
#define INCREASE_KD 'd'
#define DECREASE_KD 'f'
#define KILL       ' '   // command to activate kill switch
#define RESET      'r'   // command to activate kill reset
#define INCREASE_SETPOINT 's'
#define DECREASE_SETPOINT 'x'
#define KP_INCREMENT      0.01  // amount to increase/decrease proportional gain
#define KI_INCREMENT      0.01  // amount to increase/decrease integral gain
#define KD_INCREMENT      0.01  // amount to increase/decrease derivative gain
#define SETPOINT_INCREMENT 10.0 // amount to increase/decrease setpoint value

// -------------------------------
// Function Prototype Declarations
// -------------------------------
//public functions
void parse_serial(char serialValue);
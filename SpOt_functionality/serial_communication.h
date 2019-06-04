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
//    motorCurrent (int) - Current level of the motor.
//    kp, ki, kd (double) - Gain values for the P, I, and D terms, respectively.
//    cmd_received (bool) - Flag signalling when the serial command has been received.
//    MAX_CURRENT (int) - Maximum current command that can be sent to motor.
//    CURRENT_INCREMENT (int) - Value that motorCurrent can increase/decrease by.
//    KP_INCREMENT, KI_INCREMENT, KD_INCREMENT (double) - Value that kp, ki, and kd
//                  can increase/decrease by, respectively.
//    Setpoint (double) - Desired setpoint for the PID loop.
//    SETPOINT_INCREMENT (double) - Value that the setpoint can increase/decrease by.
//
//  Known Bugs/Limitations:	What if String is passed into parse_serial instead of char?
//
//  Revision History:
//     2019-06-03   Mike Brown      Initial revision
//     2019-06-04   Mike Brown      Added changing PID setpoint

//local includes
#include <arduino.h>
#include "SpOt_board.h"

// -------------------------------
// Program Constants
// -------------------------------
// list of SpOt commands
#define INCREASE_CURRENT 'q'
#define DECREASE_CURRENT 'a'
#define STOP '0'         // command to set motor current to zero, but not activate kill switch
#define INCREASE_KP 'p'
#define DECREASE_KP 'o'
#define INCREASE_KI 'i'
#define DECREASE_KI 'u'
#define INCREASE_KD 'd'
#define DECREASE_KD 'f'
#define KILL       'k'   // command to activate kill switch
#define INCREASE_SETPOINT 's'
#define DECREASE_SETPOINT 'x'

// -------------------------------
// Function Prototype Declarations
// -------------------------------
//public functions
void parse_serial(char serialValue);
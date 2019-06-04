// ----------------------------------------
//      serial_communication.cpp
//      ME14 Spring 2019
//      Author: Mike Brown
// ----------------------------------------
//  This file includes function definitions for reading SpOt's serial communication.
//
//  The public functions are:
//		parse_serial - Read communication from the serial port
//
//  The public variables are:
//    kp, ki, kd (double) - Gain values for the P, I, and D terms, respectively.
//    cmd_received (bool) - Flag signalling when the serial command has been received.
//    Setpoint (double) - Desired setpoint for the PID loop.
//
//  Known Bugs/Limitations:	What if String is passed into parse_serial instead of char?
//
//  Revision History:
//     2019-06-03   Mike Brown      Initial revision
//     2019-06-04   Mike Brown      Added changing PID setpoint
//     2019-06-04   Mike Brown      Removed direct user motor control, 

#include "serial_communication.h"

extern double kp, ki, kd;
extern bool cmd_received;
extern double Setpoint;

// --------------------------------------------------------------------------------
// Procedure:			parse_serial
// Description:			This procedure parses the robot's serial commands, including updated PID 
//                              gain values, stop/kill commands, and changing robot's setpoint.
// Arguments:			serialValue (char) - Character received by the Serial port 
// Return Values:		None.
// Data Structures:		None.
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		None.
//
// Author:			Mike Brown
// Last Modified:	2019-06-04
void parse_serial(char serialValue)
{
    if(serialValue == STOP)
    {
      //set current to 0
      motorCurrent = 0;
    }
    if(serialValue == INCREASE_KP) 
    {
      //increase proportional gain
  	  kp += KP_INCREMENT;
    }
    if(serialValue == DECREASE_KP) 
    {
      //decrease proportional gain
  	  kp -= KP_INCREMENT;
    }
    if(serialValue == INCREASE_KI) 
    {
      //increase integral gain
  	  ki += KI_INCREMENT;
    }
    if(serialValue == DECREASE_KI) 
    {
      //decrease integral gain
  	  ki -= KI_INCREMENT;
    }
    if(serialValue == INCREASE_KD) 
    {
      //increase derivative gain
  	  kd += KD_INCREMENT;
    }
    if(serialValue == DECREASE_KD) 
    {
      //decrease derivative gain
  	  kd -= KD_INCREMENT;
    }
    if(serialValue == KILL) 
    {
      // enter kill switch function 
      // < insert kill function call, when kill function is created >
    }
    if(serialValue == INCREASE_SETPOINT) 
    {
      //increase derivative gain
      Setpoint += SETPOINT_INCREMENT;
    }
    if(serialValue == DECREASE_SETPOINT) 
    {
      //decrease derivative gain
      Setpoint -= SETPOINT_INCREMENT;
    }
    
    //set flag for command received LED
    cmd_received = true;

}
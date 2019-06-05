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
//    Setpoint (double) - Desired setpoint for the PID loop.
//
//  Known Bugs/Limitations:	What if String is passed into parse_serial instead of char?
//
//  Revision History:
//     2019-06-03   Mike Brown      Initial revision
//     2019-06-04   Mike Brown      Added changing PID setpoint, removed user direct motor control

#include "serial_communication.h"


// --------------------------------------------------------------------------------
// Procedure:			parse_serial
// Description:			This procedure parses the robot's serial commands, including updated PID
//                              gain values, stop/kill commands, and changing robot's setpoint.
// Arguments:			serialValue (char) - Character received by the Serial port
// Return Values:		None.
// Data Structures:	None.
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		None.
//
// Author:			Mike Brown
// Last Modified:	2019-06-04
void parse_serial(char serialValue)
{
    // change function names below when get functions are added in pid_loop.cpp
    float setpoint = get_setpoint();
    float kp = get_kp();
    float ki = get_ki();
    float kd = get_kd();

    if(serialValue == INCREASE_KP)
    {
      //increase proportional gain
  	  kp += KP_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == DECREASE_KP)
    {
      //decrease proportional gain
  	  kp -= KP_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == INCREASE_KI)
    {
      //increase integral gain
  	  ki += KI_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == DECREASE_KI)
    {
      //decrease integral gain
  	  ki -= KI_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == INCREASE_KD)
    {
      //increase derivative gain
  	  kd += KD_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == DECREASE_KD)
    {
      //decrease derivative gain
  	  kd -= KD_INCREMENT;
      SetTunings(kp, ki, kd);
    }
    if(serialValue == KILL)
    {
      // enter kill switch function
      kill();
    }
    if(serialValue == RESET)
    {
      // enter kill switch function
      kill_reset();
    }
    if(serialValue == INCREASE_SETPOINT)
    {
      //increase derivative gain
      setpoint += SETPOINT_INCREMENT;
      Setpoint_set(setpoint);
    }
    if(serialValue == DECREASE_SETPOINT)
    {
      //decrease derivative gain
      setpoint -= SETPOINT_INCREMENT;
      Setpoint_set(setpoint);
    }



}

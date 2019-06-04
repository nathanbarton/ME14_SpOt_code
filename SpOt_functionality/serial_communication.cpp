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
//    motorCurrent (int) - Current level of the motor.
//    kp, ki, kd (double) - Gain values for the P, I, and D terms, respectively.
//    cmd_received (bool) - Flag signalling when the serial command has been received.
//    MAX_CURRENT (int) - Maximum current command that can be sent to motor.
//    CURRENT_INCREMENT (int) - Value that motorCurrent can increase/decrease by.
//    KP_INCREMENT, KI_INCREMENT, KD_INCREMENT (double) - Value that kp, ki, and kd
//                  can increase/decrease by, respectively.
//
//  Known Bugs/Limitations:	None.
//
//  Revision History:
//     2019-06-03   Mike Brown      Initial revision

#include "serial_communication.h"

extern double kp, ki, kd;
extern int motorCurrent;
extern bool cmd_received;
extern int MAX_CURRENT;
extern int CURRENT_INCREMENT;
extern double KP_INCREMENT, KI_INCREMENT, KD_INCREMENT;

// --------------------------------------------------------------------------------
// Procedure:			parse_serial
// Description:			This procedure parses the robot's serial commands, including 
//							updated motor current, updated PID gain values, and stop commands.
// Arguments:			serialValue (char) - Character received by the Serial port 
// Return Values:		None.
// Data Structures:		None.
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		None.
//
// Author:			Mike Brown
// Last Modified:	2019-06-03
void parse_serial(char serialValue)
{
    //parse read value 
    if(serialValue == INCREASE_CURRENT && motorCurrent < MAX_CURRENT )
    {
      //increase current
      motorCurrent += CURRENT_INCREMENT;
    }
    if(serialValue == DECREASE_CURRENT && motorCurrent > (MAX_CURRENT *(-1)))
    {
      //decrease current
      motorCurrent -= CURRENT_INCREMENT;
    }
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

    //update motor current output
    set_motor_current(motorCurrent);
    
    //set flag for command received LED
    cmd_received = true;
  

}
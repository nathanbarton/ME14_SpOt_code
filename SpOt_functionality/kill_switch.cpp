// ----------------------------------------
//      kill_switch.cpp
//      ME14 Spring 2019
//      Author: Brittany Wylie
// ----------------------------------------
// This file includes function definitions and global variables stopping all
// functionality on the SpOt for safety purposes
//
//  The public functions are:
//  Kill()
//
//  Global Variables:
//
//
#include "kill_switch.h"
// --------------------------------------------------------------------------------
// Procedure:			Kill
// Description:			Disables motor controller in emergency
// Limitations:			Relies on disabling motor controller to stop everything
// Special Notes:	  Leaves PID constants untouched
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-06-04
void kill(){
  set_motor_current(0);
  motor_control_disable();
}

// --------------------------------------------------------------------------------
// Procedure:			Reset
// Description:			Resets system in order to return to normal operation
// Limitations:			Relies on disabling motor controller to stop everything
// Special Notes:	  Leaves PID constants untouched
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-06-04
void reset(){

  motor_control_enable();

}

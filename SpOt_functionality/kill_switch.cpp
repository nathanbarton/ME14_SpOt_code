// ----------------------------------------
//      kill_switch.cpp
//      ME14 Spring 2019
//      Author: Maheck Jerez Terceros
// ----------------------------------------
// This file includes function definitions and global variables stopping all
// functionality on the SpOt for safety purposes
//
//  The public functions are:
//  kill()
//  reset()
//
#include "kill_switch.h"
// Global variables
extern volatile long encoderPosition;

//  Local Variables:
bool activeState = true;
//
//

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
  #ifdef USE_IMU
    SetMode(MANUAL, linear_position_get(encoderPosition, get_angle()));
  #else
    SetMode(MANUAL, linear_position_get(encoderPosition));
  #endif
  activeState = false;
}

// --------------------------------------------------------------------------------
// Procedure:			kill_reset
// Description:			Resets system in order to return to normal operation
// Limitations:			Relies on disabling motor controller to stop everything
// Special Notes:	  Leaves PID constants untouched
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-06-04
void kill_reset(){

  #ifdef USE_IMU
    SetMode(MANUAL, linear_position_get(encoderPosition, get_angle()));
  #else
    Setpoint_set(linear_position_get(encoderPosition));
  #endif
  
  motor_control_enable();

  #ifdef USE_IMU
    SetMode(AUTOMATIC, linear_position_get(encoderPosition, get_angle()));
  #else
    SetMode(AUTOMATIC, linear_position_get(encoderPosition));
  #endif
  
  
  activeState = true;

}

bool get_activeState(){
  return activeState;
}

// ----------------------------------------
//      pid_loop.cpp
//      ME14 Spring 2019
//      Author: Brittany Wylie
// ----------------------------------------
// This file includes function definitions and global variables for using the
// encoder position for the SpOt board as a process variable for PID control. It
// is general enough to accept IMU data for this process variable in producing
// a linear position.
//
//  The public functions are:
//        get_kp - return the current kp value (returns float)
//        get_ki - return the current ki value (returns float)
//        get_kd - return the current kd value (returns float)
//        get_setpoint - return the current setpoint value (returns float)
//
//  Global Variables:


//Local Includes
#include "pid_loop.h"

// Procedure:
// Description:
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

/*working variables*/
unsigned long lastTime;
float Input, Output, Setpoint;
float ITerm, lastInput;
float kp, ki, kd;
float outMin, outMax;
bool inAuto = false;
int controllerDirection = DIRECT;



 // Procedure:	Call compute at some interval in the
// main loop to calculate Kp, Kd, Ki values
// Description:		Computes values for kp, ki, kd
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

float Compute(float currentState)
{
   Input = currentState;
   if(!inAuto) return 0;
   unsigned long now = millis();
   int timeChange = (now - lastTime);
   if(timeChange>=REFRESH_PERIOD)
   {
      /*Compute all the working error variables*/
      float error = Setpoint - Input;
      ITerm += (ki * error);
      if(ITerm > outMax) ITerm= outMax;
      else if(ITerm < outMin) ITerm= outMin;
      float dInput = (Input - lastInput);

      /*Compute PID Output*/
      Output = kp * error + ITerm- kd * dInput;

      if(Output > outMax) Output = outMax;
      else if(Output < outMin) Output = outMin;

      /*Remember some variables for next time*/
      lastInput = Input;
      lastTime = now;
      /*Returns current state*/
      return Output;
   }
}



 // Procedure:
// Description:		sets the values of kp, ki, kd
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetTunings(float Kp, float Ki, float Kd)
{
   if (Kp<0 || Ki<0|| Kd<0) return;

  float SampleTimeInSec = ((float)REFRESH_PERIOD)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;

  if(controllerDirection ==REVERSE)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
}

// Procedure:
// Description:
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetOutputLimits(float Min, float Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;
}

// Procedure:
// Description: Allows user to turn PID loop on and off
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetMode(int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto == !inAuto)
    {  /*we just went from manual to auto*/
        Initialize();
    }
    inAuto = newAuto;
}

// Procedure:
// Description:
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

void Initialize(float currentState)
{
   Input = currentState;
   lastInput = Input;
   ITerm = Output;
   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
}

// Procedure:	Set the new Setpoint for use in PID Loop
// Description:		Implements a check at 50 feet to cap setpoint distance
// Special Notes:
//
// Author:			Maheck Jerez Terceros
// Last Modified:	2019-06-04

void Setpoint_set(float newpoint){
  if(newpoint> SETPOINT_CAP) {
    Setpoint = SETPOINT_CAP;    //units are in Inches, 600 in -> 50 ft cap 
  }
  else{
   Setpoint = newpoint;
  }
}


//Get functions
float get_kp(void)
{
  return kp;
}

float get_ki(void)
{
  return ki;
}

float get_kd(void)
{
  return kd;
}

float get_setpoint(void)
{
  return Setpoint;
}

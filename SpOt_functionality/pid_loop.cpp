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
//        get_kp - return the current kp value (returns double)
//        get_ki - return the current ki value (returns double)
//        get_kd - return the current kd value (returns double)
//        get_setpoint - return the current setpoint value (returns double)
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
double Input, Output, Setpoint;
double ITerm, lastInput;
double kp, ki, kd;
int SampleTime = 1000; //1 sec
double outMin, outMax;
bool inAuto = false;
 
#define MANUAL 0
#define AUTOMATIC 1
 
#define DIRECT 0
#define REVERSE 1
int controllerDirection = DIRECT;

 // Procedure:			
// Description:		
// Special Notes:		
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

void Compute()
{
   if(!inAuto) return;
   unsigned long now = millis();
   int timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {
      /*Compute all the working error variables*/
      double error = Setpoint - Input;
      ITerm+= (ki * error);
      if(ITerm > outMax) ITerm= outMax;
      else if(ITerm < outMin) ITerm= outMin;
      double dInput = (Input - lastInput);
 
      /*Compute PID Output*/
      Output = kp * error + ITerm- kd * dInput;
      if(Output > outMax) Output = outMax;
      else if(Output < outMin) Output = outMin;
 
      /*Remember some variables for next time*/
      lastInput = Input;
      lastTime = now;
   }
}
 
 // Procedure:			
// Description:		
// Special Notes:		
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetTunings(double Kp, double Ki, double Kd)
{
   if (Kp<0 || Ki<0|| Kd<0) return;
 
  double SampleTimeInSec = ((double)SampleTime)/1000;
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

void SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
                      / (double)SampleTime;
      ki *= ratio;
      kd /= ratio;
      SampleTime = (unsigned long)NewSampleTime;
   }
}

// Procedure:			
// Description:		
// Special Notes:		
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetOutputLimits(double Min, double Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;
 
   if(Output > outMax) Output = outMax;
   else if(Output < outMin) Output = outMin;
 
   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
}

// Procedure:			
// Description:		
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
 
void Initialize()
{
   lastInput = Input;
   ITerm = Output;
   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
}

// Procedure:			
// Description:		
// Special Notes:		
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02

void SetControllerDirection(int Direction)
{
   controllerDirection = Direction;
}

// Procedure: get_kp 
// Description:   
// Special Notes: Returns double
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_kp(void) 
{
  return kp;
}

// Procedure: get_ki   
// Description:   
// Special Notes: Returns double 
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_ki(void) 
{
  return ki;
}

// Procedure: get_kd  
// Description:   
// Special Notes: Returns double
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_kd(void) 
{
  return kd;
}

// Procedure: get_setpoint  
// Description:   
// Special Notes: Returns double 
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_setpoint(void) 
{
  return Setpoint;
}
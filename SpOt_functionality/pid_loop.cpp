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


 // Procedure:	Call compute at some interval in the
// main loop to calculate Kp, Kd, Ki values
// Description:		Computes values for kp, ki, kd
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-02
void Setpoint_set(float newpoint){
  if(newpoint> 600) {
    Setpoint = 600;
  }
  else{
   Setpoint = newpoint
  }
}
void Compute()
{
   if(!inAuto) return;
   unsigned long now = millis();
   int timeChange = (now - lastTime);
   if(timeChange>=REFRESH_PERIOD)
   {
      /*Compute all the working error variables*/
      float error = Setpoint - Input;
      ITerm += (ki * error);
      if(ITerm > outMax) ITerm= outMax;
      else if(ITerm < outMin) ITerm= outMin;
<<<<<<< HEAD
      double dInput = (Input - lastInput);

=======
      float dInput = (Input - lastInput);
 
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
      /*Compute PID Output*/
      Output = kp * error + ITerm- kd * dInput;

      if(Output > outMax) Output = outMax;
      else if(Output < outMin) Output = outMin;

      /*Remember some variables for next time*/
      lastInput = Input;
      lastTime = now;
   }
}


<<<<<<< HEAD

 // Procedure:
=======
 
// Procedure:			
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
// Description:		sets the values of kp, ki, kd
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04

void SetTunings(float Kp, float Ki, float Kd)
{
   if (Kp<0 || Ki<0|| Kd<0) return;
<<<<<<< HEAD

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
// Description:		changes the rate of sampling
// Special Notes:
//
// Author:			Brittany Wylie
// Last Modified:	2019-06-04
=======
 
  float SampleTimeInSec = ((float)(millis()-lastTime))/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;
 

}

>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9


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

   if(Output > outMax) Output = outMax;
   else if(Output < outMin) Output = outMin;

   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
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

void Initialize()
{
   lastInput = Input;
   ITerm = Output;
   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
}

<<<<<<< HEAD
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
=======

// Procedure: get_kp 
// Description:   
// Special Notes: Returns float
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
float get_kp(void) 
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
{
  return kp;
}

<<<<<<< HEAD
// Procedure: get_ki
// Description:
// Special Notes: Returns double
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_ki(void)
=======
// Procedure: get_ki   
// Description:   
// Special Notes: Returns float 
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
float get_ki(void) 
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
{
  return ki;
}

<<<<<<< HEAD
// Procedure: get_kd
// Description:
// Special Notes: Returns double
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_kd(void)
=======
// Procedure: get_kd  
// Description:   
// Special Notes: Returns float
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
float get_kd(void) 
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
{
  return kd;
}

<<<<<<< HEAD
// Procedure: get_setpoint
// Description:
// Special Notes: Returns double
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
double get_setpoint(void)
=======
// Procedure: get_setpoint  
// Description:   
// Special Notes: Returns float 
//
// Author:      Mike Brown
// Last Modified: 2019-06-04
float get_setpoint(void) 
>>>>>>> b12bf39187589d0acb83a3598b0020aa3e87b8d9
{
  return Setpoint;
}

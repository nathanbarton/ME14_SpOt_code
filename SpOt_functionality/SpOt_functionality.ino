// ----------------------------------------
//      SpOt_functionality
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This program demonstrates the control loop functionality of the SpOt robot for
//    ME14.  The program sets the linear position setpoint based on serial input received
//    from an HC-05 bluetooth module.  
//
//
//  Revision History:
//     2019-06-04   Nathan T Barton      Initial revision

#include "SpOt_board.h"
#include "motor_control.h"
#include "encoder_position.h"
#include "pid_loop.h"
#include "serial_communication.h"

//global constants
#define BAUD_RATE               115200  //for serial communication
#define SCREEN_REFRESH_PERIOD   250     //in ms

//global variables
extern volatile long encoderPosition;   //updated by ISR in encoder_position file



void setup()
{
  //initialize motor controller
  motor_control_init();    //initialize pins
  set_motor_current(motorCurrent);  //set motor current to 0 initially
  motor_control_enable();

  //initialize serial peripheral
  Serial1.begin(BAUD_RATE);
  
  //set up encoder
  encoder_init();
  //initialize encoder position
  encoder_position_set(0);
  
}


void loop()
{
  //check if a serial character is available
  if(Serial1.available() > 0)
  {
    //read incoming data and parse it
    char serialValue = Serial1.read();
    parse_serial(serialValue);
  }





  
}

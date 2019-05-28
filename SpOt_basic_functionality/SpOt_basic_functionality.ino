// ----------------------------------------
//      SpOt_basic_functionality
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This program demonstrates the basic functionality of the SpOt robot for
//    ME14.  The program sets the motor current based on serial input received
//    from an HC-05 bluetooth module.  
//
//  Serial Commands:
//    q     - increment motor current
//    a     - decrement motor current
//    space - set motor current to 0
//
//  Revision History:
//     2019-05-26   Nathan T Barton      Initial revision

#include "SpOt_board.h"
#include "motor_control.h"

//global constants
#define MAX_SPEED         75
#define SPEED_INCREMENT   5
#define REFRESH_PERIOD    200

//global variables
int serialValue = 0;    //holds the character last received from serial
int motorSpeed = 0;     //current motor speed

unsigned long lastRefreshTime = 0;   //time since periodic serial output has been refreshed
bool led_state = false;   //boolean for blinking status LED to show that the code is running



void setup() {
  //initialize motor controller
  motor_control_init();    //initialize pins
  set_motor_current(motorSpeed);  //set motor speed to 0 initially
  motor_control_enable();
  
  Serial1.begin(9600);

  //setup status LED
  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_2, HIGH);
  
}

void loop() {

  //check if a serial character is available
  if(Serial1.available() > 0)
  {
    //read incoming data
    serialValue = Serial1.read();
    //parse read value 
    if(serialValue == 'q' && motorSpeed < MAX_SPEED)
    {
      //increase speed
      motorSpeed += SPEED_INCREMENT;
    }
    if(serialValue == 'a' && motorSpeed > (MAX_SPEED*(-1)))
    {
      //decrease speed
      motorSpeed -= SPEED_INCREMENT;
    }
    if(serialValue == ' ')
    {
      //set speed to 0
      motorSpeed = 0;
    }

    set_motor_current(motorSpeed);
  }

  //check if time to refresh display
  if(millis()-lastRefreshTime >= REFRESH_PERIOD)
  {
    lastRefreshTime += REFRESH_PERIOD;
    //output current motor speed
    Serial1.print("\033[2J");
    Serial1.print("motor power level: ");
    Serial1.print(motorSpeed);
    Serial1.print("\r");

    //set motor power level (ensure that no discrepancy exists between output pins and motorSpeed)
    set_motor_current(motorSpeed);

    //toggle the LED
    if(led_state == false)
    {
      led_state = true;
      digitalWrite(PIN_LED_2, HIGH);
    }
    else
    {
      led_state = false;
      digitalWrite(PIN_LED_2, LOW);
    }
   
    
  }
  

  
}

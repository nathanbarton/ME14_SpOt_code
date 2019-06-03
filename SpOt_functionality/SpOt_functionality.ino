// ----------------------------------------
//      SpOt_functionality
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
//     2019-05-28   Nathan T Barton      added motor speed calculation
//     2019-05-28   Nathan T Barton      refactored motorSpeed to motorCurrent to better reflect purpose
//     2019-05-28   Nathan T Barton      added command received status LED

#include "SpOt_board.h"
#include "motor_control.h"
#include "encoder_position.h"

//global constants
#define MAX_CURRENT         100
#define CURRENT_INCREMENT   5
#define REFRESH_PERIOD    200   //in ms
#define BAUD_RATE         115200

#define ENCODER_CPR       16*30

//global variables
int serialValue = 0;    //holds the character last received from serial
int motorCurrent = 0;     //present motor current


double kp, ki, kd;
double Input, Output, Setpoint;
double ITerm, lastInput;

extern volatile long encoderPosition;

unsigned long lastRefreshTime = 0;   //time since periodic serial output has been refreshed
bool led_state = false;   //boolean for blinking status LED to show that the code is running
long lastEncoderPosition = 0;  //for calculating motor speed
bool cmd_received = false;  //boolean for blinking command received LED


void setup() {
  //initialize motor controller
  motor_control_init();    //initialize pins
  set_motor_current(motorCurrent);  //set motor current to 0 initially
  motor_control_enable();
  
  Serial1.begin(BAUD_RATE);

  //setup status LEDs
  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_2, HIGH);
  pinMode(PIN_LED_3, OUTPUT);

  //set up encoder
  encoder_init();
  //initialize encoder position
  encoder_position_set(0);
  
}

void Compute()
{
  //might not be necessary to include following if statement
  
  double error = Setpoint - Input;

  ITerm += (ki * error);
  double dInput = Input - lastInput;
  double dErr = (error - lastErr) ;

  //PID output computation
  Output = kp*error + ki * ITerm + kd * dInput;

  //
  lastInput = Input;
  lastTime = millis();

}

void SetTunings(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)REFRESH_PERIOD)/1000;

  kp = Kp;
  ki = Ki * SampleTimeInSec;
  kd = Kd / SampleTimeInSec;
}

void loop() {

  //check if a serial character is available
  if(Serial1.available() > 0)
  {
    //read incoming data
    serialValue = Serial1.read();
    //parse read value 
    if(serialValue == 'q' && motorCurrent < MAX_CURRENT )
    {
      //increase current
      motorCurrent += CURRENT_INCREMENT;
    }
    if(serialValue == 'a' && motorCurrent > (MAX_CURRENT *(-1)))
    {
      //decrease current
      motorCurrent -= CURRENT_INCREMENT;
    }
    if(serialValue == ' ')
    {
      //set current to 0
      motorCurrent = 0;
    }

    //update motor current output
    set_motor_current(motorCurrent);
    
    //set flag for command received LED
    cmd_received = true;
  }

  //check if time to refresh display
  if(millis()-lastRefreshTime >= REFRESH_PERIOD)
  {
    lastRefreshTime += REFRESH_PERIOD;
    
    //calculate motor speed (in RPM)
    float motorSpeed;
    motorSpeed = ((float)encoderPosition-(float)lastEncoderPosition)/(ENCODER_CPR)/ REFRESH_PERIOD*1000*60;
    lastEncoderPosition = encoderPosition;
    
    //output current motor power level
    Serial1.print("\033[2J");
    Serial1.print("motor power level: ");
    Serial1.print(motorCurrent);
    Serial1.print("\r\n");
    //output current motor speed and position
    Serial1.print("motor position: ");
    Serial1.print(encoderPosition);
    Serial1.print("\r\n");
    Serial1.print("motor speed: ");
    Serial1.print(motorSpeed);    
    Serial1.print("\r\n");

    //set motor power level (ensure that no discrepancy exists between output pins and motorSpeed)
    set_motor_current(motorCurrent);

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

    //light up command received LED
    if(cmd_received == true)
    {
      digitalWrite(PIN_LED_3, HIGH);
    }
    else
    {
      digitalWrite(PIN_LED_3, LOW);
    }
    //reset command received flag
    cmd_received = false;
   
    
  }
  

  
}

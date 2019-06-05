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
#include "kill_switch.h"
#include "linear_position.h"

//function prototype declarations
void terminal_output(void);         //output data to the serial terminal

//global constants
#define BAUD_RATE               115200  //for serial communication
#define TERMINAL_REFRESH_PERIOD    250  //in ms

#define KP_INITIAL                 30.0  // initial PID gains
#define KI_INITIAL                 10.0
#define KD_INITIAL                 5.0

#define MAX_CURRENT                100     //percentage of max current allowed


//global variables
extern volatile long encoderPosition;   //updated by ISR in encoder_position file
extern float IMUAngle
int motorCurrent = 0;                   //present motor current for output to DRV8840
float currentPosition = 0;              //current linear position of spool robot (inches)

unsigned long lastTerminalRefreshTime = 0;  //time since terminal output has been refreshed


void setup()
{
  //initialize motor controller
  motor_control_init();    //initialize pins
  set_motor_current(motorCurrent);  //set motor current to 0 initially

  // set initial PID gain values
  SetTunings(KP_INITIAL, KI_INITIAL, KD_INITIAL);

  //set output limits on PID controller
  SetOutputLimits(-MAX_CURRENT, MAX_CURRENT);

  //enable the PID controller
  SetMode(AUTOMATIC, linear_position_get(encoderPosition,IMUAngle));

  //initialize serial peripheral
  Serial1.begin(BAUD_RATE);

  //activate kill switch upon power up
  kill();

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

  //update current position
  currentPosition = linear_position_get(encoderPosition,IMUAngle);

  //run PID loop
  motorCurrent = Compute(currentPosition);

  //output to DRV8840
  set_motor_current(motorCurrent);

  //check if time to refresh the terminal output
  if(millis()-lastTerminalRefreshTime >= TERMINAL_REFRESH_PERIOD)
  {
    //update timer
    lastTerminalRefreshTime += TERMINAL_REFRESH_PERIOD;
    //output to terminal
    terminal_output();
  }


}

void terminal_output(void)
{
  //clear the screen
  Serial1.print("\033[2J");

  //output current robot state
  Serial1.print("motor current: ");
  Serial1.print(motorCurrent);
  Serial1.print("\r\n");
  Serial1.print("current position: ");
  Serial1.print(currentPosition);
  Serial1.print("\r\n");
  Serial1.print("Position Setpoint: ");
  Serial1.print(get_setpoint());
  Serial1.print("\r\n");

  //output PID tuning values
  Serial1.print("Kp: ");
  Serial1.print(get_kp());
  Serial1.print("\r\n");
  Serial1.print("Ki: ");
  Serial1.print(get_ki());
  Serial1.print("\r\n");
  Serial1.print("Kd: ");
  Serial1.print(get_kd());
  Serial1.print("\r\n");

  //output kill switch state
  Serial1.print("Kill switch state: ");
  Serial1.print(get_activeState());
  Serial1.print("\r\n");

}

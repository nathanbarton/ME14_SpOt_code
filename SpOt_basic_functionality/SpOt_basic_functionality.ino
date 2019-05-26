#include "libraries/SpOt_board.h"
#include "libraries/motor_control.h"

int serialValue = 0;
int motorSpeed = 0;

unsigned long lastRefreshTime = 0;
bool led_state = false;

#define MAX_SPEED         25
#define SPEED_INCREMENT   5
//#define DELAY_TIME        100
#define REFRESH_PERIOD    200

void setup() {
  // put your setup code here, to run once:
  motor_control_init();
  set_motor_current(motorSpeed);
  motor_control_enable();
  
  Serial1.begin(9600);

  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_2, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //check if a serial character is available
  if(Serial1.available() > 0)
  {
    //read incoming data
    serialValue = Serial1.read();
    //parse read value 
    if(serialValue == 'q' && motorSpeed < MAX_SPEED)
    {
      motorSpeed += SPEED_INCREMENT;
    }
    if(serialValue == 'a' && motorSpeed > (MAX_SPEED*(-1)))
    {
      motorSpeed -= SPEED_INCREMENT;
    }
    if(serialValue == ' ')
    {
      motorSpeed = 0;
    }

    set_motor_current(motorSpeed);
  }

  if(millis()-lastRefreshTime >= REFRESH_PERIOD)
  {
    lastRefreshTime += REFRESH_PERIOD;
    //output current motor speed
    Serial1.print("\033[2J");
    Serial1.print("motor power level: ");
    Serial1.print(motorSpeed);
    Serial1.print("\r");

    set_motor_current(motorSpeed);
    
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
  

  //delay(DELAY_TIME);
  
}

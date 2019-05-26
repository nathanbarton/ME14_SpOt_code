// ----------------------------------------
//      SpOt_board.h
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This file includes pin definitions for the SpOt drive PCB
//  for the ME14 independent project
//
//  Known Bugs:		
//
//  Revision History:
//     2019-05-25   Nathan T Barton      Initial revision


// -------------------------------
// Motor Controller Pins (DRV8840)
// -------------------------------
// control output pins
#define PIN_PHASE    4  //motor direction
#define PIN_ENBL     9  //enable motor controller
#define PIN_DECAY    8  //set decay mode of the controller
#define PIN_nRESET   7  //reset the motor controller (active low)
// current output pins
#define PIN_I4      A0  //high bit of current control value
#define PIN_I3      A1
#define PIN_I2      A2
#define PIN_I1      A3
#define PIN_I0      A4  //low bit of current control value
// control input pins
#define PIN_nFAULT   2  //error status pin of motor controller


// -------------------------------
// RC Controller Pins
// -------------------------------
#define PIN_CH_0     6
#define PIN_CH_1     3

// -------------------------------
// Motor Encoder Pins
// -------------------------------
#define PIN_ENC_A    5
#define PIN_ENC_B   10

// -------------------------------
// User LED Pins
// -------------------------------
#define PIN_LED_2   11
#define PIN_LED_3   12
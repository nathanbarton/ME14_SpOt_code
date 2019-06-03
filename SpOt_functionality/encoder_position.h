// ----------------------------------------
//      encoder_position.h
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This file includes function prototype declarations for monitoring the motor encoder
//   on the SpOt drive PCB for the ME14 spool robot project.  
//
//  The public functions are:
//		encoder_init - configure encoder pins for input and attach encoder pin ISR
//		encoder_position_set - set encoder position to a specified value
//
//  Global Variables:
//		encoderPosition (long) - absolute encoder position in terms of encoder pulses
//								 (16 pulses per motor revolution, before gearbox)
//
//  Known Bugs/Limitations:	Encoder only reads 1/4 of max encoder resolution by only
//							looking at rising edge of one encoder pin A
//
//  Revision History:
//     2019-05-28   Nathan T Barton      Initial revision

//local includes
#include <arduino.h>
#include "SpOt_board.h"

// -------------------------------
// Program Constants
// -------------------------------
#define ENCODER_POLARITY   LOW   //define the forward direction as ENC_B low when ENC_A goes high

// -------------------------------
// Function Prototype Declarations
// -------------------------------
//public functions
void encoder_init(void);
void encoder_position_set(long position);

//local functions
void enc_ISR(void);



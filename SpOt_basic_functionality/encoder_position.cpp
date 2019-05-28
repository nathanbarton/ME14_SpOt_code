// ----------------------------------------
//      encoder_position.cpp
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This file includes function definitions and global variables for monitoring the 
//   motor encoder on the SpOt drive PCB for the ME14 spool robot project.  
//
//  The public functions are:
//		encoder_init - configure encoder pins for input and attach encoder pin ISR
//		encoder_position_set - set encoder position to a specified value
//
//  Global Variables:
//		encoderPosition (long) - absolute encoder position in terms of encoder pulses
//								 (16 pulses per motor revolution, before gearbox)
//
//	Local Functions:
//		enc_ISR - interrupt service routine for state change of PIN_ENC_A
//
//  Known Bugs/Limitations:	Encoder only reads 1/4 of max encoder resolution by only
//							looking at rising edge of one encoder pin A
//
//  Revision History:
//     2019-05-28   Nathan T Barton      Initial revision

//Local Includes
#include "encoder_position.h"

//Global Variables
volatile long encoderPosition = 0;


// --------------------------------------------------------------------------------
// Procedure:			encoder_init
// Description:			Initialize encoder pin inputs and set up ISR
// Special Notes:		None.
//
// Author:			Nathan Barton
// Last Modified:	2019-05-28
void encoder_init(void)
{
	//set encoder pins to input
	pinMode(PIN_ENC_A, INPUT);
	pinMode(PIN_ENC_B, INPUT);
	
	//register interrupt service routine
	attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), enc_ISR, RISING);
}

// --------------------------------------------------------------------------------
// Procedure:			encoder_position_set
// Description:			Set encoder position to specified value
// Arguments:			position (long) - set encoder position to this value
// Special Notes:		None.  
//
// Author:			Nathan Barton
// Last Modified:	2019-05-28
void encoder_position_set(long position)
{
	encoderPosition = position;
}

// --------------------------------------------------------------------------------
// Procedure:			enc_ISR
// Description:			Interrupt service routine for PIN_ENC_A
// Limitations:			Only reads 16 CPR encoder resolution
// Special Notes:		Motor forward direction set by ENCODER_POLARITY
//
// Author:			Nathan Barton
// Last Modified:	2019-05-28
void enc_ISR(void)
{
	//ENC_A has transitioned to high
	if(digitalRead(PIN_ENC_B) == ENCODER_POLARITY)
	{
		//motor moving forward
		encoderPosition++;
	}
	else
	{
		//motor moving backwards
		encoderPosition--;
	}
	
}
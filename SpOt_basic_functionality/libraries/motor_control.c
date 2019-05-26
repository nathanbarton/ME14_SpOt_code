// ----------------------------------------
//      motor_control.c
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This file includes function definitions for interfacing with 
//   the DRV8840 motor controller on the SpOt drive PCB for the ME14
//   spool robot project.  
//
//  The public functions are:
//		motor_control_init - Initialize IO pins for communicating with DRV8840
//		motor_control_enable - Enable output of the DRV8840
//		motor_control_disable - Disable output of the DRV8840
//		set_motor_current - set the direction and current of the DRV8840 output
//
//  Known Bugs/Limitations:	
//		set_motor_current can only set values prescribed by the DRV8840	
//
//  Revision History:
//     2019-05-25   Nathan T Barton      Initial revision
//     2019-05-26   Nathan T Barton      added initial setup to motor_control_init


// --------------------------------------------------------------------------------
// Procedure:			motor_control_init
// Description:			This procedure initializes the IO pins for interfacing 
//						with the DRV8840
// Arguments:			None.
// Return Values:		None.
// Data Structures:		None
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		Disables the reset pin and sets decay mode to slow (low)
//
// Author:			Nathan Barton
// Last Modified:	2019-05-25
void motor_control_init(void)
{
	// control output pins
	pinMode(PIN_PHASE, OUTPUT);
	pinMode(PIN_ENBL, OUTPUT);
	pinMode(PIN_DECAY, OUTPUT);
	pinMode(PIN_nRESET, OUTPUT);
	// current output pins
	pinMode(PIN_I4, OUTPUT);
	pinMode(PIN_I3, OUTPUT);
	pinMode(PIN_I2, OUTPUT);
	pinMode(PIN_I1, OUTPUT);
	pinMode(PIN_I0, OUTPUT);
	// control input pins
	pinMode(PIN_nFAULT, INPUT);
	
	//set decay mode to slow and disable reset
	digitalWrite(PIN_DECAY, LOW);
	digitalWrite(PIN_nRESET, HIGH);
}

// --------------------------------------------------------------------------------
// Procedure:			motor_control_enable
// Description:			This procedure enables the DRV8840 by setting ENBL high
//
// Author:			Nathan Barton
// Last Modified:	2019-05-25
void motor_control_enable(void)
{
	digitalWrite(PIN_ENBL, HIGH);
}

// --------------------------------------------------------------------------------
// Procedure:			motor_control_disable
// Description:			This procedure disables the DRV8840 by setting ENBL low
//
// Author:			Nathan Barton
// Last Modified:	2019-05-25
void motor_control_disable(void)
{
	digitalWrite(PIN_ENBL, LOW);
}

// --------------------------------------------------------------------------------
// Procedure:			set_motor_current
// Description:			This procedure sets the current pins to control the motor 
//						current.  Current is based on a scale of -100 to 100% of 
//						max motor current, with the sign indicating motor direction
// Arguments:			level (int) - power level as a percentage of max motor current.
//									negative numbers indicate the reverse direction
// Return Values:		None.
// Limitations:			Can only set current to the percentage values allowed by the
//						DRV8840 driver, rounds up to the next highest motor current
//						value if between allowed values
//
// Author:			Nathan Barton
// Last Modified:	2019-05-25
void set_motor_current(int level)
{
	//set phase pin for direction control
	if(level<0)
	{
		//set reverse direction
		digitalWrite(PIN_PHASE, MOTOR_REVERSE);
		//set level to positive for current pin setting
		level *= (-1);
	}
	else
	{
		//set forward direction
		digitalWrite(PIN_PHASE, MOTOR_FORWARD);
	}
	
	//set current pin
	if(level == 0)
	{
		//0x00h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level <= 5)
	{
		//0x01h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=10)
	{
		//0x02h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=15)
	{
		//0x03h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=20)
	{
		//0x04h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=24)
	{
		//0x05h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=29)
	{
		//0x06h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=34)
	{
		//0x07h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=38)
	{
		//0x08h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=43)
	{
		//0x09h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=47)
	{
		//0x0Ah
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=51)
	{
		//0x0Bh
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=56)
	{
		//0x0Ch
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=60)
	{
		//0x0Dh
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=63)
	{
		//0x0Eh
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=67)
	{
		//0x0Fh
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=71)
	{
		//0x10h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=74)
	{
		//0x11h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=77)
	{
		//0x12h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=80)
	{
		//0x13h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=83)
	{
		//0x14h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=86)
	{
		//0x15h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=88)
	{
		//0x16h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=90)
	{
		//0x17h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=92)
	{
		//0x18h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=94)
	{
		//0x19h
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=96)
	{
		//0x1Ah
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=97)
	{
		//0x1Bh
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level<=98)
	{
		//0x1Ch
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	else if(level<=99)
	{
		//0x1Dh
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, HIGH);
	}
	else if(level>=100)
	{
		//0x1Dh
		digitalWrite(PIN_I4, HIGH);
		digitalWrite(PIN_I3, HIGH);
		digitalWrite(PIN_I2, HIGH);
		digitalWrite(PIN_I1, HIGH);
		digitalWrite(PIN_I0, HIGH);
	}
	else
	{
		//base case 0 current
		//0x00h
		digitalWrite(PIN_I4, LOW);
		digitalWrite(PIN_I3, LOW);
		digitalWrite(PIN_I2, LOW);
		digitalWrite(PIN_I1, LOW);
		digitalWrite(PIN_I0, LOW);
	}
	
}
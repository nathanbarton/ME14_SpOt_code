// ----------------------------------------
//      motor_control.h
//      ME14 Spring 2019
//      Author: Nathan T Barton
// ----------------------------------------
// This file includes function prototype declarations for interfacing with 
//   the DRV8840 motor controller on the SpOt drive PCB for the ME14
//   spool robot project.  
//
//  The public functions are:
//
//  Known Bugs:		
//
//  Revision History:
//     2019-05-25   Nathan T Barton      Initial revision


// -------------------------------
// Program Constants
// -------------------------------
#define MOTOR_FORWARD   HIGH   //define the forward direction as PIN_PHASE set high
#define MOTOR_REVERSE   LOW    //define the reverse direction as PIN_PHASE set low

// -------------------------------
// Function Prototype Declarations
// -------------------------------
void motor_control_init(void);
void motor_control_enable(void);
void motor_control_disable(void);
void set_motor_current(byte level);

// ----------------------------------------
//      kill_switch.h
//      ME14 Spring 2019
//      Author: Maheck Jerez Terceros
// ----------------------------------------
// This file includes function prototype declarations for monitoring the motor encoder
//   on the SpOt drive PCB for the ME14 spool robot project.
//
//  The public functions are:
//		kill() - Kills all motor control to SpOt
//    reset() - Resets system for restarting PID control
//
//  Global Variables:
//
//  Known Bugs/Limitations:
//
//  Revision History:
//     2019-05-28   Maheck Jerez Terceros      Initial revision


//public functions
void reset();
void kill();

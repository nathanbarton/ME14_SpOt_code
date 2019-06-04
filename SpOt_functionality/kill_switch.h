// ----------------------------------------
//      kill_switch.h
//      ME14 Spring 2019
//      Author: Maheck Jerez Terceros
// ----------------------------------------
// This file includes function prototype declarations for reset and kill switch
// functions in case of emergency reset.
//
//  The public functions are:
//		kill() - Kills all motor control to SpOt
//    kill_reset() - Resets system for restarting PID control
//    get_activeState() - returns state of system with respect to kill
//  Global Variables:
//
//  Known Bugs/Limitations:
//
//  Revision History:
//     2019-05-28   Maheck Jerez Terceros      Initial revision


//public functions
void kill_reset();
void kill();
voide get_activeState();

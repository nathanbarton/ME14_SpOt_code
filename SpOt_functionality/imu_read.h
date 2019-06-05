// ----------------------------------------
//      imu_read.h
//      ME14 Spring 2019
//      Author: Mike Brown
// ----------------------------------------
// This file includes functions that initialize the IMU,
// 			read values from the IMU, and get the angle of SpOt's bed.
//  The public functions are:
//		imu_init - Runs the code to initialize the IMU.
//		read_angle - Gets the updated angular position values from the IMU.
//		get_angle - Returns the current angle (float)
//
//  Known Bugs/Limitations:	None.		
//
//  Revision History:
//     2019-06-04   Mike Brown      Initial revision

//local includes
#include <arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "SpOt_board.h"

//#define I2CDEV_IMPLEMENTATION I2CDEV_ARDUINO_WIRE

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// -------------------------------
// Program Constants
// -------------------------------
#define INTERRUPT_PIN PIN_IMU_INT // pin number for the IMU's interrupt pin
#define ANGLE_INDEX    1 // index value of the angle in the yaw, pitch, roll array
						 // set 1 for pitch, and 2 for roll

#define X_GYRO_OFFSET  220  // offsets for IMU, from IMU calibration
#define Y_GYRO_OFFSET  76 
#define Z_GYRO_OFFSET  -85
#define Z_ACCEL_OFFSET 1788 

// -------------------------------
// Function Prototype Declarations
// -------------------------------
void read_angle(void);
float get_angle(void);
void imu_init(void);
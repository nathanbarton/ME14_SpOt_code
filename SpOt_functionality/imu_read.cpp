// ----------------------------------------
//      imu_read.cpp
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
//     2019-06-04     Mike Brown		Initial Revision

#include "imu_read.h"

MPU6050 mpu;

bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
float angle = 0.0;

// changes the interrupt status when the interrupt pin is signaled
void dmpDataReady(void) {
  mpuInterrupt = true;
}

// --------------------------------------------------------------------------------
// Procedure:			imu_init
// Description:			This procedure runs the initialization functions for the IMU.
// Arguments:			None.
// Return Values:		None.
// Data Structures:		None
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		None.
//
// Author:			Mike Brown
// Last Modified:	2019-06-04
void imu_init(void) {

	// set the interrupt pin as an input
	pinMode(INTERRUPT_PIN, INPUT);
 
  	// join I2C bus (I2Cdev library doesn't do this automatically)
  	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    	Wire.begin();
    	Wire.setClock(400000); // 400kHz I2C clock (200kHz if CPU is 8MHz)
  	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    	Fastwire::setup(400, true);
  	#endif

    // initialize device
    mpu.initialize();

    // load and configure the DMP
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); 

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
      // turn on the DMP, now that it's ready
      mpu.setDMPEnabled(true);
  
      // enable Arduino interrupt detection
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();
  
      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      dmpReady = true;
  
      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
    }


}

  

// --------------------------------------------------------------------------------
// Procedure:			rear_angle
// Description:			This procedure gets the bed orientation from the imu.
// Arguments:			None.
// Return Values:		None.
// Data Structures:		None
// Limitations:			None.
// Known Bugs:			None.
// Special Notes:		None.
//
// Author:			Mike Brown
// Last Modified:	2019-06-04
void read_angle(void) {


  // check if interrupt is flagged
  if(mpuInterrupt || fifoCount >= packetSize) {
  
	  // reset interrupt flag and get INT_STATUS byte
	  mpuInterrupt = false;
	  mpuIntStatus = mpu.getIntStatus();

	  // get current FIFO count
	  fifoCount = mpu.getFIFOCount();

	  // check for overflow (this should never happen unless our code is too inefficient)
	  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
	    // reset so we can continue cleanly
	    mpu.resetFIFO();
	    // otherwise, check for DMP data ready interrupt (this should happen frequently)
	  } 
	  else if (mpuIntStatus & 0x02) {
	    // wait for correct available data length, should be a VERY short wait
	    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

	    // read a packet from FIFO
	    mpu.getFIFOBytes(fifoBuffer, packetSize);

	    // track FIFO count here in case there is > 1 packet available
	    // (this lets us immediately read more without waiting for an interrupt)
	    fifoCount -= packetSize;


	    // display Euler angles in degrees
	    mpu.dmpGetQuaternion(&q, fifoBuffer);
	    mpu.dmpGetGravity(&gravity, &q);
	    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

	    // gets the angle from the correct position in the yaw, pitch, roll array
	    angle = ypr[ANGLE_INDEX]; // output in radians
	    
	  }
  }

}

// get functions
float get_angle(void) {

	return angle;

}
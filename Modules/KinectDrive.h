#ifndef KINECT_DRIVE_H_
#define KINECT_DRIVE_H_
#include "../Defines.h"
#include "WPILib.h"

class KinectDrive{
public:
	KinectDrive();
	~KinectDrive();
	void SetKinectDrive();
private:
	Kinect *kinectSensor;
	KinectStick *kinectDrive;
	
	int leftHand, rightHand;
};
#endif

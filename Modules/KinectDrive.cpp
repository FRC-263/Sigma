#include "KinectDrive.h"

KinectDrive::KinectDrive(){
	//kinectSensor = new Kinect();
	kinectDrive = new KinectStick(KINECT_DRIVE_STICK);
}
KinectDrive::~KinectDrive(){
	delete kinectDrive;
}
void KinectDrive::SetKinectDrive(){	

	kinectSensor->GetSkeleton(1);
	leftHand = kinectDrive->kLeftHand;
	rightHand = kinectDrive->kRightHand;
	kinectDrive->GetX();
	kinectDrive->GetY();
}


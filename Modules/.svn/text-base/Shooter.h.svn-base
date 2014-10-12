#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "WPILib.h"
#include <math.h>
#include "../Defines.h"
#include "../Misc/AfterPID.h"
#include "VisionTracking.h"
#include "../Sigma.h"
#include "PolyurethaneBelt.h"
#include "../Misc/DashboardConnecter.h"

class Shooter {
private:
	Victor *topWheel;
	Victor *bottomWheel;
	Victor *turretMotor;
	Notifier *shooterNotifier;

	AfterPID *turretPID;
	AfterPID *topWheelPID;
	AfterPID *bottomWheelPID;
	AfterPID *trackingPID;
	
	AnalogChannel *shooterAngle;
	
	AnalogChannel *bottomShooterTach;
	AnalogChannel *topShooterTach;
	
	VisionTracking* shooterTracker;

	DashboardConnecter *dash;
public:
	Shooter();
	~Shooter();
	
	void StartPID();
	void ResetPID();
	
	float GetTopWheelVoltage();
	float GetBottomWheelVoltage();
	VisionTracking* GetShooterTracking();
	
	static void DriveShooter(void *nshooter);
	void DriveAutonShooter(PolyurethaneBelt *belt);
};

#endif

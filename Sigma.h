#ifndef SIGMA_H_
#define SIGMA_H_

#include "WPILib.h"
#include "Defines.h"
#include "Modules/MecanumDrive.h"
#include "Modules/BridgeArm.h"
#include "Modules/Shooter.h"
#include "Modules/PolyurethaneBelt.h"
#include "Globals.h"

class Shooter;

class Sigma : public SimpleRobot
{
private:
	static Sigma *theRobot;
	
	MecanumDrive *driveTrain;
	PolyurethaneBelt *beltControl;
	BridgeArm *bridgeArm;
	Shooter *shooter;
	
public:	
	Sigma(void);	
	void Autonomous(void);
	void OperatorControl();
	static Sigma* GetSigma();
};

#endif

#ifndef BRIDGEARM_H_
#define BRIDGEARM_H_

#include "WPILIB.h"
#include "../Defines.h"

class BridgeArm {
public:
	BridgeArm();
	~BridgeArm();

	void DriveBridgeArm();

private:
	Relay *bridgeArmMotor;

	DigitalInput *topBridgeLimitSwitch;
	DigitalInput *bottomBridgeLimitSwitch;
};
#endif

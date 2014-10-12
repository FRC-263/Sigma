#include "BridgeArm.h"

BridgeArm::BridgeArm()
{
	bridgeArmMotor = new Relay(BRIDGE_ARM_SPIKE);
	topBridgeLimitSwitch = new DigitalInput(TOP_BRIDGE_ARM_LIMIT_SWITCH);
	bottomBridgeLimitSwitch = new DigitalInput(BOTTOM_BRIDGE_ARM_LIMIT_SWITCH);
}

BridgeArm::~BridgeArm()
{
	delete bridgeArmMotor;
}

void BridgeArm::DriveBridgeArm()
{
	DriverStation *ds = DriverStation::GetInstance();
	if(!ds->GetDigitalIn(5))
	{
		//printf("Top: %d, Bottom: %d\n", topBridgeLimitSwitch->Get(), bottomBridgeLimitSwitch->Get());
		if(ds->GetDigitalIn(6) && ds->GetDigitalIn(8))
		{
			bridgeArmMotor->Set(Relay::kOff);
		}
		else if(ds->GetDigitalIn(6) && !ds->GetDigitalIn(8))
		{
			bridgeArmMotor->Set(Relay::kForward);
		}
		else if(!ds->GetDigitalIn(6) && ds->GetDigitalIn(8))
		{
			bridgeArmMotor->Set(Relay::kReverse);
		}
		else
		{
			bridgeArmMotor->Set(Relay::kOff);
		}
	}
}

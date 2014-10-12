#include "PolyurethaneBelt.h"
#include "../Defines.h"

PolyurethaneBelt::PolyurethaneBelt(void)
{
	leftBallSpike = new Relay(LEFT_BALL_SWEEP_SPIKE);
	rightBallSpike = new Relay(RIGHT_BALL_SWEEP_SPIKE);
	polyurethaneBeltMotor = new Relay(POLYURETHANE_BELT_SPIKE);

	leftBallSpike->Set(Relay::kOff);
	rightBallSpike->Set(Relay::kOff);
	polyurethaneBeltMotor->Set(Relay::kOff);
}

PolyurethaneBelt::~PolyurethaneBelt()
{
	delete leftBallSpike;
	delete rightBallSpike;
}

void PolyurethaneBelt::DriveBelt()
{
	DriverStation *ds = DriverStation::GetInstance();

	if(ds->GetDigitalIn(5))
	{
		if(ds->GetDigitalIn(3) && !ds->GetDigitalIn(4)){
			//Reverse 
			leftBallSpike->Set(Relay::kReverse);
			rightBallSpike->Set(Relay::kReverse);
		}
		else if(ds->GetDigitalIn(4) && !ds->GetDigitalIn(3)){
			//Forward
			leftBallSpike->Set(Relay::kForward);
			rightBallSpike->Set(Relay::kForward);
		}
		else {
			//Off
			leftBallSpike->Set(Relay::kOff);
			rightBallSpike->Set(Relay::kOff);
			//polyurethaneBeltMotor->Set(Relay::kOff);
		}

		if(!ds->GetDigitalIn(6) && ds->GetDigitalIn(8))
		{
			polyurethaneBeltMotor->Set(Relay::kReverse);
		}
		else if(ds->GetDigitalIn(6) && !ds->GetDigitalIn(8))
		{
			polyurethaneBeltMotor->Set(Relay::kForward);
		}
		else if(ds->GetDigitalIn(6) && ds->GetDigitalIn(8))
		{
			polyurethaneBeltMotor->Set(Relay::kOff);
		}
	}
}

void PolyurethaneBelt::DriveAutonBelt(bool bDriveBelt)
{
	if(bDriveBelt)
		polyurethaneBeltMotor->Set(Relay::kForward);
	else
		polyurethaneBeltMotor->Set(Relay::kOff);
}

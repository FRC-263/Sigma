#include "Sigma.h"

Sigma* Sigma::theRobot;
Sigma::Sigma(void)
{
	GetWatchdog().SetExpiration(0.1);
	GetWatchdog().SetEnabled(false);
	driveTrain = new MecanumDrive();
	bridgeArm = new BridgeArm();
	beltControl = new PolyurethaneBelt();
	shooter = new Shooter();
	theRobot = this;
}
	
void Sigma::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);
	//int i = 0;
	//shooter->StartPID();
	shooter->ResetPID();
	/*while(IsAutonomous())
	{
		shooter->DriveAutonShooter(beltControl);
	}*/
	while(IsAutonomous())
	{
		//driveTrain->KinectDrive();
		shooter->DriveAutonShooter(beltControl);
		/*if(i < 1000)
		{
			driveTrain->AutonDrive();
			i++;
		}
		else
		{
			driveTrain->StopDrive();
			shooter->DriveAutonShooter(beltControl);
		}*/
		// Drive back for two seconds 
	}
/*	while(IsAutonomous()){
		shooter->DriveAutonShooter();
		Wait(0.005);
		i++;
		if(i > 1200)
			beltControl->DriveAutonBelt(true);
	}*/
}

void Sigma::OperatorControl()
{
	GetWatchdog().SetEnabled(false);
	shooter->StartPID();
	while (IsOperatorControl())
	{
		driveTrain->Drive();
		beltControl->DriveBelt();
		bridgeArm->DriveBridgeArm();
	}
}
	
Sigma* Sigma::GetSigma()
{
	return theRobot;
}

START_ROBOT_CLASS(Sigma);

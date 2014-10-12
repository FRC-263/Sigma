#include "MecanumDrive.h"
#include "../Globals.h"

extern Gyro *gyroSensor;

MecanumDrive::MecanumDrive(void)
{
	leftFrontMotor = new CANJaguar(LEFT_FRONT_MOTOR, CANJaguar::kPercentVbus);
	leftBackMotor = new CANJaguar(LEFT_BACK_MOTOR, CANJaguar::kPercentVbus);
	rightFrontMotor = new CANJaguar(RIGHT_FRONT_MOTOR, CANJaguar::kPercentVbus);
	rightBackMotor = new CANJaguar(RIGHT_BACK_MOTOR, CANJaguar::kPercentVbus);
	leftArm = new KinectStick(1);
	rightArm = new KinectStick(2);
		
	driveStick = new Joystick(ARCADESTICK);

	DriveTrainPID = new AfterPID(1, 0, 0);

	SetupDriveTrain();
}

MecanumDrive::~MecanumDrive(void)
{
	delete leftFrontMotor;
	delete rightFrontMotor;
	delete leftBackMotor;
	delete rightBackMotor;

	delete driveStick;
}

void MecanumDrive::Drive(void)
{
	float StrafeX = driveStick->GetX() * (driveStick->GetZ() - 1.5) / -2.5;
	float StrafeY = driveStick->GetY() * -1 * (driveStick->GetZ() - 1.5) / -2.5;
	
	float Twist = driveStick->GetTwist() * -1 * (driveStick->GetZ() - 1.5) / -2.5;

	if(fabs(Twist) < 0.15)
		Twist = 0;
	if(fabs(StrafeX) < 0.15)
		StrafeX = 0;
	if(fabs(StrafeY) < 0.15)	
		StrafeY = 0;

	CartesianSpeedCalculation(StrafeX, StrafeY, Twist);
	Normalize();

	UINT syncGroup = 0x80;

	leftFrontMotor->Set(FrontLeftSpeed * -1, syncGroup);
	rightFrontMotor->Set(FrontRightSpeed, syncGroup);
	leftBackMotor->Set(BackLeftSpeed * -1, syncGroup);
	rightBackMotor->Set(BackRightSpeed, syncGroup);

	CANJaguar::UpdateSyncGroup(syncGroup);
	
	//printf("Strafe X: %f Strafe Y: %f\n", StrafeX, StrafeY);
	//printf("FL: %f FR: %f RL: %f RR: %f\n", leftFrontMotor->GetSpeed(), rightFrontMotor->GetSpeed(), leftBackMotor->GetSpeed(), rightBackMotor->GetSpeed());
}

void MecanumDrive::AutonDrive(){
		float StrafeX = 0;
		float StrafeY = -0.36;

		float Twist = 0;
		
		static const float kP = 0.04;

		CartesianSpeedCalculation(StrafeX, StrafeY, Twist);
		Normalize();

		UINT syncGroup = 0x80;
		
		float angle = gyroSensor->GetAngle();
		
		leftFrontMotor->Set((FrontLeftSpeed * -1) * (angle * kP), syncGroup);
		rightFrontMotor->Set(FrontRightSpeed * (-angle * kP), syncGroup);
		leftBackMotor->Set((BackLeftSpeed * -1) * (angle * kP), syncGroup);
		rightBackMotor->Set(BackRightSpeed * (-angle * kP), syncGroup);

		CANJaguar::UpdateSyncGroup(syncGroup);
}
void MecanumDrive::KinectDrive(){
		//float StrafeX = 0;
		//float StrafeY = -0.36;

		float Twist = 0;

		CartesianSpeedCalculation(leftArm->GetY() * 0.33, rightArm->GetY() * 0.33, Twist);
		Normalize();

		UINT syncGroup = 0x80;

		leftFrontMotor->Set(FrontLeftSpeed * -1, syncGroup);
		rightFrontMotor->Set(FrontRightSpeed, syncGroup);
		leftBackMotor->Set(BackLeftSpeed * -1, syncGroup);
		rightBackMotor->Set(BackRightSpeed, syncGroup);

		CANJaguar::UpdateSyncGroup(syncGroup);
}

void MecanumDrive::StopDrive()
{
	UINT syncGroup = 0x80;

	leftFrontMotor->Set(0, syncGroup);
	rightFrontMotor->Set(0, syncGroup);
	leftBackMotor->Set(0, syncGroup);
	rightBackMotor->Set(0, syncGroup);

	CANJaguar::UpdateSyncGroup(syncGroup);
}

void MecanumDrive::CartesianSpeedCalculation(float x, float y, float rotation)
{
	double xIn = x;
	double yIn = y;

	yIn = -yIn;

	FrontLeftSpeed = xIn + yIn + rotation;
	FrontRightSpeed = -xIn + yIn - rotation;
	BackLeftSpeed = -xIn + yIn + rotation;
	BackRightSpeed = xIn + yIn - rotation;
}


void MecanumDrive::Normalize()
{
	double MaxMagnitude = 0;

	if(fabs(FrontLeftSpeed) > MaxMagnitude)
	{
		MaxMagnitude = fabs(FrontLeftSpeed);
	}

	if(fabs(FrontRightSpeed) > MaxMagnitude)
	{
		MaxMagnitude = fabs(FrontRightSpeed);
	}

	if(fabs(BackLeftSpeed) > MaxMagnitude)
	{
		MaxMagnitude = fabs(BackLeftSpeed);
	}

	if(fabs(BackRightSpeed) > MaxMagnitude)
	{
		MaxMagnitude = fabs(BackRightSpeed);
	}

	if(MaxMagnitude > 1.0)
	{
		FrontLeftSpeed = FrontLeftSpeed / MaxMagnitude;
		FrontRightSpeed = FrontRightSpeed / MaxMagnitude;
		BackLeftSpeed = BackLeftSpeed / MaxMagnitude;
		BackRightSpeed = BackRightSpeed / MaxMagnitude;
	}
}

void MecanumDrive::SetupDriveTrain()
{
	leftFrontMotor->SetSafetyEnabled(false);
	rightFrontMotor->SetSafetyEnabled(false);
	leftBackMotor->SetSafetyEnabled(false);
	rightBackMotor->SetSafetyEnabled(false);

	leftFrontMotor->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
	rightFrontMotor->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
	leftBackMotor->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
	rightBackMotor->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	leftFrontMotor->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	rightFrontMotor->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	leftBackMotor->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	rightBackMotor->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

	leftFrontMotor->ConfigEncoderCodesPerRev(360);
	rightFrontMotor->ConfigEncoderCodesPerRev(360);
	leftBackMotor->ConfigEncoderCodesPerRev(360);
	rightBackMotor->ConfigEncoderCodesPerRev(360);

	leftFrontMotor->EnableControl();
	rightFrontMotor->EnableControl();
	leftBackMotor->EnableControl();
	rightBackMotor->EnableControl();
}

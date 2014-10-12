#ifndef DEFINES_H_
#define DEFINES_H_

//In MecanumDrive.cpp

	//Joystick Value
	#define ARCADESTICK 1

	//Jaguar Values for Left Side
	#define LEFT_FRONT_MOTOR 1
	#define LEFT_BACK_MOTOR 2

	//Jaguar Values for Right Side
	#define RIGHT_FRONT_MOTOR 3
	#define RIGHT_BACK_MOTOR 4

//In PolyurethaneBelt.cpp

	//Ball Sweeper Channels
	#define LEFT_BALL_SWEEP_SPIKE 2
	#define RIGHT_BALL_SWEEP_SPIKE 1

	//Belt Motors
	#define POLYURETHANE_BELT_SPIKE 4

	//Banner Sensors
	#define LEFT_BANNER_SENSOR 4
	#define RIGHT_BANNER_SENSOR 5

//In BridgeArm.cpp

	//Spike Channels
	#define BRIDGE_ARM_SPIKE 3

	//Bridge Arm Limit Switch
	#define TOP_BRIDGE_ARM_LIMIT_SWITCH 1
	#define BOTTOM_BRIDGE_ARM_LIMIT_SWITCH 2

//In Shooter.cpp
		
	//Switch to Change Shooting Mode
	#define DS_SHOOTER_MODE 1
	
	//Manual Shooting Mode Defines
	#define DS_TOWER_POT 1
	#define TOWER_POT 1
	#define SHOOTER_POT 3


	//Minimum ADC reading on turret pot
	#define TURRET_POT_ADC_MIN 614

	//Maximum ADC reading on turret pot 
	#define TURRET_POT_ADC_MAX 3235
	
	//Deadbands
	#define TURRET_DEADBAND .002

	//Tachs
	#define BOTTOM_TACH_CHANNEL 4
	#define TOP_TACH_CHANNEL 6
	
	//Victors
	#define TOP_SHOOTER_WHEEL 5
	#define BOTTOM_SHOOTER_WHEEL 4
	#define TURRET_MOTOR 1

	#define TURRET_MIN .057805 //.8812
	#define TURRET_MAX .145595

//Kinect.cpp
	//Kinect Value
#define KINECT_DRIVE 1

#define KINECT 1

//Kinect Stick
#define KINECT_DRIVE_STICK 1

//Kinect Hand
#define LEFT_HAND 1
#define RIGHT_HAND 2

//Unused Defines

	//DriveTrain PID Values
	#define DRIVETRAIN_P .001
	#define DRIVETRAIN_I 0
	#define DRIVETRAIN_D 0

#endif

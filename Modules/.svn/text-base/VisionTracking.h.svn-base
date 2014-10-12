#ifndef VISION_TRACKING_H_
#define VISION_TRACKING_H_

#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include "../Misc/DashboardConnecter.h"

typedef struct s_ShooterInformation
{
	double shooterDistance;
	double particleOffset;
	int numParticles;
	double particleArea;
}ShooterInformation;

typedef struct s_DashboardShooterInformation
{
	int CenterOfMassX;
	int CenterOfMassY;
	int Height;
	int Width;
}DashboardShooterInformation;

class VisionTracking{
public:
	VisionTracking();
	~VisionTracking();
	
	ShooterInformation GetShooterInformation();
	bool IsFreshData();
private:	
	AxisCamera *cam;
	DashboardShooterInformation dash_ShooterInfo;
	DashboardConnecter *dash;
	std::string s_Packet;
	
	bool b_FreshData;
};

#endif

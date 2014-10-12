#include "VisionTracking.h"
VisionTracking::VisionTracking()
{	
	cam = &(AxisCamera::GetInstance("10.2.63.11"));
	cam->WriteResolution(AxisCamera::kResolution_640x480);
	cam->WriteBrightness(30);
	cam->WriteCompression(0);
	cam->WriteWhiteBalance(AxisCamera::kWhiteBalance_Hold);
	cam->WriteColorLevel(100);
	
	dash = new DashboardConnecter();
}

VisionTracking::~VisionTracking()
{
	//delete dash;
}

ShooterInformation VisionTracking::GetShooterInformation()
{
	ShooterInformation shooterInfo;
	std::string tempDashString;
	std::stringstream s_data;
	
	double yOffset = 0.1;
	
	ParticleFilterCriteria2 filterCriteria[] = {
		{IMAQ_MT_BOUNDING_RECT_WIDTH, 10, 800, false, false},
		{IMAQ_MT_BOUNDING_RECT_HEIGHT, 10, 800, false, false},
		//{IMAQ_MT_AREA, 100, 300, false, false}
	};
	
	b_FreshData = false;
	shooterInfo.particleArea = 0;
	if(!cam->StatusIsFatal() && cam->IsFreshImage())
	{
		ColorImage* img = cam->GetImage();
		if(img->GetWidth() > 0 && img->GetHeight() > 0)
		{
			//BinaryImage* filteredImage = img->ThresholdRGB(0,255,60,255,158,255);
			BinaryImage* filteredImage = img->ThresholdHSI(84, 255, 150, 255, 77, 112);
			//BinaryImage* filteredImage = img->ThresholdRGB(0,50,85,180,200,255);
			BinaryImage* convexImage = filteredImage->ConvexHull(false);
			BinaryImage* particleImage = convexImage->ParticleFilter(filterCriteria, 1);
			
			vector<ParticleAnalysisReport>* reports = particleImage->GetOrderedParticleAnalysisReports();
			//shooterInfo.numParticles = reports->size();
			shooterInfo.numParticles = 0;
			int j = 0;
			for(unsigned int i=0;i < reports->size(); i++)
			{
					//printf("Trying to get element: %d\n", i);
					//ParticleAnalysisReport *particleReport = &(reports->at(i));
				ParticleAnalysisReport particleReport = reports->at(i);
				
				if(particleReport.particleArea > 2500)
				{
					j++;
					dash_ShooterInfo.CenterOfMassX = particleReport.center_mass_x;
					dash_ShooterInfo.CenterOfMassY = particleReport.center_mass_y;
					dash_ShooterInfo.Height = particleReport.boundingRect.height;
					dash_ShooterInfo.Width = particleReport.boundingRect.width;
					
					s_data << particleReport.center_mass_x;
					s_Packet.append(s_data.str());
					s_Packet.append(",");
					s_data.str("");
					s_data << particleReport.center_mass_y;
					s_Packet.append(s_data.str());
					s_Packet.append(",");
					s_data.str("");
					s_data << particleReport.boundingRect.width;
					s_Packet.append(s_data.str());
					s_Packet.append(",");
					s_data.str("");
					s_data << particleReport.boundingRect.height;
					s_Packet.append(s_data.str());
					s_Packet.append(",");
					s_data.str("");
					s_data << particleReport.particleArea;
					s_Packet.append(s_data.str());
					s_Packet.append(",");
					s_data.str("");
					
					if(particleReport.center_mass_y_normalized > yOffset)
					{
						yOffset = particleReport.center_mass_y_normalized;
						shooterInfo.particleArea = particleReport.particleArea;
						shooterInfo.particleOffset = particleReport.center_mass_x_normalized;
						s_Packet.append("G");
						s_Packet.append("#");
					}
					else
					{
						s_Packet.append("B");
						s_Packet.append("#");
					}
					
					b_FreshData = true;
				}
			}
			shooterInfo.numParticles = j;
			delete filteredImage;
			delete convexImage;
			delete particleImage;
		}
		delete img;
	}
	if(s_Packet.length() > 0)
	{
		dash->AddData("shotInfo:", (char*)s_Packet.c_str());
		dash->SendData();
	}
	s_Packet.clear();
	
	return shooterInfo;
}

bool VisionTracking::IsFreshData()
{
	return b_FreshData;
}

/*
 * GearPIDWrapper.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: HOT Team
 */

#include <GearPIDWrapper.h>

GearPIDWrapper::GearPIDWrapper()
{

}

GearPIDWrapper::~GearPIDWrapper() {
}


void GearPIDWrapper::PIDWrite(float output) {
	SmartDashboard::PutNumber("* Gear PID Write", output);
	//m_gear->SetSpeed(output);
}


double GearPIDWrapper::ArmPIDGet () {
	return(m_gear.GetGearArmPosition());
}

double GearPIDWrapper::WristPIDGet() {
	return (m_gear.GetGearWristPosition());
}

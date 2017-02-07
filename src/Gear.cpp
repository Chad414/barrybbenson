/*
 * Gear.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Marlina
 */

#include "Gear.h"

Gear::Gear()
	: m_gearArm(TALON_GEAR_ARM),
	  m_gearRoll(TALON_GEAR_ROLL)
{
	// TODO Auto-generated constructor stub
	m_gearArm.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
}

/*
 * Sensors
 */

double Gear::GetGearArmPosition() {
	return (m_gearArm.GetPosition());
}

void Gear::ZeroGearArmPosition() {
	m_gearArm.SetPosition(0.0);
}

void Gear::SetGearArmPosition(double speed) {
	m_gearArm.Set(speed);
}

Gear::~Gear() {
	// TODO Auto-generated destructor stub
}


/*
 * Gear.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Marlina
 */

#include "Gear.h"

Gear::Gear()
	: m_gearArm(TALON_GEAR_ARM),
	  m_gearWrist(TALON_GEAR_WRIST),
	  m_adjustArm(TALON_ADJUST_GEAR),
	  m_gearWristEncoder(GEAR_WRIST_ENCODER_L, GEAR_WRIST_ENCODER_R, true),
	  m_gearArmEncoder(GEAR_ARM_ENCODER_L, GEAR_ARM_ENCODER_R, false)
{
	// TODO Auto-generated constructor stub
}

/*
 * Sensors
 */
double Gear::GetGearWristPosition() {
	return (m_gearWristEncoder.GetDistance());
}

double Gear::GetGearArmPosition() {
	return (m_gearArmEncoder.GetDistance());
}

Gear::~Gear() {
	// TODO Auto-generated destructor stub
}


/*
 * Gear.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: HOT Team
 */

#include "Gear.h"

Gear::Gear()
	: m_lGearArm(TALON_LEFT_GEAR_ARM),
	  m_rGearArm(TALON_RIGHT_GEAR_ARM),
	  m_adjustArm(TALON_ADJUST_GEAR),
	  m_lGearEncoder(GEAR_L_ENCODER_LEFT, GEAR_L_ENCODER_RIGHT, true),
	  m_rGearEncoder(GEAR_R_ENCODER_LEFT, GEAR_R_ENCODER_RIGHT, false)
{
	// TODO Auto-generated constructor stub
}

Gear::~Gear() {
	// TODO Auto-generated destructor stub
}


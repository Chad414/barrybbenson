/*
 * Gear.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Marlina
 */

/*
 * gear arm coast
 * 		300 to 1 gear ratio
 * 		magnetic encoder
 * 		bag motor
 * gear roller
 * 		bag motor
 * intake roller 775
 *
 */
#include "Gear.h"

Gear::Gear()
	: m_gearArm(TALON_GEAR_ARM),
	  m_gearRoll(TALON_GEAR_ROLL)
{
	// TODO Auto-generated constructor stub
	m_gearArm.SetClosedLoopOutputDirection(true);
	m_gearArm.ConfigNominalOutputVoltage(0.0, 0.0);
	m_gearArm.SetPID(TALON_GEAR_P, TALON_GEAR_I, TALON_GEAR_D);
}

double Gear::GetGearArmPosition() {
	return (m_gearArm.GetPosition());
}

void Gear::ZeroGearArmPosition() {
	m_gearArm.SetPosition(0.0);
}

bool Gear::SetGearMode(bool position) {
	if (position) {
		m_gearArm.SetControlMode(CANTalon::kPosition);
		return true;
	}
	else {
		m_gearArm.SetControlMode(CANTalon::kPercentVbus);
		return false;
	}
}

void Gear::SetGearArmPosition(double gear_speed) {
	m_gearArm.Set(gear_speed);
	gearCommandedSpeed = gear_speed;
}

double Gear::GetGearCommandedSpeed() {
	return gearCommandedSpeed;
}

void Gear::SetGearRollerSpeed(double roller_speed) {
	m_gearRoll.Set(roller_speed);
	gearRollerCommandedSpeed = roller_speed;
}

double Gear::GetGearRollerCommandedSpeed() {
	return gearRollerCommandedSpeed;
}

Gear::~Gear() {
	// TODO Auto-generated destructor stub
}


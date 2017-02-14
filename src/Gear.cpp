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
	//m_gearArm.SetClosedLoopOutputDirection(true);
	m_gearArm.SetSensorDirection(false);
	m_gearArm.SetVoltageRampRate(0);
	m_gearArm.SetPID(TALON_GEAR_P, TALON_GEAR_I, TALON_GEAR_D);
	m_gearArm.SetAllowableClosedLoopErr(0);
	m_gearArm.ConfigEncoderCodesPerRev(256);
	m_gearArm.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
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
	gearMode = position;
}

bool Gear::GetGearMode() {
	if (gearMode) {
		return true;
	}
	else {
		return false;
	}
}

void Gear::SetGearArmPosition(double gear_speed) {
	if (GetGearMode() == true){
		gear_speed = gear_speed / GEAR_DEGREE_CONST;
		m_gearArm.Set(gear_speed);
	}
	else {
		m_gearArm.Set(gear_speed);
	}

	gearCommandedSpeed = gear_speed;

	//m_gearArm.Set(gear_speed);
}

void Gear::SetGearArmSetpoint(GearArmSetpoint setpoint) {
	switch (setpoint) {
	case 0:
		SetGearArmPosition(GEAR_GROUND);
		break;
	case 1:
		SetGearArmPosition(GEAR_PLACE_FIRST);
		break;
	case 2:
		SetGearArmPosition(GEAR_PLACE_SECOND);
		break;
	case 3:
		SetGearArmPosition(GEAR_PACKAGE);
		break;
	}
}

double Gear::GetGearCommandedSpeed() {
	return gearCommandedSpeed;
}

double Gear::GetGearSetpoint() {
	return m_gearArm.GetSetpoint();
}

double Gear::GearGet() {
	return m_gearArm.Get();
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


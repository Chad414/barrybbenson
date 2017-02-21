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
	m_gearArm.SetSensorDirection(true);
	m_gearArm.SetVoltageRampRate(0);
	m_gearArm.SetPID(TALON_UP_GEAR_P, TALON_UP_GEAR_I, TALON_UP_GEAR_D);
	m_gearArm.SetAllowableClosedLoopErr(0);
	//m_gearArm.ConfigEncoderCodesPerRev(256);
	m_gearArm.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
}

double Gear::GetGearArmPosition() {
	return (m_gearArm.GetPosition()* GEAR_DEGREE_CONST);
}

double Gear::GetRawGearArmPosition() {
	return m_gearArm.GetPosition();
}

void Gear::ZeroGearArmPosition() {
	m_gearArm.SetPosition(0.0);
}

double Gear::GetGearTalonCurrent() {
	return m_gearArm.GetOutputCurrent();
}

void Gear::SetGearMode(bool position) {
	if (position) {
		m_gearArm.SetControlMode(CANTalon::kPosition);
	}
	else {
		m_gearArm.SetControlMode(CANTalon::kPercentVbus);
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
	if ((GetGearMode() == true)) {// && (GetGearTalonCurrent() < 1.5)){ //position pid, not too high current...
		gear_speed = gear_speed / GEAR_DEGREE_CONST; //conversion of desired angle to actal
		m_gearArm.Set(gear_speed); //set here...
	}
	//else if (GetGearTalonCurrent() > 1.5) { //if current too high, stop running...
		//SetGearMode(false); //change to percent, so sending 0% to motor, force it to percent mode
		//m_gearArm.Set(0.0);
	//}
	else { //if current is ok, not position mode, must be percent mode, assign gear_speed based on percent power to motor
		m_gearArm.Set(gear_speed);
	}

	gearCommandedSpeed = gear_speed;

	if ((GetGearMode() == true) && (gearCommandedSpeed > GetRawGearArmPosition())) {
		m_gearArm.SetPID(TALON_UP_GEAR_P, TALON_UP_GEAR_I, TALON_UP_GEAR_D);
	}
	else if ((GetGearMode() == true) && (gearCommandedSpeed < GetRawGearArmPosition())) {
		m_gearArm.SetPID(TALON_DOWN_GEAR_P, TALON_DOWN_GEAR_I, TALON_DOWN_GEAR_D);
	}
	else {
		m_gearArm.SetPID(TALON_UP_GEAR_P, TALON_UP_GEAR_I, TALON_UP_GEAR_D);
	}


}

void Gear::SetGearArmSetpoint(GearArmSetpoint setpoint) {
	switch (setpoint) {
	case 0:
		SetGearArmPosition(GEAR_GROUND); //has to go through all of the checks of the SetGearArmPosition function
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

	gearSetpoint = setpoint;
}

double Gear::GetGearCommandedSpeed() {
	return gearCommandedSpeed; //gear_speed from SetGearArmPosition function
}

double Gear::GetGearSetpoint() {
	return gearSetpoint;
}

double Gear::GetGearError() {
	return (GetGearArmPosition() - GetGearSetpoint());
}

double Gear::GearGet() {
	return (m_gearArm.Get());
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


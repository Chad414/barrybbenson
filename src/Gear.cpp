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
	  m_gearRoll(TALON_GEAR_ROLL),
	  m_gearOpen(GEAR_OPEN),
	  m_gearClose(GEAR_CLOSE)
{
	// TODO Auto-generated constructor stub

	m_rollTime = new Timer();
	m_gearArm.SetClosedLoopOutputDirection(true);
	m_gearArm.SetSensorDirection(true);
	m_gearArm.SetVoltageRampRate(0);
	m_gearArm.SetP(TALON_UP_GEAR_P);
	m_gearArm.SetI(TALON_UP_GEAR_I);
	m_gearArm.SetD(TALON_UP_GEAR_D);
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

void Gear::GameStartGearArmPosition() {
	//m_gearArm.SetPosition(GEAR_PACKAGE / GEAR_DEGREE_CONST);
	m_gearArm.SetPosition(0);
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
		m_gearArm.SetP(TALON_UP_GEAR_P);
		m_gearArm.SetI(TALON_UP_GEAR_I);
		m_gearArm.SetD(TALON_UP_GEAR_D);
	}
	else if ((GetGearMode() == true) && (gearCommandedSpeed < GetRawGearArmPosition())) {
		m_gearArm.SetP(TALON_DOWN_GEAR_P);
		m_gearArm.SetI(TALON_DOWN_GEAR_I);
		m_gearArm.SetD(TALON_DOWN_GEAR_D);
	}
	else {
		m_gearArm.SetP(TALON_UP_GEAR_P);
		m_gearArm.SetI(TALON_UP_GEAR_I);
		m_gearArm.SetD(TALON_UP_GEAR_D);
	}
}


double Gear::GetGearCommandedSpeed() {
	return gearCommandedSpeed * GEAR_DEGREE_CONST; //gear_speed from SetGearArmPosition function
}

double Gear::GetGearError() {
	return (fabs(GetGearArmPosition() - GetGearCommandedSpeed()));
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

void Gear::resetRoller() {
	m_gearRoll.SetPosition(0.0);
}

void Gear::openGearIntake(bool open) {
	if(open == true) {
		m_gearOpen.Set(true);
		m_gearClose.Set(false);
	} else {
		m_gearOpen.Set(false);
		m_gearClose.Set(true);
 	 }
}

Gear::~Gear() {
	// TODO Auto-generated destructor stub
}

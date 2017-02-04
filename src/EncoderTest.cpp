/*
 * EncoderTest.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */

#include <EncoderTest.h>
#include "Encoder.h"


EncoderTest::EncoderTest()
: m_shooter(13)
{
	m_shooter.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooter.SetSensorDirection(false);

	m_shooter.SetPID(SHOOTER_P, SHOOTER_I, SHOOTER_D);
	m_shooter.SetIzone(4096/5);
}

double EncoderTest::Get() {
	return m_shooter.GetPosition();
}

double EncoderTest::GetRate() {
	return m_shooter.GetSpeed();
}

void EncoderTest::Set(double value) {
	m_shooter.Set(value);
	shooterValue = value;
}

void EncoderTest::SetPIDPoint(double setpoint) {
	m_shooter.SetSetpoint(setpoint);

	shooterSetpoint = setpoint;
}

double EncoderTest::GetShooterSetpoint() {
	return shooterSetpoint;
}

void EncoderTest::EnableShoot() {
	m_shooter.Enable();
}

void EncoderTest::DisableShoot() {
	m_shooter.Disable();
}

EncoderTest::~EncoderTest() {
	// TODO Auto-generated destructor stub
}

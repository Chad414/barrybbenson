/*
 * EncoderTest.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */

#include <EncoderTest.h>

EncoderTest::EncoderTest()
: m_shooter(13),
  m_pid(P,I,D, m_shooter, m_shooter)
{
	m_shooter.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooter.ConfigEncoderCodesPerRev(4096);

	m_pid.SetSetpoint(4096); // 1 Rotation
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

EncoderTest::~EncoderTest() {
	// TODO Auto-generated destructor stub
}


void EncoderTest::EnablePID()
{
	if (!m_pid.IsEnabled())
	{
		m_pid.Enable();
	}
}

void EncoderTest::DisablePID()
{
	if (m_pid.IsEnabled())
	{
		m_pid.Disable();
	}
}

bool EncoderTest::OnTarget()
{
	return m_pid.OnTarget();
}

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

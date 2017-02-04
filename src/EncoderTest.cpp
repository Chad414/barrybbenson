/*
 * EncoderTest.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */

#include <EncoderTest.h>
#include "Encoder.h"


EncoderTest::EncoderTest()
: m_shooter(1)
{
	m_shooter.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
}

double EncoderTest::Get() {
	return m_shooter.GetPosition();
}

EncoderTest::~EncoderTest() {
	// TODO Auto-generated destructor stub
}

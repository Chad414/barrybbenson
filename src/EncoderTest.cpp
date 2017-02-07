/*
 * EncoderTest.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */

#include <EncoderTest.h>

EncoderTest::EncoderTest()
{

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

/*
 * EncoderTest.h
 *
 *  Created on: Feb 2, 2017
 *      Author: Robo13
 */
#include "WPILib.h"
#include "CANTalon.h"
#include "Encoder.h"

#ifndef SRC_ENCODERTEST_H_
#define SRC_ENCODERTEST_H_

class EncoderTest {
public:
	EncoderTest();
	virtual ~EncoderTest();

	double Get();
	void Set(double value);
private:
	CANTalon m_shooter;
};

#endif /* SRC_ENCODERTEST_H_ */

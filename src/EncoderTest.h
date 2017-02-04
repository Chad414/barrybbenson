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

#define SHOOTER_P 0.0
#define SHOOTER_I 0.0
#define SHOOTER_D 0.0

class EncoderTest {
public:
	EncoderTest();
	virtual ~EncoderTest();

	double Get();
	double GetRate();
	void Set(double value);
	void SetPIDPoint(double setpoint);
	double GetShooterSetpoint();
	void EnableShoot();
	void DisableShoot();
private:
	CANTalon m_shooter;
	double shooterValue;
	double shooterSetpoint;
};

#endif /* SRC_ENCODERTEST_H_ */

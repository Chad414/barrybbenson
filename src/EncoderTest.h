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

#define SHOOTER_P 0.1
#define SHOOTER_I 0.0
#define SHOOTER_D 0.0

class EncoderTest {
public:
	EncoderTest();
	virtual ~EncoderTest();

	double Get(); //position
	double GetRate(); //number of rotations
	void Set(double value); //set value from 0 to 1.0 to talon directly

	/*void EncoderPIDWrite(double output);
	double EncoderPIDGet();
	double EncoderGetPIDOutput();

	bool ShooterAtSetpoint();
	void SetPIDPoint(double setpoint);
	double GetShooterSetpoint();

	bool ShooterIsEnabled();
	void EnableShoot();
	void DisableShoot();*/
private:
	CANTalon m_shooter;

	/*double shooterValue;
	double shooterSetpoint;
	double shooterPIDOutput;*/
};

#endif /* SRC_ENCODERTEST_H_ */

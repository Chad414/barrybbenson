/*
 * Intake.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Robo13
 */
#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include <CANTalon.h>

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_
#define TALON_INTAKE_ROLLER 1

#define SOLENOID_INTAKE_ARM_OUT 9
#define SOLENOID_INTAKE_ARM_IN 10

#define SOLENOID_HOPPER_OUT 4
#define SOLENOID_HOPPER_IN 5

class Intake {
private:
	CANTalon m_intakeRoller;

	Solenoid m_intakeArmOut;
	Solenoid m_intakeArmIn;

	//Solenoid m_hopperOut;
	//Solenoid m_hopperIn;

	DoubleSolenoid m_hopper;

	bool IntakeArm;
	bool Hopper;
	double IntakeRoller;
public:
	Intake();
	void SetIntakeArm(bool on);
	void SetIntakeRoller(double value);
	double GetIntakeRoller();

	bool GetIntakeArm();
	void SetHopper(bool on);
	bool GetHopper();
	virtual ~Intake();



};

#endif /* SRC_INTAKE_H_ */

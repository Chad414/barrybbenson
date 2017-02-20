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
#define SOLENOID_INTAKE_ARM 0

class Intake {
private:
	CANTalon * m_intakeRoller;
	Solenoid m_intakeArm;

	bool ArmStatus;
public:
	Intake();
	void SetArm(bool on);
	bool GetArm();
	void SetRoller(double value);

	virtual ~Intake();



};

#endif /* SRC_INTAKE_H_ */

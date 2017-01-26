/*
 * Intake.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Robo13
 */
#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "Solenoid.h"

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_
#define TALON_INTAKE_ROLLER 0
#define SOLENOID_INTAKE_ARM 0

class Intake {
private:
	CANTalon* m_intakeRoller;
	Solenoid* m_intakeArm;
public:
	Intake();
	void SetArm(bool on);
	void ApplyArm();
	void ReleaseArm();
	void ApplyRoller();
	void StopRoller();
	virtual ~Intake();



};

#endif /* SRC_INTAKE_H_ */

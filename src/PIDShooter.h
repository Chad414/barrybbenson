/*
 * PIDShooter.h
 *
 *  Created on: Feb 4, 2017
 *      Author: ROBO-PGM06
 */
#include "WPILib.h"
#include <CANTalon.h>
#include "RobotUtils/RobotUtils.h"

#ifndef SRC_PIDSHOOTER_H_
#define SRC_PIDSHOOTER_H_

class PIDShooter {
private:

	CANTalon * m_shooter1;
	CANTalon * m_shooter2;
	CANTalon * m_paddle;

	Talon * shooter;

	PIDController * m_shooterPID;

	Encoder * m_shooterEncoder;

	PowerDistributionPanel* m_pdp;

	Timer * m_shooterTime;

	SmartDashboard * m_dashboard;

	double shooterSetpoint;
public:
	PIDShooter( double p, double i, double d );
	virtual ~PIDShooter();

	void SetDevice();
	void Enable();
	void DisableShooter();
	void SetSetpoint( double setpoint );

	double GetSetpoint();
	double GetRate();
	double GetDistanceToSetpoint();
};

#endif /* SRC_PIDSHOOTER_H_ */

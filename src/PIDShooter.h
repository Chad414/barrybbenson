/*
 * PIDShooter.h
 *
 *  Created on: Feb 4, 2017
 *      Author: ROBO-PGM06
 */
#include "WPILib.h"
#include "CANTalon.h"
#include "RobotUtils/RobotUtils.h"

#ifndef SRC_PIDSHOOTER_H_
#define SRC_PIDSHOOTER_H_

#define SHOOTER_P .020
#define SHOOTER_I .0001
#define SHOOTER_D 0.0
#define SHOOTER_F .03325

#define LOW_SETPOINT 2500
#define HI_SETPOINT 2750

class PIDShooter {
private:

	CANTalon * m_shooterL;
	CANTalon * m_shooterR;
	CANTalon * m_paddle;

	CANTalon * m_feeder;

	PowerDistributionPanel* m_pdp;

	Timer * m_shooterTime;

	SmartDashboard * m_dashboard;

	double shooterSetpoint;

	double p, i, d;
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
	double GetShooterP();
	double GetShooterI();
	double GetShooterD();
	double GetShooterF();
	double GetOutputCurrent();
	double GetPosition();
	double GetSpeed();
	double GetError();
	double GetSpeedGet();



	void OutputValues( SmartDashboard * dashboard );
};

#endif /* SRC_PIDSHOOTER_H_ */

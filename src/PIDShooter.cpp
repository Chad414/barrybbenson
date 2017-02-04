/*
 * PIDShooter.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: ROBO-PGM06
 */

#include "PIDShooter.h"
#include <WPILib.h>

PIDShooter::PIDShooter( double p, double i, double d ) {
	// TODO Auto-generated constructor stub
	m_shooter1 = new CANTalon(13);

	m_shooter1->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );

	m_shooterPID = new PIDController( p, i, d, m_shooter1, m_shooter1 );

	m_shooterTime = new Timer();

	m_pdp = new PowerDistributionPanel( 0 );

	m_dashboard = new SmartDashboard;
}

PIDShooter::~PIDShooter() {
	// TODO Auto-generated destructor stub
}

void PIDShooter::SetDevice()
{
	m_shooter1->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );
}

void PIDShooter::Enable()
{
	m_shooter1->Enable();
}

void PIDShooter::DisableShooter()
{
	m_shooter1->SetSetpoint(0);
	m_shooter1->Reset();
}

void PIDShooter::SetSetpoint( double setpoint)
{
	m_shooter1->SetSetpoint( setpoint );

	shooterSetpoint = setpoint;
}

double PIDShooter::GetRate()
{
	return m_shooter1->GetSpeed();
}

double PIDShooter::GetSetpoint()
{
	return shooterSetpoint;
}










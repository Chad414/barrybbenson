/*
 * PIDShooter.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: ROBO-PGM06
 */

#include "PIDShooter.h"

PIDShooter::PIDShooter( double p, double i, double d ) {
	// TODO Auto-generated constructor stub
	m_shooter1 = new CANTalon(13);

	m_shooter1->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );

	m_shooter1->SetControlMode(CANTalon::kSpeed);
	m_shooter1->SetPID(SHOOTER_P, SHOOTER_I, SHOOTER_D);
	m_shooter1->SetF(SHOOTER_F);
	m_shooter1->Enable();
	m_shooter1->SetAllowableClosedLoopErr(0);
	m_shooter1->SetSensorDirection(false);
	m_shooter1->SetClosedLoopOutputDirection(true);
	m_shooter1->ConfigNominalOutputVoltage(+0.0F, -0.0F);
	m_shooter1->ConfigPeakOutputVoltage(+12.0F, -12.0F);
	m_shooter1->SetCloseLoopRampRate(65);

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

double PIDShooter::GetP()
{
	return m_shooter1->GetP();
}

double PIDShooter::GetI()
{
	return m_shooter1->GetI();
}

double PIDShooter::GetD()
{
	return m_shooter1->GetD();
}

double PIDShooter::GetF()
{
	return m_shooter1->GetF();
}

double PIDShooter::GetOutputCurrent()
{
	return m_shooter1->GetOutputCurrent();
}

double PIDShooter::GetPosition()
{
	return m_shooter1->GetPosition();
}

double PIDShooter::GetSpeed()
{
	return m_shooter1->GetSpeed();
}

double PIDShooter::GetError()
{
	return m_shooter1->GetClosedLoopError();
}





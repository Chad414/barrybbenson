/*
 * MPController.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Jakob
 */

#include <MPController.h>

MPController::MPController(
		PIDF pidf,
		ArrayDimension2 *trajectoryPoints,
		CANTalon *talon,
		double deadband) :
		m_pidf(pidf),
		m_trajectoryPoints(trajectoryPoints),
		m_talon(talon),
		isEnabled(false),
		m_deadband(deadband),
		m_notifier(&MPController::Periodic, this){
	double notifierTime = m_trajectoryPoints->at(0)[2] / 2;
	m_notifier.StartPeriodic(notifierTime);
}


void MPController::SetPIDF(PIDF pidf)
{
	m_pidf = pidf;
}

void MPController::Control()
{
	if (!isEnabled)
		return;

	CANTalon::MotionProfileStatus status;
	m_talon->GetMotionProfileStatus(status);

	m_talon->SetControlMode(CANTalon::kMotionProfile);
	m_talon->SelectProfileSlot(1);
	m_talon->SetPID(m_pidf.p, m_pidf.i, m_pidf.d);
	m_talon->SetF(m_pidf.f);
	m_talon->SetAllowableClosedLoopErr(m_deadband);

	double targetDistance = m_trajectoryPoints->
			at(m_trajectoryPoints->size()-1)[0];
	if (m_talon->GetPosition() >= targetDistance)
	{
		Disable();
	}
	else if (status.btmBufferCnt >= MINIMUM_POINTS_IN_TALON)
	{
		m_talon->Set(CANTalon::SetValueMotionProfileEnable);
	}
}


void MPController::Enable()
{
	isEnabled = true;
	Fill();
	Control();
}


bool MPController::IsEnabled()
{
	return isEnabled;
}


void MPController::Disable()
{
	m_talon->SetControlMode(CANTalon::kPercentVbus);
	m_talon->Set(0);
	m_talon->SetPosition(0);
	isEnabled = false;
}


void MPController::Fill()
{
	CANTalon::TrajectoryPoint point;

	m_talon->ClearMotionProfileTrajectories();

	for (int i = 0; i < m_trajectoryPoints->size(); ++i)
	{
		std::vector<double> p = m_trajectoryPoints->at(i);

		point.position = p[0];
		point.velocity = p[1];
		point.timeDurMs = (int)p[2];

		point.velocityOnly = false;

		point.zeroPos = false;

		if (i == 0)
			point.zeroPos = true;
		if ((i + 1) == m_trajectoryPoints->size())
			point.isLastPoint = true;

		m_talon->PushMotionProfileTrajectory(point);
	}
}


void MPController::Periodic()
{
	m_talon->ProcessMotionProfileBuffer();
}


bool MPController::OnTarget()
{
	double p = m_talon->GetPosition();
	double t = m_trajectoryPoints->at(
			m_trajectoryPoints->size()-1)[0];

	return (t - m_deadband < p < t + m_deadband);
}

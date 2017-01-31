/*
 * MPController.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: Jakob
 */

#include <MPController.h>

#include "MotorConstants.h"

#define USE_MOTION_PROFILE_ONLY

MPController::MPController(
		const double trajectories[128][3],
		int count,
		double interval,
		double p,
		double i,
		double d,
		CANTalon *talon,
		MotorType motor,
		double target,
		double maximumVelocity)
:
	mp_trajectories(trajectories),
	mp_count(count),
	mp_interval(interval),
	m_distancePID(p, i, d, talon, talon),
	m_talon(talon),
	m_motor(motor),
	mp_maximumAcceleration(MotorAccelerations[m_motor]),
	mp_controlLoop(&MPController::PeriodicTask, this),
	mp_state(MPDisabled),
	mp_currentPoint(0),
	mp_target(target),
	mp_maximumVelocity(maximumVelocity)
	{

}



void MPController::Enable()
{
	if (IsEnabled())
		return;

	mp_state = MPMotionProfile;

	m_talon->SetControlMode(CANTalon::ControlMode::kPercentVbus);

	mp_controlLoop.StartPeriodic(mp_interval);
}


void MPController::Disable()
{
	if (!IsEnabled())
		return;

	mp_controlLoop.Stop();
	mp_state = MPDisabled;
}

void MPController::PeriodicTask()
{
	double percentage;
	switch (mp_state)
	{
	case MPDisabled:
		return;

	case MPMotionProfile:
		if (mp_currentPoint + 1 == mp_count)
		{
			mp_state = MPDistancePID;
			goto MPDistancePID;
		}

		percentage = (mp_trajectories[(int)mp_currentPoint][1]) / mp_maximumVelocity;
		m_talon->Set(percentage);
		break;

	MPDistancePID:
	case MPDistancePID:
#ifndef USE_MOTION_PROFILE_ONLY
		if (!m_distancePID->IsEnabled())
		{
			m_distancePID->SetSetpoint(mp_target);
			m_distancePID->Enable();
		}
		else if (m_distancePID->OnTarget())
		{
			mp_state = MPOnTarget;
			m_distancePID->Disable();
		}
	}
#else
	break;
}
}
#endif



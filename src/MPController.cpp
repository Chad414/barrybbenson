/*
 * MPController.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: Jakob
 */

#include <MPController.h>

#include "MotorConstants.h"

#define USE_MOTION_PROFILE_ONLY

using namespace std;

MPController::MPController(
		std::vector<std::vector<double>> trajectories,
		int count,
		double interval,
		double p,
		double i,
		double d,
		CANTalon *talon,
		double target,
		double maximumVelocity)
:
	mp_trajectories(trajectories),
	mp_count(trajectories.size()),
	mp_interval(interval),
	m_distancePID(p, i, d, talon, talon),
	m_talon(talon),
	mp_maximumAcceleration(14),
	mp_state(MPDisabled),
	mp_currentPoint(0),
	mp_target(target),
	mp_maximumVelocity(maximumVelocity),
	mp_previousPosition(0)
	{
	mp_controlLoop = std::make_unique<Notifier>(&MPController::PeriodicTask, this);
}



void MPController::Enable()
{
	cout << "Locking Mutex: Enabling" << endl;
	std::lock_guard<priority_recursive_mutex> sync(m_mutex);
	if (IsEnabled())
	{
		cout << "Already Enabled" << endl;
		return;
	}

	m_talon->SetEncPosition(0);
	mp_state = MPMotionProfile;

	m_talon->SetControlMode(CANTalon::ControlMode::kPercentVbus);

	cout << "Starting Periodic" << endl;

	mp_controlLoop->StartPeriodic(mp_interval);

	cout << "Started Periodic" << endl;
}


void MPController::Disable()
{
	cout << "Locking Mutex: Disabling" << endl;
	std::lock_guard<priority_recursive_mutex> sync(m_mutex);
	if (mp_state == MPDisabled)
	{
		cout << "Already Disabled" << endl;
		return;
	}

	cout << "Disabling" << endl;

	mp_state = MPDisabled;

	cout << "Stopping Periodic" << endl;

	// mp_controlLoop->Stop();

	cout << "Stopped Periodic" << endl;

	mp_currentPoint = 0;
}

void MPController::PeriodicTask()
{
	std::lock_guard<priority_recursive_mutex> sync(m_secondaryMutex);
	Periodic();
}

void MPController::Periodic()
{
	double percentage;
	switch (mp_state)
	{
	case MPDisabled:
		cout << "Disabled Periodic At Interval " << mp_interval << endl;
		return;

	case MPMotionProfile:
	{
		std::lock_guard<priority_recursive_mutex> sync(m_mutex);
		if (mp_currentPoint + 1 == mp_count)
		{
			mp_state = MPDistancePID;
			cout << "Finished Motion Profiling" << endl;
			break;
		}

		percentage = (mp_trajectories[(int)mp_currentPoint][1]) / mp_maximumVelocity;
		m_talon->Set(percentage);

		/*
		std::cout << "Motor Set: " << percentage << endl;
		std::cout << "Trajectory Point Velocity: " << mp_trajectories[(int)mp_currentPoint][1] << endl;
		std::cout << "Motor Mode: MotionProfiling" << endl;
		*/

		mp_currentPoint++;
		break;
	}

	case MPDistancePID:
	{
		std::lock_guard<priority_recursive_mutex> sync(m_mutex);
		Disable();
		std::cout << "Motor Mode: PIDController" << endl;
		break;


		if (!m_distancePID.IsEnabled())
		{
			m_distancePID.SetSetpoint(mp_target);
			m_distancePID.Enable();
		}
		else if (m_distancePID.OnTarget())
		{
			mp_state = MPOnTarget;
			m_distancePID.Disable();
		}
		break;
	}
	case MPOnTarget:
	{
		std::lock_guard<priority_recursive_mutex> sync(m_mutex);
		mp_state = MPDisabled;
		break;
	}
	}

}

void MPController::LogValues()
{
	std::lock_guard<priority_recursive_mutex> sync(m_mutex);
	SmartDashboard::PutNumber("Encoder Position", m_talon->GetPosition());
	SmartDashboard::PutNumber("Encoder Speed", m_talon->GetSpeed());
	SmartDashboard::PutNumber("Encposition", m_talon->GetEncPosition());
}

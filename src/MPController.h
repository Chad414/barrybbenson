/*
 * MPController.h
 *
 *  Created on: Jan 31, 2017
 *      Author: Jakob
 */

#ifndef SRC_MPCONTROLLER_H_
#define SRC_MPCONTROLLER_H_

#include <WPILib.h>
#include <CANTalon.h>

#include <vector>
#include <atomic>
#include <memory>
#include <queue>
#include <string>

#include "MotorConstants.h"

using namespace std;

enum MPState {
	MPDisabled,
	MPMotionProfile,
	MPDistancePID,
	MPOnTarget
};

class MPController {
private:

	PIDController m_distancePID;

	CANTalon *m_talon;

	std::vector<std::vector<double>> mp_trajectories;
	double mp_count;
	double mp_interval;
	double mp_target;

	double mp_maximumVelocity;
	double mp_maximumAcceleration;

	double mp_currentPoint;

	double mp_previousPosition;

	mutable priority_recursive_mutex m_mutex;
	mutable priority_recursive_mutex m_secondaryMutex;

	std::unique_ptr<Notifier> mp_controlLoop;

	MPState mp_state;

public:
	MPController(
			std::vector<std::vector<double>> trajectories,
			int count,
			double interval,
			double p,
			double i,
			double d,
			CANTalon *talon,
			double target,
			double maximumVelocity);

	void PeriodicTask();

	void Enable();
	void Disable();
	MPState GetState() { return mp_state; }
	bool OnTarget() { return GetState() == MPOnTarget; }
	bool IsEnabled() { return (mp_state == MPMotionProfile || mp_state == MPDistancePID); }

	void LogValues();

	void Periodic();
};

#endif /* SRC_MPCONTROLLER_H_ */

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

#include "MotorConstants.h"

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
	MotorType m_motor;

	const double mp_trajectories[128][3];
	double mp_count;
	double mp_interval;
	double mp_target;

	double mp_maximumVelocity;
	double mp_maximumAcceleration;

	double mp_currentPoint;

	Notifier mp_controlLoop;

	MPState mp_state;

public:
	MPController(
			const double trajectories[128][3],
			int count,
			double interval,
			double p,
			double i,
			double d,
			CANTalon *talon,
			MotorType motor,
			double target,
			double maximumVelocity);

	void PeriodicTask();

	void Enable();
	void Disable();
	MPState GetState() { return mp_state; }
	bool OnTarget() { return GetState() == MPOnTarget; }
	bool IsEnabled() { return (mp_state == MPMotionProfile || mp_state == MPDistancePID); }
};

#endif /* SRC_MPCONTROLLER_H_ */

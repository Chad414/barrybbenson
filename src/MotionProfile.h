/*
 * MotionProfile.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#ifndef SRC_MOTIONPROFILE_H_
#define SRC_MOTIONPROFILE_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "TrajectoryPoints.h"
#include "Instrumentation.h"

class MotionProfile {
public:
	MotionProfile(CANTalon & talon);
	void PeriodicTask();
	void Reset();
	void Control();
	void startFilling();
	void startFilling(const double profile[][3], int totalCnt);
	void Start();
	CANTalon::SetValueMotionProfile getSetValue() const;

	virtual ~MotionProfile();

	CANTalon & m_talon;
	Notifier m_notifer;
	CANTalon::MotionProfileStatus status;
	CANTalon::SetValueMotionProfile setValue = CANTalon::SetValueMotionProfileDisable;
	CANTalon::TrajectoryPoint point;

	int state = 0;
	int loopTimeout = -1;
	bool bStart = false;
	static const int kMinPointsInTalon = 5;
	static const int kNumLoopsTimeout = 10;

private:

};

#endif /* SRC_MOTIONPROFILE_H_ */

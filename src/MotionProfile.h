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
	void PeriodicTask(); // Moves bottom buffer to top buffer each iteration
	void Reset(); // Resets Talon memory and buffer
	void Control(); // Called every loop
	void startFilling(); // Fills first Trajectory points
	void startFilling(const double profile[][3], int totalCnt); // Fills Trajectory Points to buffer
	void Start(); // Sets bStart to true and starts firing trajectories
	CANTalon::SetValueMotionProfile getSetValue() const; // setValue getter function

	virtual ~MotionProfile();

	CANTalon & m_talon; // Local talon
	Notifier m_notifer;
	CANTalon::MotionProfileStatus status;
	CANTalon::SetValueMotionProfile setValue = CANTalon::SetValueMotionProfileDisable; // setValue automatically set to Disable
	CANTalon::TrajectoryPoint point; // Local trajectory point

	int state = 0; // Current state disabled
	int loopTimeout = -1;
	bool bStart = false;
	static const int kMinPointsInTalon = 5; // Hoe many trajectory points the Talon should wait fore before firing
	static const int kNumLoopsTimeout = 10; // Timeout every 10 loops

private:

};

#endif /* SRC_MOTIONPROFILE_H_ */

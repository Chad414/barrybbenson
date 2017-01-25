/*
 * MotionProfile.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#include "MotionProfile.h"

MotionProfile::MotionProfile(CANTalon & talon) : m_talon(talon), m_notifer(&MotionProfile::PeriodicTask, this) {
	m_talon.ChangeMotionControlFramePeriod(.5); // Set to half of trajectory point time
	m_notifer.StartPeriodic(0.005);
}

void MotionProfile::PeriodicTask() {
	m_talon.ProcessMotionProfileBuffer();
}

void MotionProfile::Reset() {
	m_talon.ClearMotionProfileTrajectories();
	setValue = CANTalon::SetValueMotionProfileDisable;
	state = 0;
	std::cout << "MP State set to: 0" << std::endl;
	loopTimeout = -1;
	bStart = false;
}

void MotionProfile::Control() {
	m_talon.GetMotionProfileStatus(status);

	if (loopTimeout < 0) {
		// Do Nothing, loopTimeout set to -1 when disabled
	} else {
		if (loopTimeout == 0) {
			Instrumentation::OnNoProgress();
		} else {
			--loopTimeout;
		}
	}

	if (m_talon.GetControlMode() != CANTalon::ControlMode::kMotionProfile) {
		state = 0;
		std::cout << "MP State set to: 0" << std::endl;
	} else {
		switch (state) {
		case 0: // When disabled
			if (bStart) {
				bStart = false;

				setValue = CANTalon::SetValueMotionProfileDisable;
				startFilling();

				state = 1;
				std::cout << "MP State set to: 1" << std::endl;
				loopTimeout = kNumLoopsTimeout;
			}
			break;
		case 1:
			if (status.btmBufferCnt > kMinPointsInTalon) {
				setValue = CANTalon::SetValueMotionProfileEnable;

				m_talon.Set(setValue);
				state = 2;
				std::cout << "MP state set to: 2" << std::cout;
				loopTimeout = kNumLoopsTimeout;
			}
			break;
		case 2:
			if (status.isUnderrun == false) {
				loopTimeout = kNumLoopsTimeout;
			}

			if (status.activePointValid && status.activePoint.isLastPoint) {
				setValue = CANTalon::SetValueMotionProfileHold;
				state = 0;
				std::cout << "MP State set to: 0" << std::endl;
				loopTimeout = -1;
			}
			break;
		}
	}
	Instrumentation::Process(status);
}

void MotionProfile::startFilling() {
	startFilling(kMotionProfile, kMotionProfileSz);
}

CANTalon::SetValueMotionProfile var;

void MotionProfile::startFilling(const double profile[][3], int totalCnt) {
	if(status.hasUnderrun) {
		Instrumentation::OnUnderrun();
		m_talon.ClearMotionProfileHasUnderrun();
	}
	CANTalon::TrajectoryPoint point; // Local trajectory point

	m_talon.ClearMotionProfileTrajectories();

	for(int i = 0; i < totalCnt; ++i){
		point.position = profile[i][0];

		point.velocity = profile[i][1];
		point.timeDurMs = (int) profile[i][2];
		point.profileSlotSelect = 1;

		point.velocityOnly = false;
		point.zeroPos = false;
		if (i == 0) {
			point.zeroPos = true;
		}
		point.isLastPoint = false;
		if ((i + 1) == totalCnt) {
			point.isLastPoint = true;
		}

		m_talon.PushMotionProfileTrajectory(point);
		std::cout << "Pushed Trajectory Points to Talon Buffer" << std::endl;
	}
}

void MotionProfile::Start() {
	bStart = true;
	std::cout << "MotionProfiling Start Function Called and bStart set to: true" << std::end;
}

CANTalon::SetValueMotionProfile MotionProfile::getSetValue() const {
	return setValue;
}

MotionProfile::~MotionProfile() {
}


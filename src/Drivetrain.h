/*
 * Drivetrain.h
 *
 *  Created on: Jan 11, 2017
 *      Author: Chad
 */

#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

#include "WPILib.h"
#include <cmath>
#include "CANTalon.h"
#include "MotionProfile.h"

#define TALON_DRIVE_LF 0
#define TALON_DRIVE_LR 1
#define TALON_DRIVE_RF 2
#define TALON_DRIVE_RR 3

#define DRIVE_ENCODER_LF 4
#define DRIVE_ENCODER_LR 3
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 1
class Drivetrain {
public:
	Drivetrain();
	void ArcadeDrive(double speed, double angle);
	void startMP();
	void resetMP();
	void controlMP();
	virtual ~Drivetrain();

private:
	CANTalon m_lDriveF;
	CANTalon m_lDriveR;
	CANTalon m_rDriveF;
	CANTalon m_rDriveR;

	RobotDrive m_drive;

	Encoder m_lEncoder;
	Encoder m_rEncoder;

	MotionProfile m_MotionProfile;

	Timer m_timer;

	double m_turn, m_speed;
};

#endif /* SRC_DRIVETRAIN_H_ */

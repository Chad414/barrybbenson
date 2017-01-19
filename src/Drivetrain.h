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

#define TALON_DRIVE_LF 0
#define TALON_DRIVE_LR 1
#define TALON_DRIVE_RF 2
#define TALON_DRIVE_RR 3

#define DRIVE_ENCODER_LF 0
#define DRIVE_ENCODER_LR 1
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 3

class Drivetrain {
public:
	Drivetrain();
	virtual ~Drivetrain();

private:
	CANTalon m_lDriveF;
	CANTalon m_lDriveR;
	CANTalon m_rDriveF;
	CANTalon m_rDriveR;

	Encoder m_lEncode;
	Encoder m_rEncode;

	Timer m_timer;

	RobotDrive m_drive;
};

#endif /* SRC_DRIVETRAIN_H_ */

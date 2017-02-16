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
#include "MPController.h"
#include "MP.h"

#define TALON_DRIVE_LF 11
#define TALON_DRIVE_LR 12
#define TALON_DRIVE_RF 21
#define TALON_DRIVE_RR 20

#define DRIVE_ENCODER_LF 4
#define DRIVE_ENCODER_LR 3
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 1

#define DRIVE_P_R 0.00005
#define DRIVE_I_R 0.001
#define DRIVE_D_R 0.0
#define DRIVE_F_R 0.0

#define DRIVE_P_L 0.00005
#define DRIVE_I_L 0.001
#define DRIVE_D_L 0.0
#define DRIVE_F_L 0.0

const PIDF PIDF_LEFT = {
		DRIVE_P_L,
		DRIVE_I_L,
		DRIVE_D_L,
		DRIVE_F_L};

const PIDF PIDF_RIGHT = {
		DRIVE_P_R,
		DRIVE_I_R,
		DRIVE_D_R,
		DRIVE_F_R};


#define ENCODER_CODES_PER_REVOLUTION 256

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

	Timer m_timer;

	MPController m_leftMotionProfile;
	MPController m_rightMotionProfile;

	double m_turn, m_speed;
};

#endif /* SRC_DRIVETRAIN_H_ */

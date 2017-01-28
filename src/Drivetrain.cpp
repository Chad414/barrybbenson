/*
 * Drivetrain.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: Chad
 */

#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_drive(&m_lDriveF, &m_lDriveR, &m_rDriveF, &m_rDriveR),
	m_lEncoder(DRIVE_ENCODER_LF, DRIVE_ENCODER_LR, true),
	m_rEncoder(DRIVE_ENCODER_RF, DRIVE_ENCODER_RR, false),
	m_MotionProfile(m_rDriveR)
{

	m_turn = 0;
	m_speed = 0;

	m_rDriveR.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rDriveR.SetSensorDirection(true);

	m_rDriveR.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);
}

void Drivetrain::InitTeleop()
{
	m_rDriveR.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_rDriveR.Set(0);
}


void Drivetrain::ArcadeDrive(double speed, double angle){
	m_drive.SetSafetyEnabled(true);
	m_speed = speed;
	m_turn = angle;
	m_drive.ArcadeDrive(speed, angle);
	cout << (int)m_rDriveR.GetControlMode() << endl;
}

void Drivetrain::startMP() {
	/*
	m_rDriveR.SetControlMode(CANTalon::ControlMode::kFollower);
	m_rDriveR.Set(TALON_DRIVE_LR);
	*/

	m_MotionProfile.Start();

}

void Drivetrain::resetMP() {
	m_MotionProfile.Reset();
}

void Drivetrain::controlMP() {
	m_MotionProfile.Control();
}

Drivetrain::~Drivetrain() {
}

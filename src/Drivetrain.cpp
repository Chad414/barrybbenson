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
	m_leftMotionProfile(PIDF_LEFT, &testMotionProfile, m_lDriveF),
	m_rightMotionProfile(PIDF_RIGHT, &testMotionProfile, m_rDriveF)
{

	m_turn = 0;
	m_speed = 0;

	m_lDriveR.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_lDriveR.SetSensorDirection(true);

	m_lDriveR.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);
}

void Drivetrain::ArcadeDrive(double speed, double angle){
	m_drive.SetSafetyEnabled(true);
	m_speed = speed;
	m_turn = angle;
	m_drive.ArcadeDrive(speed, angle);
}

void Drivetrain::startMP() {
	m_leftMotionProfile.Enable();
	m_rightMotionProfile.Enable();

}

void Drivetrain::resetMP() {
	m_leftMotionProfile.Disable();
	m_rightMotionProfile.Disable();
}

void Drivetrain::controlMP() {
	m_leftMotionProfile.Control();
	m_rightMotionProfile.Control();
}

Drivetrain::~Drivetrain() {
}

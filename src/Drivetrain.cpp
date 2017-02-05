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
	m_motionProfileController(
			kMotionProfile(),
			kMotionProfile().size(),
			kMotionProfile()[0][2],
			0.0,
			0.0,
			0.0,
			&m_rDriveR,
			0,
			18)
{
	m_turn = 0;
	m_speed = 0;

	m_rDriveR.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rDriveR.SetSensorDirection(false);

	m_rDriveR.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);
}

void Drivetrain::LogValues()
{
	m_motionProfileController.LogValues();
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
	//m_rDriveR.Set(.1);
}

void Drivetrain::startMP() {
	m_motionProfileController.Enable();
}

void Drivetrain::resetMP() {
	m_motionProfileController.Disable();
}

void Drivetrain::controlMP() {
}

Drivetrain::~Drivetrain() {
}

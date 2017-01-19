/*
 * Drivetrain.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: Chad
 */

#include <Drivetrain.h>

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveR(TALON_DRIVE_RR),
	m_drive(&m_lDriveF, &m_lDriveR, &m_rDriveF, &m_rDriveR),
	m_lEncode(DRIVE_ENCODER_LF, DRIVE_ENCODER_LR, true),
	m_rEncode(DRIVE_ENCODER_RF, DRIVE_ENCODER_RR, false)
{

}

Drivetrain::~Drivetrain() {
}

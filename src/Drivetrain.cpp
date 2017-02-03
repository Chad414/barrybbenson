/*
 * Drivetrain.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: Chad
 */

#include "Drivetrain.h"

Drivetrain::Drivetrain()
	: m_lDriveF(TALON_DRIVE_LF),
	m_lDriveM(TALON_DRIVE_LM),
	m_lDriveR(TALON_DRIVE_LR),
	m_rDriveF(TALON_DRIVE_RF),
	m_rDriveM(TALON_DRIVE_RM),
	m_rDriveR(TALON_DRIVE_RR),
	m_driveWrapperL(&m_lDriveF, &m_lDriveM),
	m_driveWrapperR(&m_rDriveF, &m_rDriveM),
	m_drive(m_driveWrapperL, m_lDriveR, m_driveWrapperR, m_rDriveR),
	m_gyro(I2C::Port::kMXP),
	m_lEncoder(DRIVE_ENCODER_LF, DRIVE_ENCODER_LR, true),
	m_rEncoder(DRIVE_ENCODER_RF, DRIVE_ENCODER_RR, false),
	m_MotionProfile(m_rDriveR)
{

	m_turn = 0;
	m_speed = 0;

	m_lDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_lDriveF.SetSensorDirection(true);
	m_rDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rDriveF.SetSensorDirection(true);


	m_rDriveR.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);
}

// DriveWrapper Functions

Drivetrain::DriveWrapper::DriveWrapper(SpeedController* talon1, SpeedController* talon2) {
	m_drive1 = talon1;
	m_drive2 = talon2;
}

void Drivetrain::DriveWrapper::Set(double speed) {
	m_drive1->Set(speed);
	m_drive2->Set(speed);
}

double Drivetrain::DriveWrapper::Get() const {
	return m_drive1->Get();
}

void Drivetrain::DriveWrapper::PIDWrite(double output) {
	Set(output);
}

void Drivetrain::DriveWrapper::SetInverted(bool isInverted) {
	m_drive1->SetInverted(isInverted);
	m_drive2->SetInverted(isInverted);
}

bool Drivetrain::DriveWrapper::GetInverted() const {
	return m_drive1->GetInverted();
}

void Drivetrain::DriveWrapper::Disable() {
	m_drive1->Disable();
	m_drive2->Disable();
}

void Drivetrain::DriveWrapper::StopMotor() {
	m_drive1->StopMotor();
	m_drive2->StopMotor();
}

// Drivetrain Functions

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

void Drivetrain::controlMP() { // Calls Control() from MotionProfile
	m_MotionProfile.Control();
}

float Drivetrain::getYaw(){ // Get Gyro Yaw
	return m_gyro.GetYaw();
}

void Drivetrain::resetGyro() {
	m_gyro.Reset();
}

double Drivetrain::getLeftEncoder() {
	return m_lDriveF.GetPosition();
}

double Drivetrain::getRightEncoder() {
	return m_rDriveF.GetPosition();
}

Drivetrain::~Drivetrain() {
}

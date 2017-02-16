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
	m_leftMotionProfile(PIDF_LEFT, testMotionProfile, m_lDriveF),
	m_rightMotionProfile(PIDF_RIGHT, testMotionProfile, m_rDriveF),
	m_distancePIDWrapper(this),
	m_distancePIDL(PIDF_LEFT.p, PIDF_LEFT.i, PIDF_LEFT.d, PIDF_LEFT.f, m_distancePIDWrapper, m_distancePIDWrapper)
	//m_distancePIDR(PIDF_RIGHT.p, PIDF_RIGHT.i, PIDF_RIGHT.d, PIDF_RIGHT.f, m_distancePIDWrapper, m_distancePIDWrapper)
{

	m_turn = 0;
	m_speed = 0;

	m_lDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_lDriveF.SetSensorDirection(true);
	m_rDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rDriveF.SetSensorDirection(true);

	m_rDriveF.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);
	m_lDriveF.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);
}


// DriveWrapper Functions

Drivetrain::DriveWrapper::DriveWrapper(SpeedController* talon1, SpeedController* talon2) {
	m_drive1 = talon1;
	m_drive2 = talon2;
}

void Drivetrain::LogValues()
{
	SmartDashboard::PutNumber("Left Encoder Speed", m_rDriveF.GetSpeed());
	SmartDashboard::PutNumber("Right Encoder Speed", m_rDriveR.GetSpeed());

	SmartDashboard::PutNumber("Left Encoder Position", m_rDriveF.GetPosition());
	SmartDashboard::PutNumber("Right Encoder Position", m_rDriveR.GetPosition());

	PIDF_LEFT.p = SmartDashboard::GetNumber("Left P", 0);
	PIDF_LEFT.i = SmartDashboard::GetNumber("Left I", 0);
	PIDF_LEFT.d = SmartDashboard::GetNumber("Left D", 0);

	PIDF_RIGHT.p = SmartDashboard::GetNumber("Right P", 0);
	PIDF_RIGHT.i = SmartDashboard::GetNumber("Right I", 0);
	PIDF_RIGHT.d = SmartDashboard::GetNumber("Right D", 0);
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

// DistancePIDWrapper Functions

Drivetrain::DistancePIDWrapper::DistancePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::DistancePIDWrapper::~DistancePIDWrapper() {
}

double Drivetrain::DistancePIDWrapper::PIDGet () {
	return(m_drivetrain->getLeftEncoder());
}

void Drivetrain::DistancePIDWrapper::PIDWrite(float output) {
	SmartDashboard::PutNumber("* Drive PID Write", output);
	m_drivetrain->setSpeed(output);
}

// AnglePIDWrapper Functions

Drivetrain::AnglePIDWrapper::AnglePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::AnglePIDWrapper::~AnglePIDWrapper() {
}

void Drivetrain::AnglePIDWrapper::PIDWrite(float output) {
	SmartDashboard::PutNumber("Turn PID Output", output);
	m_drivetrain->setTurn(output);
}

double Drivetrain::AnglePIDWrapper::PIDGet() {
	return m_drivetrain->getAngle();
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
	//m_rDriveR.Set(.1);
}

void Drivetrain::startMP() {
	m_leftMotionProfile.Enable();
	m_rightMotionProfile.Enable();
}

float Drivetrain::getYaw(){ // Get Gyro Yaw
	return m_gyro.GetYaw();
}

void Drivetrain::resetGyro() {
	m_gyro.Reset();
}

void Drivetrain::resetMP() {
	m_leftMotionProfile.Disable();
	m_rightMotionProfile.Disable();
}

void Drivetrain::controlMP() {
	m_leftMotionProfile.Control();
	m_rightMotionProfile.Control();
}
double Drivetrain::getLeftEncoder() {
	return m_lDriveF.GetPosition();
}

double Drivetrain::getRightEncoder() {
	return m_rDriveF.GetPosition();
}

void Drivetrain::setSpeed(double speed) {
	ArcadeDrive(speed, m_turn);
}

void Drivetrain::setTurn(double turn) {
	ArcadeDrive(m_speed, turn);
}

double Drivetrain::getAngle() {
	return m_gyro.GetAngle();
}

void Drivetrain::setLeftDrive(double speed) {
	m_lDriveF.Set(speed);
	m_lDriveM.Set(speed);
	m_lDriveR.Set(speed);
}

void Drivetrain::setRightDrive(double speed) {
	m_rDriveF.Set(speed);
	m_rDriveM.Set(speed);
	m_rDriveR.Set(speed);
}

double Drivetrain::getLeftDrive() {
	return m_lDriveF.Get();
}

double Drivetrain::getRightDrive() {
	return m_rDriveF.Get();
}


Drivetrain::~Drivetrain() {
}

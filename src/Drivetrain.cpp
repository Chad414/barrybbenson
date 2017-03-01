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
	m_shift(SOLENOID_SHIFT),
	m_climb(SOLENOID_CLIMBER),
	m_lEncoder(DRIVE_ENCODER_LF, DRIVE_ENCODER_LR, true),
	m_rEncoder(DRIVE_ENCODER_RF, DRIVE_ENCODER_RR, false),
	m_light(0),
	m_MotionProfile(m_rDriveR),
	m_distancePIDWrapper(this),
	m_anglePIDWrapper(this),
	m_distancePID(DISTANCE_P, DISTANCE_I, DISTANCE_D, &m_distancePIDWrapper, &m_distancePIDWrapper, 0.05),
	m_anglePID(ANGLE_P, ANGLE_I, ANGLE_D, &m_anglePIDWrapper, &m_anglePIDWrapper, 0.05)
{

	m_turn = 0;
	m_speed = 0;

	m_lDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_lDriveF.SetSensorDirection(true);
	m_rDriveF.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rDriveF.SetSensorDirection(false);


	m_rDriveF.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);
	m_lDriveF.ConfigEncoderCodesPerRev(ENCODER_CODES_PER_REVOLUTION);

	m_drive.SetSafetyEnabled(false);

	m_light.Set(Relay::kForward);
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

// DistancePIDWrapper Functions

Drivetrain::DistancePIDWrapper::DistancePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::DistancePIDWrapper::~DistancePIDWrapper() {
}

double Drivetrain::DistancePIDWrapper::PIDGet () {
	return(m_drivetrain->GetAverageDistance() / DRIVE_ENCODER_CONVERSION);
}

void Drivetrain::DistancePIDWrapper::PIDWrite(double output) {
	SmartDashboard::PutNumber("* Drive PID Write", output);
	m_drivetrain->setSpeed(output*0.7);
}

// AnglePIDWrapper Functions

Drivetrain::AnglePIDWrapper::AnglePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::AnglePIDWrapper::~AnglePIDWrapper() {
}

double Drivetrain::AnglePIDWrapper::PIDGet() {
	return m_drivetrain->getYaw();
}

void Drivetrain::AnglePIDWrapper::PIDWrite(double output) {
	SmartDashboard::PutNumber("Turn PID Output", output);
	m_drivetrain->setTurn(-output);
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

double Drivetrain::getDriveTalonL() {
	return m_lDriveF.Get();
}

double Drivetrain::getDriveTalonR() {
	return m_rDriveF.Get();
}

void Drivetrain::setClimbShift(bool on) {
	m_climb.Set(on);
}

double Drivetrain::getSpeed() {
	return m_speed;
}

double Drivetrain::getAngle() {
	return m_turn;
}

float Drivetrain::getYaw(){ // Get Gyro Yaw
	return m_gyro.GetYaw();
}

void Drivetrain::resetGyro() {
	m_gyro.Reset();
}

double Drivetrain::getLeftEncoder() {
	return m_lDriveF.GetPosition() * DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::getRightEncoder() {
	return m_rDriveF.GetPosition() * DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::getLeftEncoderRaw() {
	return m_lDriveF.GetPosition();
}
double Drivetrain::getRightEncoderRaw() {
	return m_rDriveF.GetPosition();
}

void Drivetrain::zeroDriveEncoders() {
	m_rDriveF.SetPosition(0.0);
	m_lDriveF.SetPosition(0.0);
}

void Drivetrain::setShift(bool on) {
	m_shift.Set(on);
	m_shiftValue = on;
}

bool Drivetrain::getShift() {
	return m_shiftValue;
}

void Drivetrain::setTurn(double turn) {
	ArcadeDrive(m_speed, turn);
}

void Drivetrain::setSpeed(double speed) {
	ArcadeDrive(speed, m_turn);
}

double Drivetrain::getTotalDriveCurrent() {
	return m_lDriveF.GetOutputCurrent()
			+ m_lDriveM.GetOutputCurrent()
			+ m_lDriveR.GetOutputCurrent()
			+ m_rDriveF.GetOutputCurrent()
			+ m_rDriveM.GetOutputCurrent()
			+ m_rDriveR.GetOutputCurrent();
}

double Drivetrain::GetAverageDistance(){
	return ((getLeftEncoder() + getRightEncoder()) /2);
}

double Drivetrain::GetLSpeed() {
	return m_lDriveF.GetSpeed() * DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::GetRSpeed() {
	return m_rDriveF.GetSpeed() * DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::GetAverageSpeed(){
	return((GetLSpeed() + GetRSpeed()) / 2);
}

float Drivetrain::GetSpeed(){
	return(m_speed);
}

float Drivetrain::GetTurn(){
	return(m_turn);
}

void Drivetrain::EnablePID() {
	if (!m_distancePID.IsEnabled()) {
		m_distancePID.Enable();
	}
	if (!m_anglePID.IsEnabled()) {
		m_anglePID.Enable();
	}
}

void Drivetrain::DisablePID() {
	if (m_distancePID.IsEnabled()) {
		m_distancePID.Disable();
	}

	if (m_anglePID.IsEnabled()) {
		m_anglePID.Disable();
	}
}

bool Drivetrain::IsPIDEnabled() {
	if (m_distancePID.IsEnabled() || m_anglePID.IsEnabled()) {
		return true;
	}
	else {
		return false;
	}
}

void Drivetrain::SetPIDSetpoint(double distance, double angle) {
	m_distancePID.SetSetpoint(distance / DRIVE_ENCODER_CONVERSION);
	m_anglePID.SetSetpoint(angle);
}

double Drivetrain::GetDistancePIDError() {
	return m_distancePID.GetError()* DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::GetRotationPIDError() {
	return m_distancePID.GetError();
}

double Drivetrain::GetDistanceToSetpoint() {
	return (GetDistancePIDSetpoint() - GetAverageDistance());
}

double Drivetrain::GetDistancePIDSetpoint() {
	return (m_distancePID.GetSetpoint()* DRIVE_ENCODER_CONVERSION);
}

double Drivetrain::GetAnglePIDSetpoint() {
	return m_anglePID.GetSetpoint();
}

double Drivetrain::GetAnglePIDError() {
	return m_anglePID.GetError();
}

void Drivetrain::resetAnglePID() {
	m_anglePID.Reset();
}

void Drivetrain::resetDistancePID() {
	m_distancePID.Reset();
}

bool Drivetrain::AnglePIDIsEnabled() {
	return m_anglePID.IsEnabled();
}

void Drivetrain::SetAnglePID(float p, float i, float d) {
	m_anglePID.SetPID(p, i, d);
}

void Drivetrain::SetDistancePIDMax(float maximum) {
	m_distancePID.SetOutputRange(-maximum, maximum);
}

double Drivetrain::GetAngleP() {
	return m_anglePID.GetP();
}

double Drivetrain::GetAngleI() {
	return m_anglePID.GetI();
}

double Drivetrain::GetAngleD() {
	return m_anglePID.GetD();
}

bool Drivetrain::DistanceAtSetpoint() {
	if (fabs(GetDistancePIDSetpoint() - GetAverageDistance()) < 4) {
		return true;
	} else {
		return false;
	}
}

bool Drivetrain::AngleAtSetpoint() {
	if (fabs(GetAnglePIDSetpoint() - getYaw()) < 2.5) {
		return true;
	}
	else {
		return false;
	}
}

Drivetrain::~Drivetrain() {
}

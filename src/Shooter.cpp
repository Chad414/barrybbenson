/*
 * Shooter.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: HOT Team
 */

#include "Shooter.h"

Shooter::Shooter()
	: m_shooterL(SHOOTER_LEFT_TALON),
	  m_shooterR(SHOOTER_RIGHT_TALON),
	  m_paddle(SHOOTER_PADDLE_TALON)
{
	// TODO Auto-generated constructor stub

	m_shooterL.SetPID(SHOOTER_P,SHOOTER_I, SHOOTER_D);
	m_shooterR.SetPID(SHOOTER_P,SHOOTER_I, SHOOTER_D);
	m_shooterL.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooterR.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);

	m_shooterL.SetSensorDirection(false);
	m_shooterR.SetSensorDirection(true);
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

void Shooter::RunShoot(double shoot_speed) {
	if (GetShootMode() == true) {
		m_shooterL.Set(SHOOTER_RIGHT_TALON);
		m_shooterL.SetClosedLoopOutputDirection(true);
		m_shooterR.Set(+shoot_speed);
	}
	else {

		m_shooterL.Set(-shoot_speed);
		m_shooterR.Set(+shoot_speed);
	}

	shooterSpeed = shoot_speed;

	if ((GetShootMode() == true) && (fabs(GetShootError()) < 200) && (shooterSpeed != 0.0) ) {
		RunPaddle(-1.0);
	}
	else {
		//RunPaddle(0.0);
	}
}

void Shooter::ZeroShootEncoder() {
	m_shooterL.SetPosition(0.0);
	m_shooterR.SetPosition(0.0);
}

double Shooter::GetShoot() {
	return shooterSpeed;
}

double Shooter::GetLRawShooter() {
	return m_shooterL.Get();
}

double Shooter::GetRRawShooter() {
	return m_shooterR.Get();
}

double Shooter::GetLShootSpeed() {
	return m_shooterL.GetSpeed();
}

double Shooter::GetRShootSpeed() {
	return m_shooterR.GetSpeed();
}

double Shooter::GetAverageShootSpeed(){
	return ((GetLShootSpeed()+ GetRShootSpeed()) / 2 );
}

double Shooter::GetShootError() {
	return (GetAverageShootSpeed() - shooterSpeed);
}

void Shooter::SetShootMode(bool mode) {
	if (mode) {
		m_shooterL.SetControlMode(CANTalon::kFollower);
		m_shooterR.SetControlMode(CANTalon::kSpeed);
	}
	else if (!mode) {
		m_shooterL.SetControlMode(CANTalon::kPercentVbus);
		m_shooterR.SetControlMode(CANTalon::kPercentVbus);
	}
	shooterMode = mode;
}

bool Shooter::GetShootMode() {
	return shooterMode;
}

void Shooter::RunPaddle(double paddle_speed) { //negative is correct
	m_paddle.Set(paddle_speed);

	paddleSpeed = paddle_speed;
}

double Shooter::GetPaddle() {
	return paddleSpeed;
}

double Shooter::getLeftShoot() {
	return m_shooterL.GetPosition();
}

double Shooter::getRightShoot() {
	return m_shooterR.GetPosition();
}

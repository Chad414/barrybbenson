/*
 * Shooter.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: HOT Team
 */

#include "Shooter.h"

namespace Shooter {

Shooter::Shooter()
	: m_shooterL(SHOOTER_LEFT_TALON),
	  m_shooterR(SHOOTER_RIGHT_TALON),
	  m_feeder(FEEDER_TALON),
	  m_paddle(SHOOTER_PADDLE_TALON)
{
	// TODO Auto-generated constructor stub
	m_shooterL.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooterR.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

void Shooter::RunShoot(double shoot_speed) {
	m_shooterL.Set(-shoot_speed);
	m_shooterR.Set(shoot_speed);

	shooterSpeed = shoot_speed;
}

double Shooter::GetShoot() {
	return shooterSpeed;
}

void Shooter::RunPaddle(double paddle_speed) {
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

void Shooter::runFeeder() {
	m_feeder.Set(-1.0);
}

void Shooter::stopFeeder() {
	m_feeder.Set(0);
}

double Shooter::getFeeder() {
	return m_feeder.Get();
}

} /* namespace Shooter */

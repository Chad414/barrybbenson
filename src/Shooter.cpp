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
	  m_paddle(SHOOTER_PADDLE_TALON)
{
	// TODO Auto-generated constructor stub
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

void Shooter::RunShoot(double shoot_speed) {
	m_shooterL.Set(shoot_speed);
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

} /* namespace Shooter */

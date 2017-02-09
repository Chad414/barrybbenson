/*
 * Shooter.h
 *
 *  Created on: Feb 2, 2017
 *      Author: HOT Team
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include "WPILib.h"
#include "CANTalon.h"

#define SHOOTER_LEFT_TALON 11
#define SHOOTER_RIGHT_TALON 10

#define FEEDER_TALON 5

#define SHOOTER_PADDLE_TALON 5

namespace Shooter {

class Shooter {
private:
	CANTalon m_shooterL;
	CANTalon m_shooterR;

	CANTalon m_feeder;

	CANTalon m_paddle;

	double shooterSpeed;
	double paddleSpeed;
public:
	Shooter();
	virtual ~Shooter();

	void RunShoot(double shoot_speed);
	double GetShoot();

	void RunPaddle(double paddle_speed);
	double GetPaddle();

	double getLeftShoot();
	double getRightShoot();

	void runFeeder();
	void stopFeeder();
	double getFeeder();

};

} /* namespace Shooter */

#endif /* SRC_SHOOTER_H_ */

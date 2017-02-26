/*
 * Shooter.h
 *
 *  Created on: Feb 2, 2017
 *      Author: HOT Team
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

//2320 rpm

#include "WPILib.h"
#include "CANTalon.h"

#define SHOOTER_LEFT_TALON 11
#define SHOOTER_RIGHT_TALON 10

#define SHOOTER_PADDLE_TALON 9

#define SHOOTER_P 0.09
#define SHOOTER_I 0.0
#define SHOOTER_D 0.0
#define SHOOTER_F 0.03765
class Shooter {
private:
	CANTalon m_shooterL;
	CANTalon m_shooterR;

	CANTalon m_paddle;

	double shooterSpeed;
	double paddleSpeed;
	bool shooterMode;
public:
	Shooter();
	virtual ~Shooter();

	void RunShoot(double shoot_speed);
	double GetShoot();

	void ZeroShootEncoder();

	double GetLRawShooter();
	double GetRRawShooter();

	double GetLShootSpeed();
	double GetRShootSpeed();
	double GetAverageShootSpeed();

	double GetShootError();

	void SetShootMode(bool mode); //true is pid, false is vbus
	bool GetShootMode();

	void RunPaddle(double paddle_speed);
	double GetPaddle();

	double getLeftShoot();
	double getRightShoot();


};

#endif /* SRC_SHOOTER_H_ */

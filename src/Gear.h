/*
 * Gear.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Marlina
 */

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

#include "RobotUtils/RobotUtils.h"
#include "WPILib.h"
#include "CANTalon.h"

#define TALON_GEAR_ARM 8
#define TALON_GEAR_ROLL 12



class Gear {
private:
	CANTalon m_gearArm;
	CANTalon m_gearRoll;

public:
	Gear();

	double GetGearArmPosition();
	void ZeroGearArmPosition();
	void SetGearArmPosition(double speed);

	virtual ~Gear();
};

#endif /* SRC_GEAR_H_ */

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

#define TALON_GEAR_ARM 0
#define TALON_GEAR_WRIST 1
#define TALON_GEAR_ROLL 2

#define GEAR_ARM_ENCODER_R 1
#define GEAR_ARM_ENCODER_L 0

#define GEAR_WRIST_ENCODER_R 1
#define GEAR_WRIST_ENCODER_L 0

class Gear {
private:
	CANTalon m_gearArm;
	CANTalon m_gearWrist;
	CANTalon m_gearRoll;

	Encoder m_gearArmEncoder;
	Encoder m_gearWristEncoder;

public:
	Gear();

	double GetGearArmPosition();
	double GetGearWristPosition();

	virtual ~Gear();
};

#endif /* SRC_GEAR_H_ */

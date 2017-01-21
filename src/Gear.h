/*
 * Gear.h
 *
 *  Created on: Jan 21, 2017
 *      Author: HOT Team
 */

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

#include "RobotUtils/RobotUtils.h"
#include "WPILib.h"
#include "CANTalon.h"

#define TALON_LEFT_GEAR_ARM 0
#define TALON_RIGHT_GEAR_ARM 1
#define TALON_ADJUST_GEAR 2

#define GEAR_L_ENCODER_LEFT 1
#define GEAR_L_ENCODER_RIGHT 0

#define GEAR_R_ENCODER_LEFT 1
#define GEAR_R_ENCODER_RIGHT 0


class Gear {
private:
	CANTalon m_lGearArm;
	CANTalon m_rGearArm;
	CANTalon m_adjustArm;

	Encoder m_lGearEncoder;
	Encoder m_rGearEncoder;

public:
	Gear();

	double GetLGearPosition();
	double GetRGearPosition();

	double GetGearPosition();
	virtual ~Gear();
};

#endif /* SRC_GEAR_H_ */

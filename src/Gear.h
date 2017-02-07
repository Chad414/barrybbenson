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

#define TALON_GEAR_ARM 1 //8
#define TALON_GEAR_ROLL 12

#define TALON_GEAR_P 0.3
#define TALON_GEAR_I 0.0
#define TALON_GEAR_D 0.0
#define TALON_GEAR_F 0.0

class Gear {
private:
	CANTalon m_gearArm;
	CANTalon m_gearRoll;

	double gearCommandedSpeed;
	double gearRollerCommandedSpeed;

	bool gearMode;
public:
	Gear();

	double GetGearArmPosition();
	void ZeroGearArmPosition();

	bool SetGearMode(bool position); //true is pid mode; false is joystick control
	bool GetGearMode();

	void SetGearArmPosition(double gear_speed); //pid mode, accepts desired position; joystick mode, is % to talon
	double GetGearCommandedSpeed(); //pid mode, returns desired position; joystick mode, returns percent value

	double GetGearSetpoint();
	void SetGearRollerSpeed(double roller_speed);
	double GetGearRollerCommandedSpeed();

	virtual ~Gear();
};

#endif /* SRC_GEAR_H_ */

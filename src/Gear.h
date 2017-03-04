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

//talon definition
#define TALON_GEAR_ARM 8
#define TALON_GEAR_ROLL 12

//gear arm pid values
#define TALON_UP_GEAR_P 2.7
#define TALON_UP_GEAR_I 0.0
#define TALON_UP_GEAR_D 0.0
#define TALON_UP_GEAR_F 0.0

#define TALON_DOWN_GEAR_P 1.3
#define TALON_DOWN_GEAR_I 0.0
#define TALON_DOWN_GEAR_D 0.0
#define TALON_DOWN_GEAR_F 0.0

//gear arm constant to make degree
#define GEAR_DEGREE_CONST 165.75

#define GEAR_GROUND 0.0
#define GEAR_PACKAGE 86.0
#define GEAR_PLACE_FIRST 62.0 //70.0
#define GEAR_PLACE_SECOND 28.0
#define GEAR_HUMAN_LOAD 80.0

class Gear {
private:
	CANTalon m_gearArm;
	CANTalon m_gearRoll;
	Timer *m_rollTime;

	double gearCommandedSpeed;
	double gearRollerCommandedSpeed;
	double gearSetpoint = 0;
	bool gearMode;
public:
	Gear();
//gear arm
	double GetGearArmPosition();
		//return encoder position

	double GetRawGearArmPosition();
	void ZeroGearArmPosition();
		//sets encoder position to 0.0
	void GameStartGearArmPosition();

	void SetGearMode(bool position);
		//true is pid mode; false is joystick control
	bool GetGearMode();
		//true is pid mode; false is joystick control

	double GetGearTalonCurrent();

	double GetGearError();

	void SetGearArmPosition(double gear_speed);
		//pid mode, accepts desired position; joystick mode, is % to talon

	double GetGearCommandedSpeed();
		//pid mode, returns desired position; joystick mode, returns percent value
	double GearGet();
		//percentage sent to talon
	double GetGearSetpoint();
		//return pid setpoint

	void resetRoller();

//roller
	void SetGearRollerSpeed(double roller_speed);
	double GetGearRollerCommandedSpeed();

	virtual ~Gear();
};

#endif /* SRC_GEAR_H_ */

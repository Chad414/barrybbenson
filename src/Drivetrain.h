/*
 * Drivetrain.h
 *
 *  Created on: Jan 11, 2017
 *      Author: Chad
 */

#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

#include "WPILib.h"
#include <cmath>
#include "CANTalon.h"
#include "MotionProfile.h"
#include "AHRS.h"

#define USE_TEST_BENCH

#define TALON_DRIVE_LF 11
#define TALON_DRIVE_LR 12
#define TALON_DRIVE_RF 21
//#define TALON_DRIVE_RR 13
#define TALON_DRIVE_LM 14
#define TALON_DRIVE_RM 41

#ifndef USE_TEST_BENCH
#define TALON_DRIVE_RR 20
#else
#define TALON_DRIVE_RR 1
#endif

#define HOT_BENCH_VICTOR 0

#define DRIVE_ENCODER_LF 4
#define DRIVE_ENCODER_LR 3
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 1

#define ENCODER_CODES_PER_REVOLUTION 256

class Drivetrain {
public:
	Drivetrain();
	void InitTeleop();
	void ArcadeDrive(double speed, double angle);
	void startMP();
	void resetMP();
	void controlMP();
	float getYaw();
	virtual ~Drivetrain();

private:
	class DriveWrapper : public SpeedController {
	   public:
		DriveWrapper(SpeedController* talon1, SpeedController* talon2);
		virtual void Set(double speed);
		virtual double Get() const;
		virtual void PIDWrite (double output);
		virtual void SetInverted (bool isInverted);
		virtual bool GetInverted() const;
		virtual void Disable();
		virtual void StopMotor();
	   private:
		SpeedController* m_drive1;
		SpeedController* m_drive2;
	};

	CANTalon m_lDriveF;
	CANTalon m_lDriveM;
	CANTalon m_lDriveR;
	CANTalon m_rDriveF;
	CANTalon m_rDriveM;
	CANTalon m_rDriveR;


	DriveWrapper m_driveWrapperL;
	DriveWrapper m_driveWrapperR;

	RobotDrive m_drive;

	AHRS m_gyro;

	Encoder m_lEncoder;
	Encoder m_rEncoder;



	MotionProfile m_MotionProfile;

	Timer m_timer;

	double m_turn, m_speed;
};

#endif /* SRC_DRIVETRAIN_H_ */

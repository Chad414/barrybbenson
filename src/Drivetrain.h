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
#include "MPController.h"
#include "MP.h"
#include "AHRS.h"

//#define USE_TEST_BENCH

#define TALON_DRIVE_LF 6
#define TALON_DRIVE_LR 5
#define TALON_DRIVE_RF 1
#define TALON_DRIVE_RR 2
#define TALON_DRIVE_LM 4
#define TALON_DRIVE_RM 3


#define DRIVE_P_R 0.00005
#define DRIVE_I_R 0.001
#define DRIVE_D_R 0.0
#define DRIVE_F_R 0.0

#define DRIVE_P_L 0.00005
#define DRIVE_I_L 0.001
#define DRIVE_D_L 0.0
#define DRIVE_F_L 0.0

#ifdef USE_TEST_BENCH
#define TALON_DRIVE_RR 1
#endif

const PIDF PIDF_LEFT = {
		DRIVE_P_L,
		DRIVE_I_L,
		DRIVE_D_L,
		DRIVE_F_L};

const PIDF PIDF_RIGHT = {
		DRIVE_P_R,
		DRIVE_I_R,
		DRIVE_D_R,
		DRIVE_F_R};


#define HOT_BENCH_VICTOR 0



#define DRIVE_ENCODER_LF 4
#define DRIVE_ENCODER_LR 3
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 1

#define DISTANCE_SHIFTL_P 0
#define DISTANCE_SHIFTL_I 0
#define DISTANCE_SHIFTL_D 0

#define DISTANCE_SHIFTH_P 0
#define DISTANCE_SHIFTH_I 0
#define DISTANCE_SHIFTH_D 0

#define ANGLE_P 0
#define ANGLE_I 0
#define ANGLE_D 0

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
	void resetGyro();
	double getLeftEncoder();
	double getRightEncoder();
	void setSpeed(double speed);
	void setTurn(double angle);
	double getAngle();

	void setLeftDrive(double speed);
	void setRightDrive(double speed);
	double getLeftDrive();
	double getRightDrive();

	virtual ~Drivetrain();

	void LogValues();

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

	class DistancePIDWrapper : public PIDSource, public PIDOutput {
	public:
		DistancePIDWrapper(Drivetrain* drivetrain);
		virtual ~DistancePIDWrapper();
		double PIDGet();
		void PIDWrite(float output);
	private:
		Drivetrain* m_drivetrain;
	};

	class AnglePIDWrapper : public PIDOutput, public PIDSource {
	public:
		AnglePIDWrapper(Drivetrain *drivetrain);
		virtual ~AnglePIDWrapper();
		void PIDWrite(float output);
		double PIDGet();
	private:
	private:
		Drivetrain* m_drivetrain;
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

	Timer m_timer;

	MPController m_leftMotionProfile;
	MPController m_rightMotionProfile;

	DistancePIDWrapper m_distancePIDWrapper;
	AnglePIDWrapper m_anglePIDWrapper;

	PIDController m_distancePID;
	PIDController m_anglePID;

	double m_turn, m_speed;
};

#endif /* SRC_DRIVETRAIN_H_ */

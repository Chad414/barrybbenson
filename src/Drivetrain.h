
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

#define TALON_DRIVE_LF 7
#define TALON_DRIVE_LM 5
#define TALON_DRIVE_LR 6
#define TALON_DRIVE_RF 2
#define TALON_DRIVE_RM 4
#define TALON_DRIVE_RR 3

#define SOLENOID_SHIFT 1 //0 on practice
#define SOLENOID_CLIMBER 0 //1 on practice

/*
#ifndef USE_TEST_BENCH
#define TALON_DRIVE_RR 20
#else
#define TALON_DRIVE_RR 1
#endif

#define HOT_BENCH_VICTOR 0
*/

#define DRIVE_ENCODER_LF 4
#define DRIVE_ENCODER_LR 3
#define DRIVE_ENCODER_RF 2
#define DRIVE_ENCODER_RR 1

#define ENCODER_CODES_PER_REVOLUTION 256

#define DRIVE_ENCODER_CONVERSION 2.63

#define DISTANCE_P 0.44
#define DISTANCE_I 0
#define DISTANCE_D 0

#define ANGLE_P 1.2
#define ANGLE_I 0
#define ANGLE_D 0

#define SHIFT_THRESH 0.0

class Drivetrain {
public:
	Drivetrain();
	void InitTeleop();
	void ArcadeDrive(double speed, double angle);
	double getSpeed();
	double getAngle();
	void startMP();
	void resetMP();
	void controlMP();

	double getFrontLeftTalon();
	double getMiniLeftTalon();
	double getBackLeftTalon();
	double getFrontRightTalon();
	double getMiniRightTalon();
	double getBackRightTalon();

	void setClimbShift(bool on);
	float getYaw();
	void resetGyro();
	double getLeftEncoder();
	double getRightEncoder();

	double getLeftEncoderRaw();
	double getRightEncoderRaw();

	void zeroDriveEncoders();
	void setShift(bool on);
	bool getShift();
	void setTurn(double turn);
	void setSpeed(double speed);
	double getTotalDriveCurrent();

	double turnPIDSpeed = 0.55;
	double distancePIDSpeed = 0.8;
	double distancePIDOutput = 0;
	double anglePIDOutput = 0;

	//--------------------------------------------------------------------------------

	double GetAverageDistance();
	/*
	 * Gets left encoder speed
	 */
	double GetLSpeed();

	/*
	 * Gets right encoder speed
	 */
	double GetRSpeed();

	/*
	 * Gets average encoder speed
	 */
	double GetAverageSpeed();
	/******************************
	 * Motor Control
	 ******************************/
	float GetSpeed();
	float GetTurn();

	/*****************************
	 * 	PID
	 *****************************/
	void EnablePID();
	void DisablePID();

	bool IsPIDEnabled();

	void SetPIDSetpoint(double distance, double angle);

	double GetRotationPIDError();
	double GetDistancePIDError();
	double GetDistanceToSetpoint();
	double GetDistancePIDSetpoint();
	double GetAnglePIDSetpoint();
	bool AnglePIDIsEnabled();
	double GetAnglePIDError();
	void resetAnglePID();
	void resetDistancePID();

	void SetAnglePID(float p, float i, float d);

	void SetDistancePIDMax(float maximum);

	double GetAngleP();
	double GetAngleI();
	double GetAngleD();

	//--------------------------------------------------------------------------------
	double GetGyroAngle();


	bool DistanceAtSetpoint();
	bool AngleAtSetpoint();
	//--------------------------------------------------------------------------------

	double getDistanceSetPoint();
	void setTurnPIDSpeed(double speed);
	void setDistancePIDSpeed(double speed);

	void setDriveToBrakeMode();
	void setDriveToCoastMode();

	void setAngleP(double p);

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

	class DistancePIDWrapper : public PIDSource, public PIDOutput {
	public:
		DistancePIDWrapper(Drivetrain* drivetrain);
		virtual ~DistancePIDWrapper();
		double PIDGet() override;
		void PIDWrite(double output) override;
	private:
		Drivetrain* m_drivetrain;
	};

	class AnglePIDWrapper : public PIDSource, public PIDOutput {
	public:
		AnglePIDWrapper(Drivetrain* drivetrain);
		virtual ~AnglePIDWrapper();
		double PIDGet() override;
		void PIDWrite(double output) override;
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

	//AHRS m_gyro;

	Solenoid m_shift;
	Solenoid m_climb;

	Encoder m_lEncoder;
	Encoder m_rEncoder;

	Relay m_light;

	//MotionProfile m_MotionProfile;

	AnalogGyro m_newGyro;

	DistancePIDWrapper m_distancePIDWrapper;
	AnglePIDWrapper m_anglePIDWrapper;

	PIDController m_distancePID;
	PIDController m_anglePID;

	double m_turn, m_speed;

};

#endif /* SRC_DRIVETRAIN_H_ */

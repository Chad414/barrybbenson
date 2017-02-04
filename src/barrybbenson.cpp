#include "WPILib.h"
#include "CANTalon.h"
#include "RobotUtils/RobotUtils.h"

#include "Drivetrain.h"
#include "Shooter.h"

/*
	 ***** Driver Joystick Mapping
	 *
	 * BUTTONS
	 * 		A -
	 * 		B -
	 * 		X -
	 * 		Y -
	 *
	 * DPAD
	 * 		UP -
	 * 		DOWN -
	 * 		LEFT -
	 * 		RIGHT -
	 *
	 * JOYSTICK
	 * 		LEFT - up/down drive
	 * 		RIGHT - left/right drive
	 *
	 * BUMPERS
	 * 		LEFT - gear shifter (hold)
	 * 		RIGHT -
	 *
	 * TRIGGERS
	 * 		LEFT - paddle out
	 * 		RIGHT - paddle in
	 *
	 * OTHER
	 * 		START -
	 * 		BACK -
	 *
	 */

/*
	 ***** Operator Joystick Mapping
	 *
	 * BUTTONS
	 * 		A - gear to ground
	 * 		B - gear to place, wrist out
	 * 		X - gear to angle off gear
	 * 		Y - gear to package
	 *
	 * DPAD
	 * 		UP - pickup out, hopper out
	 * 		DOWN - pickup in, hopper in
	 * 		LEFT -
	 * 		RIGHT - hopper in
	 *
	 * JOYSTICK
	 * 		LEFT - manual gear arm movement
	 * 		RIGHT -
	 *
	 * BUMPERS
	 * 		LEFT - gear out roller
	 * 		RIGHT - gear in roller
	 *
	 * TRIGGERS
	 * 		LEFT - fuel out roller
	 * 		RIGHT - fuel in roller
	 *
	 * OTHER
	 * 		START - shooter up
	 * 		BACK -
	 *
	 */

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Shooter::Shooter m_shoot;
	Drivetrain m_drivetrain;

public:

	double shooterSpeed = 0.4;

	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);
	}

	void RobotInit() {
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
		TeleopDrive();
		TeleopShoot();
	}

	void TeleopShoot() {
		if (m_driver->ButtonRT()) {
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_driver->ButtonPressedY()) {
			shooterSpeed += 0.025;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_driver->ButtonPressedB()) {
			shooterSpeed -= 0.025;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_driver->ButtonPressedX()) {
			shooterSpeed = 0;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.Shooter::getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.Shooter::getRightShoot());
		SmartDashboard::PutNumber("Shooter Power", shooterSpeed);
	}

	void TeleopDrive() {
		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain.ArcadeDrive(-m_driver->AxisLY(), -m_driver->AxisRX());
		}

		SmartDashboard::PutNumber("Forward and Backward", m_drivetrain.getSpeed());
		SmartDashboard::PutNumber("Turning", m_drivetrain.getAngle());
		SmartDashboard::PutNumber("Left Drive Encoder", m_drivetrain.getLeftEncoder());
		SmartDashboard::PutNumber("Right Drive Encoder", m_drivetrain.getRightEncoder());

	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

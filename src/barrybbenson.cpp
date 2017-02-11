#include "WPILib.h"
#include "CANTalon.h"
#include <iostream>
#include "RobotUtils/RobotUtils.h"
#include "CameraServer.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

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
	bool isFeederOn = false;

	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);
	}

    static void VisionThread() {
        cs::UsbCamera m_camera = CameraServer::GetInstance()->StartAutomaticCapture();
        std::cout << "Camera Capture Started" << std::endl;
        m_camera.SetResolution(640, 480);
        m_camera.SetExposureManual(50);
        m_camera.SetExposureHoldCurrent();
        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
        cv::Mat source;
        cv::Mat output;
        while(true) {
            cvSink.GrabFrame(source);
            cvtColor(source, output, cv::COLOR_BGR2GRAY);
            outputStreamStd.PutFrame(output);
        }
    }

	void RobotInit() {
        std::thread visionThread(VisionThread);
        visionThread.detach();
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
		if (m_operator->ButtonRT()) {
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_operator->ButtonPressedY()) {
			shooterSpeed += 0.025;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_operator->ButtonPressedB()) {
			shooterSpeed -= 0.025;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}
		if (m_operator->ButtonPressedX()) {
			shooterSpeed = 0;
			m_shoot.Shooter::RunShoot(shooterSpeed);
		}

		if (m_operator->ButtonPressedA()) {
			if (isFeederOn) {
				m_shoot.stopFeeder();
				isFeederOn = false;
			} else {
				m_shoot.runFeeder();
				isFeederOn = true;
			}
		}

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.Shooter::getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.Shooter::getRightShoot());
		SmartDashboard::PutNumber("Shooter Power", shooterSpeed);
	}

	void TeleopDrive() {
		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain.ArcadeDrive(-m_driver->AxisLY(), -m_driver->AxisRX());
		}

		if (m_driver->ButtonLB()) {
			m_drivetrain.setShift(true);
		} else {
			m_drivetrain.setShift(false);
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

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

	PowerDistributionPanel m_pdp;

	Timer m_timer;

	Shooter::Shooter m_shoot;
	Drivetrain m_drivetrain;

	double totalDriveCurrent;

public:

	double shooterSpeed;
	bool isFeederOn = false;

	barrybbenson() : m_pdp(0) {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		totalDriveCurrent = m_pdp.GetCurrent(7)
				+ m_pdp.GetCurrent(5)
				+ m_pdp.GetCurrent(6)
				+ m_pdp.GetCurrent(2)
				+ m_pdp.GetCurrent(4)
				+ m_pdp.GetCurrent(3);
	}

    static void VisionThread() {
        cs::UsbCamera m_camera = CameraServer::GetInstance()->StartAutomaticCapture();
        cs::UsbCamera m_camera2 = CameraServer::GetInstance()->StartAutomaticCapture();
        std::cout << "Camera Capture Started" << std::endl;
        m_camera.SetResolution(320, 240);
        m_camera.SetExposureManual(10);
        m_camera.SetExposureHoldCurrent();
        m_camera.SetBrightness(2);
        m_camera2.SetResolution(320, 240);
        m_camera2.SetExposureManual(10);
        m_camera2.SetExposureHoldCurrent();
        m_camera2.SetBrightness(2);
        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("USBCamera", 320, 240);
        cv::Mat source;
        cv::Mat output;
        while(true) {
            cvSink.GrabFrame(source);
            cvtColor(source, output, cv::COLOR_BGR2BGR565);
            outputStreamStd.PutFrame(output);
        }
    }

	void RobotInit() {
        std::thread visionThread(VisionThread);
        visionThread.detach();
	}

	void DisabledPeriodic() {
		SmartDashboard::PutNumber("Right Shooter Raw", m_shoot.Shooter::GetRRawShooter());
		SmartDashboard::PutNumber("Left Shooter Raw", m_shoot.Shooter::GetLRawShooter());

		SmartDashboard::PutBoolean("Shooter Mode", m_shoot.Shooter::GetShootMode());
		SmartDashboard::PutNumber("Shooter Power", shooterSpeed);

		SmartDashboard::PutNumber("Left Shooter Speed", m_shoot.Shooter::GetLShootSpeed());
		SmartDashboard::PutNumber("Right Shooter Speed", m_shoot.Shooter::GetRShootSpeed());

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.Shooter::getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.Shooter::getRightShoot());
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
		if (m_driver->ButtonA()) {
			m_shoot.Shooter::SetShootMode(false);
			m_shoot.Shooter::RunShoot(1.0);
		}
		else if (m_driver->ButtonB()) {
			m_shoot.Shooter::SetShootMode(true);
			m_shoot.Shooter::RunShoot(3400);
		}
		else {
			m_shoot.Shooter::SetShootMode(false);
			m_shoot.Shooter::RunShoot(0.0);
		}


		SmartDashboard::PutNumber("Right Shooter Raw", m_shoot.Shooter::GetRRawShooter());
		SmartDashboard::PutNumber("Left Shooter Raw", m_shoot.Shooter::GetLRawShooter());

		SmartDashboard::PutBoolean("Shooter Mode", m_shoot.Shooter::GetShootMode());
		SmartDashboard::PutNumber("ShooterSpeed", shooterSpeed);
		SmartDashboard::PutNumber("Get Shoot", m_shoot.Shooter::GetShoot());

		SmartDashboard::PutNumber("Get Paddle", m_shoot.Shooter::GetPaddle());

		SmartDashboard::PutNumber("Left Shooter Speed", m_shoot.Shooter::GetLShootSpeed());
		SmartDashboard::PutNumber("Right Shooter Speed", m_shoot.Shooter::GetRShootSpeed());
		SmartDashboard::PutNumber("Average Shooter Speed", m_shoot.Shooter::GetAverageShootSpeed());
		SmartDashboard::PutNumber("Shoot Error", m_shoot.Shooter::GetShootError());

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.Shooter::getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.Shooter::getRightShoot());

	}

	void TeleopDrive() {
		if (fabs(m_driver->AxisLY()) > 0.2) { // || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain.ArcadeDrive(-m_driver->AxisLY(), -m_driver->AxisRX());
				//negative is the right way for can 11
				//negative is the right way for can 10

		}

		if (m_driver->ButtonLB()) {
			if (m_timer.Get() >= 2.0) {
				m_drivetrain.setShift(false);
			} else {
				m_drivetrain.setShift(true);
			}
		} else {
			m_drivetrain.setShift(false);
		}

		//SmartDashboard::PutNumber("Forward and Backward", m_drivetrain.getSpeed());
		//SmartDashboard::PutNumber("Turning", m_drivetrain.getAngle());
		//SmartDashboard::PutNumber("Left Drive Encoder", m_drivetrain.getLeftEncoder());
		//SmartDashboard::PutNumber("Right Drive Encoder", m_drivetrain.getRightEncoder());

		if (totalDriveCurrent >= 2.5) {
			m_timer.Start();
		} else {
			m_timer.Stop();
			m_timer.Reset();
		}

		//SmartDashboard::PutNumber("Left Drive Current - Front", m_pdp.GetCurrent(7));
		//SmartDashboard::PutNumber("Left Drive Current - Mini", m_pdp.GetCurrent(5));
		//SmartDashboard::PutNumber("Left Drive Current - Rear", m_pdp.GetCurrent(6));
		//SmartDashboard::PutNumber("Right Drive Current - Front", m_pdp.GetCurrent(2));
		//SmartDashboard::PutNumber("Right Drive Current - Mini", m_pdp.GetCurrent(4));
		//SmartDashboard::PutNumber("Right Drive Current - Rear", m_pdp.GetCurrent(3));
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

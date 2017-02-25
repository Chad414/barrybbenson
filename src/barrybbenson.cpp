#include "WPILib.h"
#include "CANTalon.h"
#include <iostream>
#include "RobotUtils/RobotUtils.h"
#include "CameraServer.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "Drivetrain.h"
#include "Shooter.h"
#include "Gear.h"
#include "Intake.h"

/*
	 ***** Driver Joystick Mapping
	 *
	 * BUTTONS
	 * 		A - run shoot full blast
	 * 		B - run shoot 3400 rpm
	 * 		X - climb out
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
	 * 		B - gear secondary place
	 * 		X - gear initial place
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
	 * 		START - shooter up //not yet because it is currently on driver for testing until the encoder is in
	 * 		BACK -
	 *
	 */

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;
	Timer* m_timer;


	PowerDistributionPanel m_pdp;


	Shooter m_shoot;
	Drivetrain m_drivetrain;
	Gear m_gear;
	Intake m_intake;

	Timer m_currentTimer;
	Timer m_rollTimer;
	double totalDriveCurrent;
	int placeGear = 0;

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
        //std::thread visionThread(VisionThread);
        //visionThread.detach();
        m_gear.GameStartGearArmPosition();
        m_shoot.ZeroShootEncoder();
	}

	void DisabledPeriodic() {
		SmartDashboard::PutNumber("Right Shooter Raw", m_shoot.GetRRawShooter());
		SmartDashboard::PutNumber("Left Shooter Raw", m_shoot.GetLRawShooter());

		SmartDashboard::PutBoolean("Shooter Mode", m_shoot.GetShootMode());
		SmartDashboard::PutNumber("Shooter Power", shooterSpeed);

		SmartDashboard::PutNumber("Left Shooter Speed", m_shoot.GetLShootSpeed());
		SmartDashboard::PutNumber("Right Shooter Speed", m_shoot.GetRShootSpeed());

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.getRightShoot());
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
		TeleopGear();
		TeleopIntake();
	}

	void TeleopShoot() {
		if (m_driver->ButtonA()) {
			m_shoot.SetShootMode(false);
			m_shoot.RunShoot(1.0);
		}
		else if (m_driver->ButtonB()) {
			m_shoot.SetShootMode(true);
			m_shoot.RunShoot(3400);
		}
		else {
			m_shoot.SetShootMode(false);
			m_shoot.RunShoot(0.0);
		}

		if (m_driver->AxisLT() > 0.2) {
			m_shoot.RunPaddle(1.0);
		}
		else if (m_driver->AxisRT() > 0.2) {
			m_shoot.RunPaddle(-1.0);
		}
		else {
			m_shoot.RunPaddle(0.0);
		}


		SmartDashboard::PutNumber("Right Shooter Raw", m_shoot.GetRRawShooter());
		SmartDashboard::PutNumber("Left Shooter Raw", m_shoot.GetLRawShooter());

		SmartDashboard::PutBoolean("Shooter Mode", m_shoot.GetShootMode());
		SmartDashboard::PutNumber("ShooterSpeed", shooterSpeed);
		SmartDashboard::PutNumber("Get Shoot", m_shoot.GetShoot());

		SmartDashboard::PutNumber("Get Paddle", m_shoot.GetPaddle());

		SmartDashboard::PutNumber("Left Shooter Speed", m_shoot.GetLShootSpeed());
		SmartDashboard::PutNumber("Right Shooter Speed", m_shoot.GetRShootSpeed());
		SmartDashboard::PutNumber("Average Shooter Speed", m_shoot.GetAverageShootSpeed());
		SmartDashboard::PutNumber("Shoot Error", m_shoot.GetShootError());

		SmartDashboard::PutNumber("Left Shooter Encoder", m_shoot.getLeftShoot());
		SmartDashboard::PutNumber("Right Shooter Encoder", m_shoot.getRightShoot());

	}

	void TeleopDrive() {

		SmartDashboard::PutNumber("Axis RX", -m_driver->AxisRX());
		SmartDashboard::PutNumber("Angle", m_drivetrain.getAngle());

		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain.ArcadeDrive(-m_driver->AxisLY(), -m_driver->AxisRX());
				//negative is the right way for can 11
				//negative is the right way for can 10
		}

		if (m_driver->ButtonX()) {
			m_drivetrain.setClimbShift(true);
		}
		else {
			m_drivetrain.setClimbShift(false);
		}

		if (m_driver->ButtonLB()) {
			if (m_currentTimer.Get() >= 2.0) {
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
			m_currentTimer.Start();
		} else {
			m_currentTimer.Stop();
			m_currentTimer.Reset();
		}

		//SmartDashboard::PutNumber("Left Drive Current - Front", m_pdp.GetCurrent(7));
		//SmartDashboard::PutNumber("Left Drive Current - Mini", m_pdp.GetCurrent(5));
		//SmartDashboard::PutNumber("Left Drive Current - Rear", m_pdp.GetCurrent(6));
		//SmartDashboard::PutNumber("Right Drive Current - Front", m_pdp.GetCurrent(2));
		//SmartDashboard::PutNumber("Right Drive Current - Mini", m_pdp.GetCurrent(4));
		//SmartDashboard::PutNumber("Right Drive Current - Rear", m_pdp.GetCurrent(3));
	}

	//intake is ready for test
	void TeleopIntake() {
		if (m_operator->GetPOV() == 0.0) {
			if (m_gear.GetGearArmPosition() > 75) { //checks to see if gear arm is in
				m_intake.SetHopper(true);
				m_intake.SetIntakeArm(true);
			}
		}
		else if (m_operator->GetPOV() == 180.0) {
			m_intake.SetIntakeArm(false);
			m_intake.SetHopper(false);
		}
		else if (m_operator->GetPOV() == 90.0) {
			m_intake.SetHopper(false);
		}

		if (m_operator->AxisLT() > 0.2) {
			m_intake.SetIntakeRoller(1.0);
		}
		else if (m_operator->AxisRT() > 0.2) {
			m_intake.SetIntakeRoller(-1.0);
		}
		else {
			m_intake.SetIntakeRoller(0.0);
		}

		SmartDashboard::PutNumber("Intake Roller", m_intake.GetIntakeRoller());
		SmartDashboard::PutNumber("Intake POV", m_operator->GetPOV());
	}

	//gear is done !!
	void TeleopGear() {
		SmartDashboard::PutNumber("Gear Timer", m_rollTimer.Get());
		SmartDashboard::PutNumber("Gear Position", m_gear.GetGearArmPosition());
		SmartDashboard::PutBoolean("Gear Mode", m_gear.GetGearMode());
		SmartDashboard::PutNumber("Gear Raw Position", m_gear.GetRawGearArmPosition());
		SmartDashboard::PutNumber("Gear Commanded", m_gear.GetGearCommandedSpeed());
		SmartDashboard::PutNumber("Gear Error", m_gear.GetGearError());
		SmartDashboard::PutNumber("Gear Place", placeGear);
		SmartDashboard::PutNumber("Gear Roller Speed", m_gear.GetGearRollerCommandedSpeed());

		if (fabs(m_operator->AxisLY()) > 0.2) {
			m_gear.SetGearMode(false);
			m_gear.SetGearArmPosition(m_operator->AxisLY());
		}
		else if (m_operator->ButtonA()) {
			m_gear.SetGearMode(true);
			m_gear.SetGearArmPosition(GEAR_GROUND);
		}
		else if (m_operator->ButtonX()) {
			m_gear.SetGearMode(true);
			m_gear.SetGearArmPosition(GEAR_PLACE_FIRST);
		}
		else if (m_operator->ButtonB()){
			switch (placeGear){
				case 0:
					m_gear.SetGearMode(true);
					m_gear.SetGearArmPosition(GEAR_PLACE_FIRST);
					if (m_gear.GetGearError() < 5) {
						placeGear++;
						m_rollTimer.Stop();
						m_rollTimer.Reset();
						m_rollTimer.Start();
					}
					break;
				case 1:
					m_gear.SetGearRollerSpeed(-0.7);
					if (m_rollTimer.Get() > 1.0) {
						m_gear.SetGearRollerSpeed(0.0);
						placeGear++;
					}
					break;
				case 2:
					m_gear.SetGearArmPosition(GEAR_PLACE_SECOND);
					if (m_gear.GetGearError() < 5) {
						placeGear++;
					}
			}

		}
		else if (m_operator->ButtonY()) {
			m_gear.SetGearMode(true);
			m_gear.SetGearArmPosition(GEAR_PACKAGE);
		}
		else if (m_operator->ButtonRB()) {
			m_gear.SetGearRollerSpeed(1.0);
		}
		else if (m_operator->ButtonLB()) {
			m_gear.SetGearRollerSpeed(-1.0);
		}
		else {
			m_gear.SetGearMode(false);
			m_gear.SetGearArmPosition(0.0);
			m_gear.SetGearRollerSpeed(0.0);
			placeGear = 0;
		}
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

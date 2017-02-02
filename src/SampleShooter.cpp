#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TalonSRX.h>
#include <encoder.h>
#include <XboxController.h>

class Robot: public frc::IterativeRobot {
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	TalonSRX * m_talon1 = new TalonSRX( 7 );
	TalonSRX * m_talon2 = new TalonSRX( 12 );
	TalonSRX * m_talonPaddle = new TalonSRX( 5 ); // placeholder

	XboxController * m_controller = new XboxController( 0 );

	double speed;

public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);


	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {
		speed = 0;
	}

	void TeleopPeriodic() {
		if ( m_controller->GetXButton() )
		{
			speed = .5;
		}
		else if ( m_controller->GetAButton() )
		{
			speed = -.5;
		}
		else
		{
			speed = 0;
		}

		m_talon1->Set( speed );
		m_talon2->Set( speed );
		m_talonPaddle->Set( speed );

	}

	void TestPeriodic() {
		lw->Run();
	}


};


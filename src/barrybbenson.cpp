#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "Drivetrain.h"

using namespace std;

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Victor* m_shooter1;
	Victor* m_shooter2;

	PowerDistributionPanel* m_pdp;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

	Drivetrain m_drivetrain;

public:
	barrybbenson() {
		speed = 0;
		previousAButton = false;
		previousXButton = false;

		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		m_shooter1 = new Victor(0);
		m_shooter2 = new Victor(1);

		m_pdp = new PowerDistributionPanel(0);
	}
	void RobotInit() {
	}


	void AutonomousInit() {
		cout << "Autonomous Init" << endl;
		m_drivetrain.resetMP();
		m_drivetrain.startMP(); // We have to call Start before Control
	}

	void AutonomousPeriodic() {
		m_drivetrain.LogValues();
	}

	void TeleopInit() {
		speed = 0;
		previousAButton = false;
		previousXButton = false;
		m_drivetrain.resetMP();
		m_drivetrain.resetGyro();
	}

	void DisabledInit() {
		cout << "Disabled Init" << endl;
		m_drivetrain.resetMP();
	}

	void TeleopPeriodic() {
		TeleopDrive();
		//TeleopShoot();

		SmartDashboard::PutNumber("Gyro Yaw", m_drivetrain.getYaw());

		previousAButton = m_driver->ButtonA();
		previousXButton = m_driver->ButtonX();
	}

	void TeleopDrive() {
		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain.ArcadeDrive(m_driver->AxisLY(), -m_driver->AxisRX());
		}

		SmartDashboard::PutBoolean("Left Drive Encoder", m_drivetrain.getLeftEncoder());
		SmartDashboard::PutBoolean("Left Right Encoder", m_drivetrain.getRightEncoder());

		/*
		 * Go To Angle Code
		if (m_driver->ButtonY()) {
			if (m_drivetrain.getYaw() > 8) {
				m_drivetrain.ArcadeDrive(0, 0.5);
			}
			if (m_drivetrain.getYaw() < -8) {
				m_drivetrain.ArcadeDrive(0, -0.5);
			}
			if (m_driver->ButtonX()) {
				if (m_drivetrain.getYaw() < 88) {
					m_drivetrain.ArcadeDrive(0, 0.5);
				}
				if (m_drivetrain.getYaw() > 92) {
					m_drivetrain.ArcadeDrive(0, -0.5);
				}
			}
			if (m_driver->ButtonB()) {
				if (m_drivetrain.getYaw() < -88) {
					m_drivetrain.ArcadeDrive(0, 0.5);
				}
				if (m_drivetrain.getYaw() > -92) {
					m_drivetrain.ArcadeDrive(0, -0.5);
				}
			}
		}
		*/

	}

	void TeleopShoot() {

		if (m_driver->ButtonX() && (previousXButton == false) && speed > 0.0) {
			speed -= 0.05;
			}
		else if (m_driver->ButtonA() && (previousAButton == false) && speed < 1.0) {
			speed+= 0.05;
			}

		else if (m_driver->ButtonB() && speed > 0.0) {
			speed = 0.0;
		}
		else {
			m_shooter1->Set(speed);
		}



		/*
		if ((fabs(m_driver->AxisLY())) > 0.2) {
			m_shooter1->Set(m_driver->AxisLY());
		}
		else {
			m_shooter1->Set(0);
		}
		//m_shooter1->Set(0.2);
		 *
		 */
		SmartDashboard::PutNumber("speed", speed);
		SmartDashboard::PutBoolean("A Button", previousAButton);
		SmartDashboard::PutBoolean("X Button", previousXButton);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

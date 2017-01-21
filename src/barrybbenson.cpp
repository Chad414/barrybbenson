#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "Drivetrain.h"
#include "MotionProfile.h"

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

	}

	void AutonomousPeriodic() {
		m_drivetrain.startMP();
	}

	void TeleopInit() {
		speed = 0;
		previousAButton = false;
		previousXButton = false;
	}

	void TeleopPeriodic() {
		TeleopDrive();
		TeleopShoot();

		previousAButton = m_driver->ButtonA();
		previousXButton = m_driver->ButtonX();
	}

	void TeleopDrive() {
		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
					m_drivetrain.ArcadeDrive(-m_driver->AxisLY(), m_driver->AxisRX());
				}
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

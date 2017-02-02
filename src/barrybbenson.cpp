#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include <TalonSRX.h>

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	TalonSRX * m_shooter1;
	TalonSRX * m_shooter2;

	PowerDistributionPanel* m_pdp;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		m_shooter1 = new TalonSRX( 7 );
		m_shooter2 = new TalonSRX( 12 );

		m_pdp = new PowerDistributionPanel(0);
	}
	void RobotInit() {
		}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		speed = 0;
		previousAButton = false;
		previousXButton = false;
	}

	void TeleopPeriodic() {
	 TeleopShoot();

	 previousAButton= m_driver->ButtonA();
	 previousXButton= m_driver->ButtonX();
	}

	void TeleopShoot() {

		if (m_driver->ButtonX() ) {
			speed = -.5;
			}
		else if (m_driver->ButtonA() ) {
			speed = .5;
			}

		else
		{
			speed = 0.0;
		}

			m_shooter1->Set( speed );
			m_shooter2->Set( speed );
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



START_ROBOT_CLASS(barrybbenson)

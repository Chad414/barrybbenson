#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "Gear.h"

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Victor* m_shooter1;
	Victor* m_shooter2;

	PowerDistributionPanel* m_pdp;

	Gear m_gear;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

public:
	barrybbenson() {
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

	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
	}

	void TeleopShoot() {

	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

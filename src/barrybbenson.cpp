#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;
	CANTalon* m_CANTalon1;
	CANTalon* m_CANTalon2;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

public:
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

		if (m_driver->ButtonA()) {
			m_CANTalon1-> Set (.5);
			}

		else if (m_driver->ButtonX()) {
			m_CANTalon2-> Set (.25);
			}
		}



	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

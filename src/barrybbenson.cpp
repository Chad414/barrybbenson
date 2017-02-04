#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "EncoderTest.h"

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

	PowerDistributionPanel* m_pdp;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

	EncoderTest m_shooter;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

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
		m_shooter.Set(1.0);

		SmartDashboard::PutNumber("Encoder Value", m_shooter.Get());
		SmartDashboard::PutNumber("Encoder Rate", m_shooter.GetRate());
	}
};

/*	void TeleopShoot() {

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




		if ((fabs(m_driver->AxisLY())) > 0.2) {
			m_shooter1->Set(m_driver->AxisLY());
		}
		else {
			m_shooter1->Set(0);
		}
		//m_shooter1->Set(0.2);
		 *

		SmartDashboard::PutNumber("speed", speed);
		SmartDashboard::PutBoolean("A Button", previousAButton);
		SmartDashboard::PutBoolean("X Button", previousXButton);
	}

	void TestPeriodic() {
	}

};
*/
START_ROBOT_CLASS(barrybbenson)

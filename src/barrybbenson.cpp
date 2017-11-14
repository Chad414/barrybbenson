#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "ctrlib/CANTalon.h"

class benchTest: public HotBot {
private:

	HotJoystick* m_driver;

	Victor* m_PWMmotor0;
	Victor* m_PWMmotor1;
	CANTalon* m_CANmotor1;
	CANTalon* m_CANmotor2;

	bool aButton;
	bool aButtonOld = 0;

	float joystickRaw;
	float joystickMod;
	float spdCmd[4];

	int motorSelect = 0;

public:
	benchTest() {
		m_driver = new HotJoystick(0);

		m_PWMmotor0 = new Victor(0);
		m_PWMmotor1 = new Victor(1);
		m_CANmotor1 = new CANTalon(1);
		m_CANmotor2 = new CANTalon(2);


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

		 /* Read inputs from Joystick */
		 aButton= m_driver->ButtonA();
		 joystickRaw = m_driver->AxisLX();  /* Uses Left Stick, X axis */


		 /* Deadband input, determine joystickMod */
		 /* Needs to be done by students */



		 /* Process button press to determine motorSelect */
		 /* Needs to be done by students */



		 /* Use motorSelect to define speed commands to motors */
		 /* Needs to be done by students */



		 /* Command speeds to motor controllers */
		 m_CANmotor1->Set(joystickRaw);
		 m_CANmotor2->Set(0.0);
		 m_PWMmotor0->Set(0.0);
		 m_PWMmotor1->Set(0.0);

		 DashboardOutput();
	}

	void DashboardOutput() {
		/* Writes variables to Dashboard */
		SmartDashboard::PutBoolean("ButtonA", aButton);
		SmartDashboard::PutNumber("joystickRaw", joystickRaw);
		SmartDashboard::PutNumber("joystickMod", joystickMod);
		SmartDashboard::PutNumber("motorSelect", motorSelect);
		SmartDashboard::PutNumber("SpdCmd(CAN1)", spdCmd[0]);
		SmartDashboard::PutNumber("SpdCmd(CAN2)", spdCmd[1]);
		SmartDashboard::PutNumber("SpdCmd(PWM0)", spdCmd[2]);
		SmartDashboard::PutNumber("SpdCmd(PWM1)", spdCmd[3]);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(benchTest)

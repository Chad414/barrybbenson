#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "ctrlib/CANTalon.h"

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;

	Victor* m_PWMmotor0;
	Victor* m_PWMmotor1;
	CANTalon* m_CANmotor1;
	CANTalon* m_CANmotor2;

	bool aButton;
	bool bButton;
	bool xButton;
	bool yButton;
	float joystickRaw[4];
	float spdCmd[4];

public:
	barrybbenson() {
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
		 aButton= m_driver->ButtonA();
		 bButton= m_driver->ButtonB();
		 xButton= m_driver->ButtonX();
		 yButton= m_driver->ButtonY();

		 joystickRaw[0] = m_driver->AxisLX();  /* Uses Left Stick, X axis */
		 joystickRaw[1] = m_driver->AxisLY();  /* Uses Left Stick, Y axis */
		 joystickRaw[2] = m_driver->AxisRX();  /* Uses Right Stick, X axis */
		 joystickRaw[3] = m_driver->AxisRY();  /* Uses Right Stick, Y axis */

		 /* Need to deadband inputs */
		 for (int i = 0; i < 4; i++) {
			 if ((joystickRaw[i] > -0.2) && (joystickRaw[i] < 0.2)) {
				 spdCmd[i] = 0.0;
			 } else if (joystickRaw[i] < 0.0) {
				 spdCmd[i] = (joystickRaw[i] + 0.2)/0.8;

			 } else {
				 spdCmd[i] = (joystickRaw[i] - 0.2)/0.8;
			 }
		 }

		 m_CANmotor1->Set(spdCmd[0]);
		 m_CANmotor2->Set(spdCmd[1]);
		 m_PWMmotor0->Set(spdCmd[2]);
		 m_PWMmotor1->Set(spdCmd[3]);

		 DashboardOutput();
	}

	void DashboardOutput() {
		SmartDashboard::PutBoolean("ButtonA", aButton);
		SmartDashboard::PutBoolean("ButtonB", bButton);
		SmartDashboard::PutBoolean("ButtonX", xButton);
		SmartDashboard::PutBoolean("ButtonY", yButton);
		SmartDashboard::PutNumber("Joy0[LX]", joystickRaw[0]);
		SmartDashboard::PutNumber("Joy1[LY]", joystickRaw[1]);
		SmartDashboard::PutNumber("Joy2[RX]", joystickRaw[2]);
		SmartDashboard::PutNumber("Joy3[RY]", joystickRaw[3]);
		SmartDashboard::PutNumber("SpdCmd(CAN1)", spdCmd[0]);
		SmartDashboard::PutNumber("SpdCmd(CAN2)", spdCmd[1]);
		SmartDashboard::PutNumber("SpdCmd(PWM0)", spdCmd[2]);
		SmartDashboard::PutNumber("SpdCmd(PWM1)", spdCmd[3]);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

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
	bool aButtonOld = false;
	bool transitionInProcess = false;

	float joystickRaw;
	float joystickMod;
	float spdCmd;

	int motorSelect = 4;
	     /* 0: CANTalon1
		    1: CANTalon2
			2: Victor0
			3: Victor1
			4: No Motor Selected */

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

		 if(joystickRaw <= 0.2 && joystickRaw >= -0.2){
			 joystickMod = 0.0;
		 }else if(joystickRaw > 0.2){
			 joystickMod = (joystickRaw - 0.2) * 1.25;
		 }else{
			 joystickMod = (joystickRaw + 0.2) * 1.25;
		 }

		 spdCmd = joystickMod;

		 /* Process button press to determine motorSelect */
		 if ((aButton == true) && (aButtonOld == false)) {
			 transitionInProcess = true;
		 } else {
			 transitionInProcess = false;
		 }

		 /* Use motorSelect to define speed commands to motors */
		 if (transitionInProcess == true) {
			 if (motorSelect < 4) {
				 motorSelect++;
			 } else {
				 motorSelect = 0;
			 }

		 }

		 /* Command speeds to motor controllers */
		 switch (motorSelect) {
		 case 0:
			 m_CANmotor1->Set(spdCmd);
			 m_CANmotor2->Set(0.0);
			 m_PWMmotor0->Set(0.0);
			 m_PWMmotor1->Set(0.0);
			 break;
		 case 1:
			 m_CANmotor1->Set(0.0);
			 m_CANmotor2->Set(spdCmd);
			 m_PWMmotor0->Set(0.0);
			 m_PWMmotor1->Set(0.0);
			 break;
		 case 2:
			 m_CANmotor1->Set(0.0);
			 m_CANmotor2->Set(0.0);
			 m_PWMmotor0->Set(spdCmd);
			 m_PWMmotor1->Set(0.0);
			 break;
		 case 3:
			 m_CANmotor1->Set(0.0);
			 m_CANmotor2->Set(0.0);
			 m_PWMmotor0->Set(0.0);
			 m_PWMmotor1->Set(spdCmd);
			 break;
		 case 4:
			 m_CANmotor1->Set(0.0);
			 m_CANmotor2->Set(0.0);
			 m_PWMmotor0->Set(0.0);
			 m_PWMmotor1->Set(0.0);
			 break;
		 }

		 /* Preserve knowledge of previous loop button state */
		 aButtonOld = aButton;

		 DashboardOutput();
	}

	void DashboardOutput() {
		/* Writes variables to Dashboard */
		SmartDashboard::PutBoolean("ButtonA", aButton);
		SmartDashboard::PutNumber("joystickRaw", joystickRaw);
		SmartDashboard::PutNumber("joystickMod", joystickMod);
		SmartDashboard::PutNumber("motorSelect", motorSelect);
		SmartDashboard::PutNumber("SpdCmd", spdCmd);
	}


	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(benchTest)

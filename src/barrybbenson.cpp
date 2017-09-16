#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "ctrlib/CANTalon.h"

class barrybbenson: public HotBot {   
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Victor* m_PWMmotor0;
	Victor* m_PWMmotor1;
	CANTalon* m_CANmotor1;
	CANTalon* m_CANmotor2;

	PowerDistributionPanel* m_pdp;

	AnalogPotentiometer* m_pot;

	double speed;
	bool previousAButton;
	bool previousXButton;
	double potentio;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		m_PWMmotor0 = new Victor(0);
		m_PWMmotor1 = new Victor(1);

		m_CANmotor1 = new CANTalon(1);
		m_CANmotor2 = new CANTalon(2);
		//m_motor1->SetControlMode(CANSpeedController::kSpeed);

		m_pdp = new PowerDistributionPanel(0);

		AnalogInput *ai = new AnalogInput(0);
		m_pot = new AnalogPotentiometer(ai, 360, 0);
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
		potentio = 0.0F;
	}

	void TeleopPeriodic() {
	 TeleopShoot();

	 previousAButton= m_driver->ButtonA();
	 previousXButton= m_driver->ButtonX();
	}

	void TeleopShoot() {

		potentio = m_pot->Get();
		speed = potentio/360;

//		m_CANmotor1->Set(speed);
//		m_CANmotor2->Set(speed);
//		m_PWMmotor0->Set(speed);
		m_PWMmotor1->Set(speed);


		SmartDashboard::PutNumber("speed", speed);
		SmartDashboard::PutBoolean("A Button", previousAButton);
		SmartDashboard::PutBoolean("X Button", previousXButton);
		SmartDashboard::PutNumber("Pot", potentio);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

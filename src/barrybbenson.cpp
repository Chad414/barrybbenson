#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "AHRS.h"

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Victor* m_PWMmotor0;
	Victor* m_PWMmotor1;
	CANTalon* m_CANmotor1;
	CANTalon* m_CANmotor2;

	AHRS *m_gyro;

	PowerDistributionPanel* m_pdp;

	AnalogPotentiometer* m_pot;

	double speed;
	bool previousAButton;
	bool previousXButton;
	double potentio;

public:
	barrybbenson() {


		m_CANmotor1 = new CANTalon(1);
		m_CANmotor2 = new CANTalon(2);

		m_CANmotor1->SetFeedbackDevice(CANTalon::QuadEncoder);
		m_CANmotor1->ConfigEncoderCodesPerRev(1024);

		m_pdp = new PowerDistributionPanel(0);

		m_gyro = new AHRS(I2C::Port::kMXP);

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
		speed = potentio*10;
		double slider0 = SmartDashboard::GetNumber("DB/Slider 0", 0.0);
		double slider1 = SmartDashboard::GetNumber("DB/Slider 1", 0.0);
		double slider2 = SmartDashboard::GetNumber("DB/Slider 2", 0.0);
		double slider3 = SmartDashboard::GetNumber("DB/Slider 3", 0.0);

		//m_CANmotor1->Set(slider0);
		m_CANmotor1->Set(speed);




		SmartDashboard::PutNumber("CAN1", slider0);
		SmartDashboard::PutNumber("CAN2", slider1);
		SmartDashboard::PutNumber("PWM0", slider2);
		SmartDashboard::PutNumber("PWM1", slider3);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

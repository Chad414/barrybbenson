#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"

#define MOTOR_P 0.55
#define MOTOR_I 0.0 //0.0001
#define MOTOR_D 0.0
#define MOTOR_FF 0.0 //0.03325

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	PowerDistributionPanel* m_pdp;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;


	float LJoy;
	float RJoy;
	CANTalon* m_motor1;
	CANTalon* m_motor2;

	AnalogPotentiometer* m_pot;

	      double speed_rpm, error_rpm;
	      double PID_P, PID_I, PID_D, PID_FF, PID_Current, PID_Position, PID_Speed, PID_Error, PID_Setpoint, PID_SpeedGet;
	      double potentio;




public:
	barrybbenson() {



		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);
		m_pdp = new PowerDistributionPanel(0);
		m_motor1 = new CANTalon(1);
		m_motor2 = new CANTalon(2);

		m_motor1->SetFeedbackDevice(CANTalon::QuadEncoder);
		m_motor1->ConfigEncoderCodesPerRev(256);
		m_motor2->ConfigEncoderCodesPerRev(256);
		m_motor1->SetClosedLoopOutputDirection(true);
		m_motor2->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		m_motor2->SetClosedLoopOutputDirection(true);

		//m_motor1->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
		m_motor1->SetPID(MOTOR_P, MOTOR_I, MOTOR_D);
		m_motor2->SetPID(MOTOR_P, MOTOR_I, MOTOR_D);
		m_motor1->SetAllowableClosedLoopErr(0);
		m_motor2->SetAllowableClosedLoopErr(0);

		m_motor1->SetSensorDirection(true);
		m_motor2->SetSensorDirection(true);
		m_motor1->SetClosedLoopOutputDirection(true);
		m_motor2->SetClosedLoopOutputDirection(true);
		//m_motor1->SetCloseLoopRampRate(65);

		AnalogInput *ai = new AnalogInput(0);
		m_pot = new AnalogPotentiometer(ai, 360, 0);



		speed_rpm = 0.0;


	}
	void RobotInit()
	{
	}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		speed = 0;
		previousAButton = false;
		previousXButton = false;
		m_motor1->SetPosition(0.0);


	}

	void TeleopPeriodic() {
		previousAButton = m_driver->ButtonA();
		previousXButton = m_driver->ButtonX();
		LJoy = m_driver->AxisLY();
		RJoy = m_driver->AxisRY();
		TeleopShoot();


	}



	void TeleopShoot() {
		/*if (m_driver->ButtonA())
		{
			m_motor1->SetControlMode(CANSpeedController::kSpeed);
			speed_rpm = 50;
            m_motor1->Set(speed_rpm);

		}*/
		/*if (m_driver->ButtonB())
		{
			m_motor1->SetControlMode(CANSpeedController::kPercentVbus);
			speed_rpm = 1.0;
            m_motor1->Set(speed_rpm);

		}
		else if (LJoy > .1 || LJoy < -.1)
		{
			m_motor2->SetControlMode(CANSpeedController::kPercentVbus);
			speed_rpm = 0.1;
			m_motor2->Set(speed_rpm);
			m_motor2->Set(LJoy);
		}*/

		if (LJoy > 0.2 || LJoy < -0.2)
		{
			m_motor2->SetControlMode(CANSpeedController::kPercentVbus);
			speed_rpm = 1.0;
			//m_motor2->Set(speed_rpm);
			m_motor2->Set(LJoy);
		}
		else
		{
			m_motor2->Set(0);
		}
		if (RJoy > 0.2 || RJoy < -0.2)
		{
			m_motor1->SetControlMode(CANSpeedController::kPercentVbus);
			m_motor1->Set(RJoy);
		}
		//else if (!(LJoy > .2 || LJoy < -.2)) {
		else {
			m_motor1->SetControlMode(CANSpeedController::kPercentVbus);
			speed_rpm = 0.0;
			m_motor1->Set(speed_rpm);
		}


		//potentio = m_pot->Get();
		            //speed_rpm = potentio*10;  /* speed in rpm */

		            //m_motor1->Set(speed_rpm);

		            PID_P = m_motor1->GetP();
		            PID_I = m_motor1->GetI();
		            PID_D = m_motor1->GetD();
		            PID_FF = m_motor1->GetF();
		            PID_Current = m_motor1->GetOutputCurrent();
		            PID_Position = m_motor1->GetPosition();
		            PID_Speed = m_motor1->GetSpeed();
		            PID_Error = m_motor1->GetClosedLoopError();  /* Closed loop error is is is Native Units per 100ms for Mag Encoder */
		            error_rpm = (PID_Error/4096.0)*600.0;           /* Formula for Mag Encoder to convert Native Units per 100ms to rpm  */
		            PID_Setpoint = m_motor1->GetSetpoint();

		            PID_P = m_motor2->GetP();
		            PID_I = m_motor2->GetI();
		            PID_D = m_motor2->GetD();
		            PID_FF = m_motor2->GetF();
		            PID_Current = m_motor2->GetOutputCurrent();
		            PID_Position = m_motor2->GetPosition();
		            PID_Speed = m_motor2->GetSpeed();
		            PID_Error = m_motor2->GetClosedLoopError();
		            error_rpm = (PID_Error/4096.0)*600.0;
		            PID_Setpoint = m_motor2->GetSetpoint();

		            SmartDashboard::PutNumber("PID_P", PID_P);
		            SmartDashboard::PutNumber("PID_I", PID_I);
		            SmartDashboard::PutNumber("PID_D", PID_D);
		            SmartDashboard::PutNumber("PID_FF", PID_FF);
		            SmartDashboard::PutNumber("PID_Current", PID_Current);
		            SmartDashboard::PutNumber("PID_Position", PID_Position);
		            SmartDashboard::PutNumber("PID_Speed", PID_Speed);
		            SmartDashboard::PutNumber("PID_Error", PID_Error);
		            SmartDashboard::PutNumber("PID_Setpoint", PID_Setpoint);
		            SmartDashboard::PutNumber("potentio", potentio);
		            SmartDashboard::PutNumber("speed_rpm", speed_rpm);
		            SmartDashboard::PutNumber("error_rpm", error_rpm);
		            SmartDashboard::PutNumber("Motor1 Speed", m_motor1->GetSpeed());
		            SmartDashboard::PutNumber("Motor2 Speed", m_motor2->GetSpeed());

		      }


	void TestPeriodic() {
	}

};
START_ROBOT_CLASS(barrybbenson)

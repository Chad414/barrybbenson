#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "EncoderTest.h"

#define MOTOR_P 0.02
#define MOTOR_I 0.0001
#define MOTOR_D 0.0
#define MOTOR_FF 0.03325

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
	CANTalon* m_motor1;

	AnalogPotentiometer* m_pot;

	      double speed_rpm, error_rpm;
	      double PID_P, PID_I, PID_D, PID_FF, PID_Current, PID_Position, PID_Speed, PID_Error, PID_Setpoint, PID_SpeedGet;
	      double potentio;


public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);
		m_pdp = new PowerDistributionPanel(0);
		m_motor1 = new CANTalon(0);

		m_motor1->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		m_motor1->SetClosedLoopOutputDirection(true);
		m_motor1->SetControlMode(CANTalon::kSpeed);

		m_motor1->SetPID(MOTOR_P, MOTOR_I, MOTOR_D);
		m_motor1->SetF(MOTOR_FF);
        m_motor1->Enable();
        m_motor1->SetAllowableClosedLoopErr(0);
        m_motor1->SetSensorDirection(false);
        m_motor1->SetClosedLoopOutputDirection(true);
        m_motor1->ConfigNominalOutputVoltage(+0.0F, -0.0F);
        m_motor1->ConfigPeakOutputVoltage(+12.0F, -12.0F);
        m_motor1->SetCloseLoopRampRate(65);

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

		speed_rpm = 0.0;
		potentio = 0.0F;
	}

	void TeleopPeriodic() {
		TeleopPID();
		previousXButton = m_driver->ButtonX();

/*
		if (m_shooter.ShooterAtSetpoint() == false) {
			m_shooter.SetPIDPoint(200);
			m_shooter.EnableShoot();
		}
		else {
			m_shooter.DisableShoot();
		}
*/
		SmartDashboard::PutNumber("CAN Shooter Setpoint", m_shooter.GetShooterSetpoint());
		SmartDashboard::PutBoolean("CAN At Setpoint", m_shooter.ShooterAtSetpoint());
		SmartDashboard::PutBoolean("CAN Shooter Enabled", m_shooter.ShooterIsEnabled());

		SmartDashboard::PutNumber("CAN Encoder Value", m_shooter.Get());
		SmartDashboard::PutNumber("CAN Encoder Rate", m_shooter.GetRate());

		SmartDashboard::PutNumber("CAN PID Setpoint", m_shooter.GetShooterSetpoint());

	}
};

/*	void TeleopShoot() {

		if (m_driver->ButtonX())
		{
			m_motor1->Set(0.1);
		}

		SmartDashboard::PutNumber("Encoder Value", m_shooter.Get());
		SmartDashboard::PutNumber("Encoder Rate", m_shooter.GetRate());
	}

	void TeleopPID() {
	            potentio = m_pot->Get();
	            speed_rpm = potentio*10;  /* speed in rpm */

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
	      }

		SmartDashboard::PutNumber("speed", speed);
		SmartDashboard::PutBoolean("A Button", previousAButton);
		SmartDashboard::PutBoolean("X Button", previousXButton);
	}

	void TestPeriodic() {
	}

};
*/
START_ROBOT_CLASS(barrybbenson)

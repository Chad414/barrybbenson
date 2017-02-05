#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"

#define SHOOTER_P 0.02
#define SHOOTER_I 0.0001
#define SHOOTER_D 0.0
#define SHOOTER_FF 0.03325


class barrybbenson: public HotBot {
private:
	CANTalon* m_CANmotor1;
	AnalogPotentiometer* m_pot;

	double speed_rpm, error_rpm;
	double PID_P, PID_I, PID_D, PID_FF, PID_Current, PID_Position, PID_Speed, PID_Error, PID_Setpoint, PID_SpeedGet;
	double potentio;

public:
	barrybbenson() {
		m_CANmotor1 = new CANTalon(2);
		m_CANmotor1->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		m_CANmotor1->SetClosedLoopOutputDirection(true);
		m_CANmotor1->SetControlMode(CANTalon::kSpeed);

		m_CANmotor1->SetPID(SHOOTER_P, SHOOTER_I, SHOOTER_D);
		m_CANmotor1->SetF(SHOOTER_FF);
		m_CANmotor1->Enable();
		m_CANmotor1->SetAllowableClosedLoopErr(0);
		m_CANmotor1->SetSensorDirection(false);
		m_CANmotor1->SetClosedLoopOutputDirection(true);
		m_CANmotor1->ConfigNominalOutputVoltage(+0.0F, -0.0F);
		m_CANmotor1->ConfigPeakOutputVoltage(+12.0F, -12.0F);
		m_CANmotor1->SetCloseLoopRampRate(65);

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
		speed_rpm = 0.0;
		potentio = 0.0F;
	}

	void TeleopPeriodic() {
	 TeleopShoot();

	}

	void TeleopShoot() {
		potentio = m_pot->Get();
		speed_rpm = potentio*10;  /* speed in rpm */

		m_CANmotor1->Set(speed_rpm);

		PID_P = m_CANmotor1->GetP();
		PID_I = m_CANmotor1->GetI();
		PID_D = m_CANmotor1->GetD();
		PID_FF = m_CANmotor1->GetF();
		PID_Current = m_CANmotor1->GetOutputCurrent();
		PID_Position = m_CANmotor1->GetPosition();
		PID_Speed = m_CANmotor1->GetSpeed();
		PID_Error = m_CANmotor1->GetClosedLoopError();  /* Closed loop error is is is Native Units per 100ms for Mag Encoder */
		error_rpm = (PID_Error/4096.0)*600.0;           /* Formula for Mag Encoder to convert Native Units per 100ms to rpm  */
		PID_Setpoint = m_CANmotor1->GetSetpoint();

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

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

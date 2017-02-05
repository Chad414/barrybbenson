#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"

#define SHOOTER_P 0.25
#define SHOOTER_I 0.15
#define SHOOTER_D 0.0

class barrybbenson: public HotBot {
private:
	CANTalon* m_CANmotor1;

	double speed;
	double PID_P, PID_I, PID_D, PID_Current, PID_Position, PID_Speed, PID_Error, PID_Setpoint, PID_SpeedGet;


public:
	barrybbenson() {
		m_CANmotor1 = new CANTalon(2);
		m_CANmotor1->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		m_CANmotor1->SetClosedLoopOutputDirection(true);
		m_CANmotor1->SetControlMode(CANTalon::kSpeed);
		m_CANmotor1->SetPID(SHOOTER_P, SHOOTER_I, SHOOTER_D);
		m_CANmotor1->Enable();
		m_CANmotor1->SetAllowableClosedLoopErr(0);




	}
	void RobotInit() {
	}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		speed = 0;

	}

	void TeleopPeriodic() {
	 TeleopShoot();

	}

	void TeleopShoot() {

		double slider0 = SmartDashboard::GetNumber("DB/Slider 0", 0.0);

		speed = -slider0;
		m_CANmotor1->Set(speed);

		PID_P = m_CANmotor1->GetP();
		PID_I = m_CANmotor1->GetI();
		PID_D = m_CANmotor1->GetD();
		PID_Current = m_CANmotor1->GetOutputCurrent();
		PID_Position = m_CANmotor1->GetPosition();
		PID_Speed = m_CANmotor1->GetSpeed();
		PID_Error = m_CANmotor1->GetClosedLoopError();
		PID_Setpoint = m_CANmotor1->GetSetpoint();
		PID_SpeedGet = m_CANmotor1->Get();



		SmartDashboard::PutNumber("PID_P", PID_P);
		SmartDashboard::PutNumber("PID_I", PID_I);
		SmartDashboard::PutNumber("PID_D", PID_D);
		SmartDashboard::PutNumber("PID_Current", PID_Current);
		SmartDashboard::PutNumber("PID_Position", PID_Position);
		SmartDashboard::PutNumber("PID_Speed", PID_Speed);
		SmartDashboard::PutNumber("PID_SetPoint/speed", speed);
		SmartDashboard::PutNumber("PID_Error", PID_Error);
		SmartDashboard::PutNumber("Slider0", slider0);
		SmartDashboard::PutNumber("PID_Setpoint", PID_Setpoint);
		SmartDashboard::PutNumber("PID_SpeedGet", PID_Setpoint);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

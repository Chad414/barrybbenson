
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "PIDShooter.h"

bool continuous;
bool shot;
bool shooting;

#define SETPOINT 300

class barrybbenson: public HotBot {
private:
	PIDShooter * m_pidShooter;

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	XboxController * controller;

	SmartDashboard * m_dashboard;

	double speedrpm, errorrpm, pressure;

	double PID_P, PID_I, PID_D, PID_F, PID_Current,
	PID_Position, PID_Speed,
	PID_Error, PID_Setpoint, PID_SpeedGet;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		controller = new XboxController(0);

		m_pidShooter = new PIDShooter( SHOOTER_P, SHOOTER_I, SHOOTER_D );

	}
	void RobotInit() {

	}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		speedrpm = 0;
	}

	void TeleopPeriodic() {
	 TeleopShoot();
	}

	void TeleopShoot()
	{
		if ( m_operator->ButtonPressedLT() == true )
		{
			m_pidShooter->Enable();
			m_pidShooter->SetSetpoint( SETPOINT );

			PID_P = m_pidShooter->GetP();
			PID_I = m_pidShooter->GetI();
			PID_D = m_pidShooter->GetD();
			PID_F = m_pidShooter->GetF();
			PID_Current = m_pidShooter->GetOutputCurrent();
			PID_Position = m_pidShooter->GetPosition();
			PID_Speed = m_pidShooter->GetSpeed();
			PID_Error = m_pidShooter->GetError();

			errorrpm = (PID_Error/4096.0)*600.0;

			m_dashboard->PutNumber("PID_P", PID_P);
			m_dashboard->PutNumber("PID_I", PID_I);
			m_dashboard->PutNumber("PID_D", PID_D);
			m_dashboard->PutNumber("PID_FF", PID_F);
			m_dashboard->PutNumber("PID_Current", PID_Current);
			m_dashboard->PutNumber("PID_Position", PID_Position);
			m_dashboard->PutNumber("PID_Speed", PID_Speed);
			m_dashboard->PutNumber("PID_Error", PID_Error);
			m_dashboard->PutNumber("PID_Setpoint", PID_Setpoint);
			m_dashboard->PutNumber("speed_rpm", speedrpm);
			m_dashboard->PutNumber("error_rpm", errorrpm);
			PID_Setpoint = m_pidShooter->GetSetpoint();

			m_dashboard->PutNumber( "Setpoint", m_pidShooter->GetSetpoint() );
			m_dashboard->PutNumber( "CANTalon Speed", m_pidShooter->GetRate() );


		}
	}
		



		/*
		if ((fabs(m_driver->AxisLY())) > 0.2) {
			m_pidShooter->Set(m_driver->AxisLY());
		}
		else {
			m_pidShooter->Set(0);
		}
		//m_pidShooter->Set(0.2);
		 *

		m_dashboard->PutNumberPutNumber("speed", speed);
		m_dashboard->PutNumberPutBoolean("A Button", previousAButton);
		m_dashboard->PutNumberPutBoolean("X Button", previousXButton);
	}
	*/

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

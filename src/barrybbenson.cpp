
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "PIDShooter.h"

bool continuous;
bool shooting;
enum shot
{
	NO_POWER = 0,
	LOW_POWER = 1,
	HIGH_POWER = 2
};

class barrybbenson: public HotBot {
private:
	PIDShooter * m_pidShooter;

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	SmartDashboard * m_dashboard;

	double speedrpm, errorrpm, pressure;

	double PID_P, PID_I, PID_D, PID_F, PID_Current,
	PID_Position, PID_Speed,
	PID_Error, PID_Setpoint, PID_SpeedGet;

	int shotPower;

public:
	barrybbenson() {
		m_driver = new HotJoystick(1);
		m_operator = new HotJoystick(0);
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
		shotPower = NO_POWER;
	}

	void TeleopPeriodic() {
	 TeleopShoot();
	}

	void TeleopShoot()
	{
		if ( m_operator->ButtonPressedLT() == true && shotPower != LOW_POWER )
		{
			shotPower = LOW_POWER;
			shooting = true;
		}
		if ( m_operator->ButtonPressedRT() == true )
		{
			shooting = true;
			shotPower = HIGH_POWER;
		}
		if ( shooting == true )
		{

			m_pidShooter->Enable();
			switch (shotPower)
			{
			case LOW_POWER:
			{
				m_pidShooter->SetSetpoint( LOW_SETPOINT );
				break;
			}
			case HIGH_POWER:
			{
				m_pidShooter->SetSetpoint( HI_SETPOINT );
				break;
			}

			}
			PID_P = m_pidShooter->GetShooterP();
			PID_I = m_pidShooter->GetShooterI();
			PID_D = m_pidShooter->GetShooterD();
			PID_F = m_pidShooter->GetShooterF();
			PID_Current = m_pidShooter->GetOutputCurrent();
			PID_Position = m_pidShooter->GetPosition();
			PID_Speed = m_pidShooter->GetSpeed();
			PID_Error = m_pidShooter->GetError();

			errorrpm = (PID_Error/4096.0)*600.0;

			m_pidShooter->OutputValues(m_dashboard);
			m_dashboard->PutNumber("speed_rpm", speedrpm);
			m_dashboard->PutNumber("error_rpm", errorrpm);
			PID_Setpoint = m_pidShooter->GetSetpoint();

			m_dashboard->PutNumber( "Setpoint", m_pidShooter->GetSetpoint() );
			m_dashboard->PutNumber( "CANTalon Speed", m_pidShooter->GetRate() );

			if ( (m_operator->ButtonPressedLT() == true || m_operator->ButtonPressedRT() == true) && shooting == true )
			{
				shotPower = NO_POWER;
				shooting = false;
			}
			if ( shooting == false )
			{
				m_pidShooter->DisableShooter();
			}
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

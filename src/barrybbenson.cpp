#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "PIDShooter.h"

bool continuous;
bool shot;
bool shooting;

double setpoint;

double p;
double i;
double d;

class barrybbenson: public HotBot {
private:
	PIDShooter * m_pidShooter;

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	SmartDashboard * m_dashboard;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		m_pidShooter = new PIDShooter( 1, 0, 0 );

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
	 TeleopShoot();
	}

	void TeleopShoot() {
		/*if (m_driver->ButtonX() ) {

						shooting = true;
						setpoint = 300; // placeholder value
			}
		else if (m_driver->ButtonA() ) {

						shooting = true;
						setpoint = -300; //placeholder value
			}
		if ( shot == true )
		{ */
			m_pidShooter->Enable();
			m_pidShooter->SetSetpoint( 300 );

			while ( shooting == true )
				{
					if ( m_driver->ButtonX() )
					{
						shooting = false;
						m_pidShooter->DisableShooter();
					}
				}
					m_dashboard->PutNumber( "Setpoint", m_pidShooter->GetSetpoint() );
					m_dashboard->PutNumber( "CANTalon Speed", m_pidShooter->GetRate() );


		}
	//}
		



		/*
		if ((fabs(m_driver->AxisLY())) > 0.2) {
			m_shooter1->Set(m_driver->AxisLY());
		}
		else {
			m_shooter1->Set(0);
		}
		//m_shooter1->Set(0.2);
		 *

		SmartDashboard::PutNumber("speed", speed);
		SmartDashboard::PutBoolean("A Button", previousAButton);
		SmartDashboard::PutBoolean("X Button", previousXButton);
	}
	*/

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)

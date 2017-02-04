#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include <CANTalon.h>

bool continuous;
bool shot;
bool shooting;

double setpoint;

int p;
int i;
int d;

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	CANTalon * m_shooter1;
	CANTalon * m_shooter2;
	CANTalon * m_paddle;

	PIDController * m_shooterPID;

	Encoder * m_shooterEncoder;

	PowerDistributionPanel* m_pdp;
	
	Timer * m_shooterTime;

	double speed;
	//int timesPressed;
	bool previousAButton;
	bool previousXButton;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);

		m_shooter1->SetFeedbackDevice( CANTalon::CtreMagEncoder_Relative );

		m_shooterPID = new PIDController( p, i, d, m_shooter1, m_shooterEncoder );
		
		m_shooterTime = new Timer();

		m_pdp = new PowerDistributionPanel( 0 );
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
		m_shooterPID->SetSetpoint( 0 );
		m_shooterPID->SetContinuous( continuous );

		m_shooterPID->SetPID( 1, 0 , 0 );

	    m_shooterTime->Reset();

		shot = false;
	}

	void TeleopPeriodic() {
	 TeleopShoot();

	 previousAButton= m_driver->ButtonA();
	 previousXButton= m_driver->ButtonX();
	}

	void TeleopShoot() {
			if (m_driver->ButtonX() ) {
						shot = true;
						shooting = true;
						setpoint = 2000; // placeholder values
			}
			else if (m_driver->ButtonA() ) {
						shot = true;
						shooting = true;
						setpoint = -2000; //placeholder values
			}
		if ( shot == true )
		{
			m_shooterPID->Enable();
			m_shooterPID->SetSetpoint( setpoint );

			while ( shooting == true )
				{

					if ( m_shooterPID->GetError() > 1000 )
						{
							m_shooterPID->SetPID( 5, 1, 2 );
						}
					else if ( m_shooterPID->GetError() > 500 && m_shooterPID->GetError() < 1000 )
						{
							m_shooterPID->SetPID( 3, 0, 1 );
						}
					else
						{
							m_shooterPID->SetPID( 1, 0, 0 );
						}

					if ( m_driver->ButtonX() )
						{
							shooting = false;
						}
				}
					m_shooterPID->SetSetpoint( 0 );
		}
	}
		



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


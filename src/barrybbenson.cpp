#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "Gear.h"

class barrybbenson: public HotBot {
private:

	HotJoystick* m_driver;
	HotJoystick* m_operator;

	Victor* m_shooter1;
	Victor* m_shooter2;

	PowerDistributionPanel* m_pdp;

	Gear m_gear;

	double speed;

	bool previousAButton;
	bool previousXButton;

public:
	barrybbenson() {
		m_driver = new HotJoystick(0);
		m_operator = new HotJoystick(1);
	}
	void RobotInit() {
	}

	void DisabledPeriodic() {
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
		TeleopGear();
	}

	void TeleopGear() {
		if (fabs(m_driver->AxisLY()) > 0.2) {
			m_gear.SetGearMode(false);
			m_gear.SetGearArmPosition(m_driver->AxisLY());
		}
		else if (m_driver->ButtonA()) {
			m_gear.SetGearMode(true);
			m_gear.SetGearArmPosition(10);
		}
		else if (m_driver->ButtonB()) {
			m_gear.ZeroGearArmPosition();
		}
		else {
			m_gear.SetGearArmPosition(0.0);
		}

		SmartDashboard::PutNumber("Gear Commanded", m_gear.GetGearCommandedSpeed());
		SmartDashboard::PutNumber("Gear Position", m_gear.GetGearArmPosition());
		SmartDashboard::PutNumber("Gear Setpoint", m_gear.GetGearSetpoint());
	}

	void TestPeriodic() {
	}
};

START_ROBOT_CLASS(barrybbenson)

#include "Intake.h"

Intake::Intake()
	:	m_intakeRoller(TALON_INTAKE_ROLLER),
		m_intakeArm(SOLENOID_INTAKE_ARM)
{

}
Intake::~Intake()
{

}
void Intake::SetArm(bool on){
	m_intakeArm.Set(on);
}

void Intake::SetRoller(double value) {
	m_intakeRoller->Set(value);
}


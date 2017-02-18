#include "Intake.h"

Intake::Intake()
	:	m_intakeRoller(TALON_INTAKE_ROLLER),
		m_intakeArm(SOLENOID_INTAKE_ARM)
{

}
void Intake::SetArm(bool b){
	m_intakeArm.Set(b);
}

void Intake::SetRoller(double value) {
	m_intakeRoller->Set(value);
}


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

	ArmStatus = on;
}

bool Intake::GetArm() {
	return ArmStatus;
}

void Intake::SetRoller(double value) {
	m_intakeRoller->Set(value);
}


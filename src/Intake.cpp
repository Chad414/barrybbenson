#include "Intake.h"

Intake::Intake()
	:	m_intakeRoller(TALON_INTAKE_ROLLER),
		m_intakeArm(SOLENOID_INTAKE_ARM)
{
	m_intakeArm = new Solenoid(SOLENOID_INTAKE_ARM);
	m_intakeRoller = new CANTalon(TALON_INTAKE_ROLLER);
}
void Intake::SetArm(bool on){
	m_intakeArm -> Set(on);
}

void Intake::ApplyArm() {
	m_intakeArm -> Set(true);
}

void Intake::ReleaseArm() {
	m_intakeArm -> Set(false);
}

void Intake::ApplyRoller() {
	m_intakeRoller -> Set(0.5);
}

void Intake::StopRoller() {
	m_intakeRoller -> Set(0.0);
}

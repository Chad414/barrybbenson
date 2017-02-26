#include "Intake.h"

Intake::Intake()
	:	m_intakeRoller(TALON_INTAKE_ROLLER),
		m_intakeArmOut(SOLENOID_INTAKE_ARM_OUT),
		m_intakeArmIn(SOLENOID_INTAKE_ARM_IN),
		m_hopperOut(SOLENOID_HOPPER_OUT),
		m_hopperIn(SOLENOID_HOPPER_IN)
{

}
Intake::~Intake()
{

}
void Intake::SetIntakeArm(bool on){
	if (GetHopper() == true) {
		m_intakeArmIn.Set(!on);
		m_intakeArmOut.Set(on);
		IntakeArm = on;
	}
}

bool Intake::GetIntakeArm() {
	return IntakeArm;
}

void Intake::SetIntakeRoller(double value) {
	m_intakeRoller.Set(value);
	IntakeRoller = value;
}

double Intake::GetIntakeRoller() {
	return m_intakeRoller.Get();
}

void Intake::SetHopper(bool on){
	m_hopperOut.Set(on);
	m_hopperIn.Set(!on);
	Hopper = on;
}

bool Intake::GetHopper() {
	return Hopper;
}

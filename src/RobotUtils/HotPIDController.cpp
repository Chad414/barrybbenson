
#include <RobotUtils/HotPIDController.h>

/******************************
 * 	Constructors
 ******************************/
HotPIDController::HotPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, source, output, period) {
	m_source = source;
	def_p = p;
	def_i = i;
	def_d = d;
}

HotPIDController::HotPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period)
: PIDController(p, i, d, f, source, output, period) {
	m_source = source;
	def_p = p;
	def_i = i;
	def_d = d;
}

/******************************
 * 	Configuration
 ******************************/

/******************************
 * 	Enable/Disable
 ******************************/
void HotPIDController::Enable() {
	if (!IsEnabled()) {
		PIDController::Enable();
	}
}

void HotPIDController::Disable() {
	if (IsEnabled()) {
		PIDController::Disable();
	}
}

/******************************
 * 	Set PID set point
 ******************************/
void HotPIDController::SetSetpoint(float setpoint, bool enable) {
	PIDController::SetSetpoint(setpoint);
	if (enable) {
		Enable();
	}
}

/******************************
 * 	Get Input/Output Value
 ******************************/
double HotPIDController::GetInput() const {
	return m_source->PIDGet();
}

double HotPIDController::GetOutput() const {
	return Get();
}
/******************************
 * 	Control PID
 ******************************/
/**
 * 	Get Default PID
 */
float HotPIDController::GetDefP() {
	return def_p;
}
float HotPIDController::GetDefI() {
	return def_i;
}
float HotPIDController::GetDefD() {
	return def_d;
}

/**
 * 	Modify PID
 */
void HotPIDController::SetP(float p) {
	SetPID(p, GetI(), GetD());
}
void HotPIDController::SetI(float i) {
	SetPID(GetP(), i, GetD());
}
void HotPIDController::SetD(float d) {
	SetPID(GetP(), GetI(), GetD());
}

/**
 * 	Modify Default PID
 */
void HotPIDController::SetDefPID(float p, float i, float d) {
	def_p = p;
	def_i = i;
	def_d = d;
}
void HotPIDController::SetDefP(float p) {
	SetDefPID(p, GetDefI(), GetDefD());
}
void HotPIDController::SetDefI(float i) {
	SetDefPID(GetDefP(), i, GetDefD());
}
void HotPIDController::SetDefD(float d) {
	SetDefPID(GetDefP(), GetDefI(), d);
}

/**
 * 	Reset PID To Default Value
 */
void HotPIDController::ResetToDefPID() {
	SetPID(def_p, def_i, def_d);
}

/**
 * 	Set Dynamic PID
 */
void HotPIDController::DynamicPID(float range, float p, float i, float d) {
	m_dynamicPIDs[range] = new PIDCoef(p, i, d);
}

/**
 * 	Update PID For Update
 */
void HotPIDController::Update() {
	for (std::map<float, PIDCoef*>::iterator it = m_dynamicPIDs.begin(); it != m_dynamicPIDs.end(); it++) {
		if (it->first < fabs(GetError())) {
			SetPID(it->second->GetP(), it->second->GetI(), it->second->GetD());
			return;
		}
	}

	ResetToDefPID();
}

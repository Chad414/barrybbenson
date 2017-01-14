#include <RobotUtils/HotBot.h>

/******************************
 * 	Constructor
 ******************************/
HotBot::HotBot(std::string dirPath) {
}
HotBot::~HotBot() {}

/**
 * 	Start
 */
void HotBot::Start(){
}

/**
 * 	Count Subsystem
 */
int HotBot::SubsystemCount() {
	return m_subsystems.size();
}


/******************************
 * 	Set subsystem
 * 		This function should only be called from subsystem constructor
 ******************************/
void HotBot::SetSubsystem(HotSubsystem* subsystem) {
	m_subsystems[subsystem->GetName()] = subsystem;
}

/******************************
 * 	Start Robot Routines
 ******************************/
void HotBot::RobotInit() {
	BeforeRobot();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeRobot();
	}
}

void HotBot::DisabledInit() {
	BeforeDisabled();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeDisabled();
	}
}

void HotBot::AutonomousInit() {
	BeforeAuton();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeAuton();
	}
}

void HotBot::TeleopInit() {
	BeforeTeleop();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeTeleop();
	}
}

void HotBot::TestInit() {
	BeforeTeleop();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeTest();
	}
}

void HotBot::DisabledPeriodic() {
	DisabledPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->DisabledPeriod();
		it->second->GeneralPeriod();
	}
}

void HotBot::AutonomousPeriodic() {
	AutonPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->AutonPeriod();
		it->second->GeneralPeriod();
	}
}

void HotBot::TeleopPeriodic() {
	TeleopPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TeleopPeriod();
		it->second->GeneralPeriod();
	}
}

void HotBot::TestPeriodic() {
	TestPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TestPeriod();
		it->second->GeneralPeriod();
	}
}

/******************************
 * 	To be Defined
 ******************************/
void HotBot::BeforeRobot() {}
void HotBot::BeforeDisabled() {}
void HotBot::BeforeAuton() {}
void HotBot::BeforeTeleop() {}
void HotBot::BeforeTest() {}

void HotBot::DisabledPeriod() {}
void HotBot::AutonPeriod() {}
void HotBot::TeleopPeriod() {}
void HotBot::TestPeriod() {}
void HotBot::GeneralPeriod() {}


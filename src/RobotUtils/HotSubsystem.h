
#ifndef SRC_HOTSUBSYSTEM_H_
#define SRC_HOTSUBSYSTEM_H_

#include <RobotUtils/HotBot.h>
#include <RobotUtils/HotJoystick.h>
#include <string>

class HotBot;

class HotSubsystem {
public:
	/******************************
	 * 	Constructor
	 * 		In this function, we connect subsystem and hot bot.
	 ******************************/

	HotSubsystem(HotBot* bot, std::string name);
	virtual ~HotSubsystem();

	/******************************
	 * 	Getter
	 ******************************/
	std::string GetName() const;
	HotBot* GetBot() const;

	/******************************
	 * 	Initialization
	 ******************************/
	virtual void BeforeRobot();
	virtual void BeforeDisabled();
	virtual void BeforeAuton();
	virtual void BeforeTeleop();
	virtual void BeforeTest();

	/******************************
	 *	Period
	 ******************************/
	virtual void DisabledPeriod();
	virtual void AutonPeriod();
	virtual void TeleopPeriod();
	virtual void TestPeriod();

	virtual void GeneralPeriod();
private:
	std::string m_name;
	HotBot* m_bot;
};

#endif /* SRC_HOTSUBSYSTEM_H_ */

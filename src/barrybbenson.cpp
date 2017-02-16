#include <WPILib.h>
#include <RobotUtils/RobotUtils.h>
#include <AutonPeriodics.h>
#include <AutonStructs.h>



class barrybbenson: public HotBot
{
private:

	autonChoice m_autonChoice;

public:
	barrybbenson()
	{
		m_autonChoice = {LEFT, RED, GEAR};
	}
	void RobotInit()
	{

	}



	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		switch (m_autonChoice.StartPosition)
		{
		case LEFT:
			leftPeriodic(m_autonChoice);
			break;
		case CENTER:
			centerPeriodic(m_autonChoice);
			break;
		case RIGHT:
			rightPeriodic(m_autonChoice);
			break;
		}
		
		
	}


};




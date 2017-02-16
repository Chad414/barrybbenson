/*
 * AutonPeriodics.cpp
 *
 *  Created on: Feb 16, 2017
 *      Author: Paul
 */
#include <AutonPeriodics.h>

void leftPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Alliance)
	{
	case RED:
		leftRedPeriodic(autonChoice);
		break;
	case BLUE:
		leftBluePeriodic(autonChoice);
		break;
	}
}

void centerPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Alliance)
		{
		case RED:
			centerRedPeriodic(autonChoice);
			break;
		case BLUE:
			centerBluePeriodic(autonChoice);
			break;
		}
}

void rightPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Alliance)
		{
		case RED:
			rightRedPeriodic(autonChoice);
			break;
		case BLUE:
			rightBluePeriodic(autonChoice);
			break;
		}
}

void leftRedPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
	{
	case GEAR:
					//do gear routine here
		break;
	case GEAR_AND_SHOOT:
					//do gear and shoot routine here
		break;
	/*
	 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
	 * All of these routines will either be motion profiling or PID control
	 */
	}
}

void leftBluePeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
		{
		case GEAR:
						//do gear routine here
			break;
		case GEAR_AND_SHOOT:
						//do gear and shoot routine here
			break;
		/*
		 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
		 * All of these routines will either be motion profiling or PID control
		 */
		}
}

void rightRedPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
		{
		case GEAR:
						//do gear routine here
			break;
		case GEAR_AND_SHOOT:
						//do gear and shoot routine here
			break;
		/*
		 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
		 * All of these routines will either be motion profiling or PID control
		 */
		}
}

void rightBluePeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
		{
		case GEAR:
						//do gear routine here
			break;
		case GEAR_AND_SHOOT:
						//do gear and shoot routine here
			break;
		/*
		 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
		 * All of these routines will either be motion profiling or PID control
		 */
		}
}

void centerRedPeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
		{
		case GEAR:
						//do gear routine here
			break;
		case GEAR_AND_SHOOT:
						//do gear and shoot routine here
			break;
		/*
		 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
		 * All of these routines will either be motion profiling or PID control
		 */
		}
}

void centerBluePeriodic(autonChoice autonChoice)
{
	switch (autonChoice.Routine)
		{
		case GEAR:
						//do gear routine here
			break;
		case GEAR_AND_SHOOT:
						//do gear and shoot routine here
			break;
		/*
		 * Other routines will be added later. Examples include a shoot 50 balls, or shoot 50 balls plus a gear.
		 * All of these routines will either be motion profiling or PID control
		 */
		}
}

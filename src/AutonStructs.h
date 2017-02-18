/*
 * AutonStructs.h
 *
 *  Created on: Feb 16, 2017
 *      Author: Paul
 */

#ifndef SRC_AUTONSTRUCTS_H_
#define SRC_AUTONSTRUCTS_H_

enum startPosition		//The position you start at, while looking out from the drivers station.
{
	LEFT,
	CENTER,
	RIGHT
};

enum alliance
{
	RED,
	BLUE
};

enum routine
{
	GEAR,				//Only sets gear
	GEAR_AND_SHOOT		//Sets gear and shoots 10 balls
};

struct autonChoice		//Change this using some kind of UI, this will be used to save what we decide for our auton.
{
	startPosition StartPosition;
	alliance Alliance;
	routine Routine;
};



#endif /* SRC_AUTONSTRUCTS_H_ */

/*
 * MotorConstants.h
 *
 *  Created on: Jan 31, 2017
 *      Author: Jakob
 */

#ifndef SRC_MOTORCONSTANTS_H_
#define SRC_MOTORCONSTANTS_H_


enum MotorType // Names of motors
{
	kBaneBot550
};

const double MotorVelocities[] = { // Maximum speeds in rpm
		17100
};

const double MotorAccelerations[] = { // Maximum accelerations in rpm/s
		500
};

#endif /* SRC_MOTORCONSTANTS_H_ */

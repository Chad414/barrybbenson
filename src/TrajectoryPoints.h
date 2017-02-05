/*
 * TrajectoryPoints.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#ifndef SRC_TRAJECTORYPOINTS_H_
#define SRC_TRAJECTORYPOINTS_H_


#include <vector>

const int kMotionProfileSz = 128;



/* 1,024 Ticks = 1 Revolution
 * 1 rev per second = 1,024 ticks / sec = 102.4 velocity
 *
 * Testing Maximum Velocity: 7500 rpm
 *  	-125 rps
 *  	-128,000 ticks/s
 *  	-12,800 velocity
 *
 * Testing Maximum Acceleration: 500 rpm/s
 *  	-8.33 rps
 *  	-8,533.33 ticks/s/s
 *  	-853.333 acceleration
 *
 * Testin Maximum Jerk: 250 rpm/s
 *  	-4.165 rps
 *  	-4,266.67 ticks/s/s/s
 *  	-426.67 jerk
 *
 * Testing Target Distance 100 revolutions
 *  	-102,400 distance
 */




std::vector<std::vector<double>> kMotionProfile();

#endif /* SRC_TRAJECTORYPOINTS_H_ */

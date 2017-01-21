/*
 * TrajectoryPoints.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#ifndef SRC_TRAJECTORYPOINTS_H_
#define SRC_TRAJECTORYPOINTS_H_

const int kMotionProfileSz = 1;



// One DEGREE UNIT = 5.625 degrees = 4 encoder ticks
// Position = One DEGREE UNIT
// Velocity = 1/10 DEGREE UNIT per ms
// Time = duration in ms
const double kMotionProfile[][3] = {
{0,	0, 0}};

#endif /* SRC_TRAJECTORYPOINTS_H_ */

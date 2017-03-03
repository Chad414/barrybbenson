/*
 * CameraHandler.h
 *
 *  Created on: Feb 28, 2017
 *      Author: chada
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#define GYRO_GAIN 24.86 // Degrees per X position

#include "WPILib.h"

class CameraHandler {
public:
	CameraHandler();
	virtual ~CameraHandler();

	double GetTargetNormalizedCenter();
	double GetAngle();
	bool seeTarget();
};

#endif /* CAMERAHANDLER_H_ */

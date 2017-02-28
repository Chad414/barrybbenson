/*
 * CameraHandler.h
 *
 *  Created on: Feb 28, 2017
 *      Author: chada
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#include "WPILib.h"

class CameraHandler {
public:
	CameraHandler();
	virtual ~CameraHandler();

	double GetTargetNormalizedCenter();
	double GetAngle();
};

#endif /* CAMERAHANDLER_H_ */

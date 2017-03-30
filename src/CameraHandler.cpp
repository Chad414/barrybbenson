/*
 * CameraHandler.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: chada
 */

#include "CameraHandler.h"

CameraHandler::CameraHandler() {
	// TODO Auto-generated constructor stub

}

CameraHandler::~CameraHandler() {
	// TODO Auto-generated destructor stub
}

double CameraHandler::GetPegTargetNormalizedCenter() {
	return SmartDashboard::GetNumber("Peg X", 0.0);
}

double CameraHandler::GetPegAngle() {
	return GetPegTargetNormalizedCenter() * GYRO_GAIN;
}

bool CameraHandler::seePegTarget() {
	if (fabs(GetPegTargetNormalizedCenter()) > 0.0) {
		return true;
	} else {
		return false;
	}
}

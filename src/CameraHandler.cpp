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

double CameraHandler::GetTargetNormalizedCenter() {
	return SmartDashboard::GetNumber("Peg X", 0.0);
}

double CameraHandler::GetAngle() {
	return GetTargetNormalizedCenter() * GYRO_GAIN;
}

bool CameraHandler::seeTarget() {
	if (GetTargetNormalizedCenter() > 0) {
		return true;
	} else {
		return false;
	}
}

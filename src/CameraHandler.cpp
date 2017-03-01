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
	return SmartDashboard::GetNumber("ImageXCenter", 0.0);
}

double CameraHandler::GetAngle() {
	return GetTargetNormalizedCenter() * -22.0287958;
}

bool CameraHandler::seeTarget() {
	if (GetTargetNormalizedCenter() > 0) {
		return true;
	} else {
		return false;
	}
}

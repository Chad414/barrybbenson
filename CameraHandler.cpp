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
	return GetTargetNormalizedCenter() * 34.25;
}

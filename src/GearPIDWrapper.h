/*
 * GearPIDWrapper.h
 *
 *  Created on: Jan 24, 2017
 *      Author: HOT Team
 */

#ifndef SRC_GEARPIDWRAPPER_H_
#define SRC_GEARPIDWRAPPER_H_

#include "WPILib.h"
#include "Gear.h"

class Gear;

class GearPIDWrapper: public PIDSource, public PIDOutput{
public:
	GearPIDWrapper();
	virtual ~GearPIDWrapper();

	double WristPIDGet();
	double ArmPIDGet();

	void PIDWrite(float output);

private:
	Gear m_gear;
};

#endif /* SRC_DISTANCEPIDWRAPPER_H_ */

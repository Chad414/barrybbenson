/*
 * Instrumentation.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#ifndef SRC_INSTRUMENTATION_H_
#define SRC_INSTRUMENTATION_H_

#include <iomanip>
#include "WPILib.h"
#include "CANTalon.h"

class Instrumentation {
public:
	Instrumentation();
	static void OnNoProgress();
	static void OnUnderrun();
	static const char * StrOutputEnable(unsigned int value);
	static void Process(CANTalon::MotionProfileStatus & status);

	virtual ~Instrumentation();
};

#endif /* SRC_INSTRUMENTATION_H_ */

/*
 * Instrumentation.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: Chad
 */

#include <Instrumentation.h>

Instrumentation::Instrumentation() {
}

void Instrumentation::OnNoProgress() {
	std::cout << "NOPROGRESS\n";
}

void Instrumentation::OnUnderrun() {
	std::cout << "UNDERRUN\n";
}

const char * Instrumentation::StrOutputEnable(unsigned int value) {
	static const char table[][6] = {" Dis "," En  ","Hold ","Inval"};
	if (value > 3) {
		value = 3;
	}
	return table[value];
}

 void Instrumentation::Process(CANTalon::MotionProfileStatus & status) {
	static double timeout = 0;
	static int count = 0;

	const char delim[] = "\t";
	const char endline[] = "\n";

	double now = GetTime();

	if ((now - timeout) > 0.2) {
		timeout = now; // Loops every 200ms

		if(--count <= 0) {
			count = 8;

			std::cout
				<< "outputEnable" << delim
				<< "topBufferRem" << delim
				<< "topBufferCnt" << delim
				<< "btmBufferCnt" << delim
				<< "     IsValid" << delim
				<< " HasUnderrun" << delim
				<< "  IsUnderrun" << delim
				<< "      IsLast" << delim
				<< "     VelOnly" << delim
				<< "     targPos" << delim
				<< "     targVel" << delim
				<< " profSlotSel" << delim
				<< "   timeDurMs" << delim

				<< endline;
		}
		std::cout
			<< std::setw(12)<< StrOutputEnable(status.outputEnable) << delim
			<< std::setw(12)<< status.topBufferRem << delim
			<< std::setw(12)<< status.topBufferCnt << delim
			<< std::setw(12)<< status.btmBufferCnt << delim
			<< std::setw(12)<< (status.activePointValid ? "1" : "") << delim
			<< std::setw(12)<< (status.hasUnderrun ? "1" : "") << delim
			<< std::setw(12)<< (status.isUnderrun ? "1" : "") << delim
			<< std::setw(12)<< (status.activePoint.isLastPoint ? "1" : "") << delim
			<< std::setw(12)<< (status.activePoint.velocityOnly ? "1" : "") << delim
			<< std::setw(12)<< status.activePoint.position << delim
			<< std::setw(12)<< status.activePoint.velocity << delim
			<< std::setw(12)<< status.activePoint.profileSlotSelect << delim
			<< std::setw(12)<< status.activePoint.timeDurMs << delim

			<< endline;
	}
}

Instrumentation::~Instrumentation() {
}


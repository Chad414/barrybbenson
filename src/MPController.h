/*
 * MPController.h
 *
 *  Created on: Feb 14, 2017
 *      Author: Jakob
 */

#ifndef SRC_MPCONTROLLER_H_
#define SRC_MPCONTROLLER_H_

#include <WPILib.h>
#include <CANTalon.h>
#include <vector>

#include "PID.h"
#include "MP.h"

#define MINIMUM_POINTS_IN_TALON 5




class MPController {
private:
	PIDF m_pidf;

	CANTalon *m_talon;
	ArrayDimension2 m_trajectoryPoints;

	bool isEnabled;
	double m_deadband;

	Notifier m_notifier;
public:
	MPController(
			PIDF pidf,
			ArrayDimension2 trajectoryPoints,
			CANTalon *talon,
			double deadband = 25
			);

	void SetPIDF(PIDF pidf);

	void Control();

	void Enable();
	bool IsEnabled();
	void Disable();

	bool OnTarget();
private:
	void Fill();
	void Periodic();
};

#endif /* SRC_MPCONTROLLER_H_ */

/*
 * periodics.h
 *
 *  Created on: Feb 16, 2017
 *      Author: Paul
 */

#ifndef SRC_AUTONPERIODICS_H_
#define SRC_AUTONPERIODICS_H_
#include <AutonStructs.h>

//Top level functions, these include only a switch statement based on alliance, leading to the lower functions
//***************************\\
void leftPeriodic(autonChoice);
void centerPeriodic(autonChoice);
void rightPeriodic(autonChoice);
//***************************\\

//The lower level functions, include a switch statement for the choice of routine, should include functions or code that directly control robot actions.
//***************************\\
void leftRedPeriodic(autonChoice);
void leftBluePeriodic(autonChoice);
void centerRedPeriodic(autonChoice);
void centerBluePeriodic(autonChoice);
void rightRedPeriodic(autonChoice);
void rightBluePeriodic(autonChoice);
//***************************\\

#endif /* SRC_AUTONPERIODICS_H_ */

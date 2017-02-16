/*
 * PID.h
 *
 *  Created on: Feb 16, 2017
 *      Author: Jakob
 */

#ifndef SRC_PID_H_
#define SRC_PID_H_


#define DRIVE_P_R 0.0
#define DRIVE_I_R 0.0
#define DRIVE_D_R 0.0
#define DRIVE_F_R 0.0

#define DRIVE_P_L 0.0
#define DRIVE_I_L 0.0
#define DRIVE_D_L 0.0
#define DRIVE_F_L 0.0

struct PIDF
{
	double p, i, d, f;
};

PIDF PIDF_LEFT();
PIDF PIDF_RIGHT();

#endif /* SRC_PID_H_ */

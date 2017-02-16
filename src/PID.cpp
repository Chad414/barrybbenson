#include "PID.h"

PIDF PIDF_LEFT()
{
	return {
		DRIVE_P_L,
		DRIVE_I_L,
		DRIVE_D_L,
		DRIVE_F_L};
}

PIDF PIDF_RIGHT()
{
	return {
		DRIVE_P_R,
		DRIVE_I_R,
		DRIVE_D_R,
		DRIVE_F_R
	};
}

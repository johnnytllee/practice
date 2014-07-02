#include "log.h"

typedef enum
{
    IMTK_PB_CTRL_SPEED_FR_64X   =   -6400000,   ///< Fast Rewind 64X
    IMTK_PB_CTRL_SPEED_FR_32X   =   -3200000,   ///< Fast Rewind 32X
    IMTK_PB_CTRL_SPEED_FR_16X   =   -1600000,   ///< Fast Rewind 16X
    IMTK_PB_CTRL_SPEED_FR_8X    =   -800000,    ///< Fast Rewind 8X
    IMTK_PB_CTRL_SPEED_FR_4X    =   -400000,    ///< Fast Rewind 4X
    IMTK_PB_CTRL_SPEED_FR_2X    =   -200000,    ///< Fast Rewind 2X
    IMTK_PB_CTRL_SPEED_ZERO     =   0,          ///< paused; only for IMtkPb_Ctrl_GetPlayParam() and not for IMtkPb_Ctrl_SetSpeed().
    IMTK_PB_CTRL_SPEED_1X       =   100000,     ///< normal play; only for IMtkPb_Ctrl_GetPlayParam() and not for IMtkPb_Ctrl_SetSpeed().
    IMTK_PB_CTRL_SPEED_FF_2X    =   200000,     ///< Fast Forward 2X
    IMTK_PB_CTRL_SPEED_FF_4X    =   400000,     ///< Fast Forward 4X
    IMTK_PB_CTRL_SPEED_FF_8X    =   800000,     ///< Fast Forward 8X
    IMTK_PB_CTRL_SPEED_FF_16X   =   1600000,    ///< Fast Forward 16X
    IMTK_PB_CTRL_SPEED_FF_32X   =   3200000,     ///< Fast Forward 32X
    IMTK_PB_CTRL_SPEED_FF_64X   =   6400000,     ///< Fast Forward 64X
    IMTK_PB_CTRL_SPEED_SF_1_2X    =  200,    ///< Slow Forward 1/2X, Lib Master only
    IMTK_PB_CTRL_SPEED_SF_1_4X    =  400,    ///< Slow Forward 1/4X, Lib Master only
    IMTK_PB_CTRL_SPEED_SF_1_8X    =  800,    ///< Slow Forward 1/8X, Lib Master only
    IMTK_PB_CTRL_SPEED_SF_1_16X   =  1600,   ///< Slow Forward 1/16X, Lib Master only
    IMTK_PB_CTRL_SPEED_SF_1_32X   =  3200,   ///< Slow Forward 1/32X, Lib Master only
    IMTK_PB_CTRL_SPEED_SR_1_2X    =  -200,   ///< Slow Rewind 1/2X, Lib Master only,   Slow reverse function is not ready now.
    IMTK_PB_CTRL_SPEED_SR_1_4X    =  -400,   ///< Slow Rewind 1/4X, Lib Master only,   Slow reverse function is not ready now.
    IMTK_PB_CTRL_SPEED_SR_1_8X    =  -800,   ///< Slow Rewind 1/8X, Lib Master only,   Slow reverse function is not ready now.
    IMTK_PB_CTRL_SPEED_SR_1_16X   =  -1600,  ///< Slow Rewind 1/16X, Lib Master only,   Slow reverse function is not ready now.
    IMTK_PB_CTRL_SPEED_SR_1_32X   =  -3200,  ///< Slow Rewind 1/32X, Lib Master only,   Slow reverse function is not ready now.

} IMTK_PB_CTRL_SPEED_T;

int main(void)
{
	IMTK_PB_CTRL_SPEED_T speed = IMTK_PB_CTRL_SPEED_SF_1_2X;
	if (speed > IMTK_PB_CTRL_SPEED_FF_64X) {
		LOGI("expected");
	} else {
		LOGI("unexpected");
	}
	return(0);
}


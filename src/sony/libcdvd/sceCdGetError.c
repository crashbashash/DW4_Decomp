/* sceCdGetError.c - sceCdGetError: the last error cdvdman reported. */
#include "dw4/eekernel.h"
#include "dw4/sony/libcdvd.h"

int sceCdGetError(void)
{
    int error;

    if (_sceCd_scmd_prechk(CD_PRECHK_GET_ERROR) == 0) {
        return -1;
    }
    if (sceSifCallRpc(&_sceCd_cd_scmd, CD_SCMD_GET_ERROR, 0, 0, 0, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return -1;
    }
    error = UNCACHED_WORD(_sceCd_scmdrdata);
    SignalSema(_sceCd_scmd_semid);
    return error;
}

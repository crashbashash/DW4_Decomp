/* sceCdBreak.c - sceCdBreak: aborts the command in flight. */
#include "dw4/eekernel.h"
#include "dw4/sony/libcdvd.h"

int sceCdBreak(void)
{
    int result;

    if (_sceCd_scmd_prechk(CD_PRECHK_BREAK) == 0) {
        return 0;
    }
    sceCdCbfunc_num = SCECdFuncBreak;
    if (sceSifCallRpc(&_sceCd_cd_scmd, CD_SCMD_BREAK, 0, 0, 0, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        sceCdCbfunc_num = 0;
        return 0;
    }
    sceCdCbfunc_num = 0;
    result = UNCACHED_WORD(_sceCd_scmdrdata);
    SignalSema(_sceCd_scmd_semid);
    return result;
}

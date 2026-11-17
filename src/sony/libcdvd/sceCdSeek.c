/* sceCdSeek.c - sceCdSeek: starts an asynchronous seek to a sector. */
#include "dw4/support/eekernel.h"
#include "dw4/sony/libcdvd.h"

int sceCdSeek(unsigned int lbn)
{
    int *send = _sceCd_ncmdsdata;

    if (sceCdNcmdDiskReady() == 6) {
        return 0;
    }
    if (_sceCd_ncmd_prechk(CD_PRECHK_SEEK) == 0) {
        return 0;
    }
    send[0] = lbn;
    sceSifWriteBackDCache(send, 4);
    sceCdCbfunc_num = SCECdFuncSeek;
    _sceCd_c_cb_sem = 1;
    if (sceSifCallRpc(&_sceCd_cd_ncmd, CD_NCMD_SEEK, SIF_RPCM_NOWAIT, send, 4, 0, 0,
                      _sceCd_cd_callback, (void *)&sceCdCbfunc_num) < 0) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    return 1;
}

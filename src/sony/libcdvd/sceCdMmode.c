/* sceCdMmode.c - sceCdMmode: selects the media (CD or DVD) the drive reads. */
#include "dw4/support/eekernel.h"
#include "dw4/sony/libcdvd.h"

static int rpc_mmode = 34;
static int outcnt_mmode = 4;
static int incnt_mmode = 4;

int sceCdMmode(int media)
{
    int *send = _sceCd_scmdsdata;
    int result;

    if (_sceCd_scmd_prechk(CD_PRECHK_MMODE) == 0) {
        return 0;
    }
    send[0] = media;
    sceSifWriteBackDCache(send, 4);
    if (sceSifCallRpc(&_sceCd_cd_scmd, rpc_mmode, 0, send, outcnt_mmode, _sceCd_scmdrdata, incnt_mmode, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    result = UNCACHED_WORD(_sceCd_scmdrdata);
    SignalSema(_sceCd_scmd_semid);
    return result;
}

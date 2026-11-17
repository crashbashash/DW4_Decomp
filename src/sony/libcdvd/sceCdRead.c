/* sceCdRead.c - sceCdRead: starts an asynchronous read from the disc into the caller's buffer. */
#include "dw4/support/eekernel.h"
#include "dw4/sony/libcdvd.h"

/* The N-command buffer as the read command lays it out. */
typedef struct {
    unsigned int lbn;
    unsigned int sectors;
    void *buffer;
    sceCdRMode mode;
    CdReadIntrData *intrData;
    int *curPos;
} CdReadCommand;

int sceCdRead(unsigned int lbn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
    CdReadCommand *cmd = (CdReadCommand *)_sceCd_ncmdsdata;
    int size;

    if (!(_sceCd_ee_read_mode & 1)) {
        if (sceCdNcmdDiskReady() == 6) {
            return 0;
        }
    }
    if (_sceCd_ncmd_prechk(CD_PRECHK_READ) == 0) {
        return 0;
    }
    cmd->lbn = lbn;
    cmd->sectors = sectors;
    cmd->buffer = buf;
    cmd->mode.trycount = mode->trycount;
    cmd->mode.spindlctrl = mode->spindlctrl;
    cmd->mode.datapattern = mode->datapattern;
    cmd->intrData = &_sceCd_rd_intr_data;
    cmd->curPos = _sceCd_Read_cur_pos;
    switch (mode->datapattern) {
    case SCECdSecS2048:
        size = sectors << 11;
        break;
    case SCECdSecS2328:
        size = sectors * 2328;
        break;
    case SCECdSecS2340:
        size = sectors * 2340;
        break;
    default:
        size = sectors << 11;
        break;
    }
    _sceCd_Read_cur_pos[0] = 0;
    if (!(_sceCd_ee_read_mode & 2)) {
        sceSifWriteBackDCache(buf, size);
    }
    sceSifWriteBackDCache(&_sceCd_rd_intr_data, sizeof(CdReadIntrData));
    sceSifWriteBackDCache(cmd, sizeof(CdReadCommand));
    sceSifWriteBackDCache(_sceCd_Read_cur_pos, 4);
    if (SCE_CD_debug > 0) {
        scePrintf("call cdread cmd\n");
    }
    sceCdCbfunc_num = SCECdFuncRead;
    _sceCd_c_cb_sem = 1;
    if (sceSifCallRpc(&_sceCd_cd_ncmd, CD_NCMD_READ, SIF_RPCM_NOWAIT, cmd, sizeof(CdReadCommand), 0, 0,
                      _sceCd_cd_read_intr, &_sceCd_rd_intr_data) < 0) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("cdread end\n");
    }
    return 1;
}

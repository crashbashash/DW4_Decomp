/* cdvd000.c - libcdvd's EE side: the client of cdvdman's RPC servers. Commands go out as RPCs on the
 * N-command (disc) and S-command (drive) channels, each guarded by a semaphore; the callback thread
 * reports command completion to the game. */
#include "dw4/support/eekernel.h"
#include "dw4/sony/libkernl.h"
#include "dw4/sony/libcdvd.h"
#include <string.h>

/* The search request the N-command server takes and the record it answers with. */
typedef struct _CdSearchBuffer {
    sceCdlFILE file;
    char name[256];
    struct _CdSearchBuffer *self;
    int layer;
} CdSearchBuffer;

/* the SIF command cdvdman sends when the console is powered off */
#define CD_CMD_POWER_OFF 0x80000012

static void _sceCd_cbLoop(void *arg);
static int PowerOffCB(void);

static char __ps2_libinfo__[16] = "PsIIlibcdvd 2800";
int SCE_CD_debug = 0;
static int cb_thid = 0;
static int scmd_sema_keep_cmd = 0;
static int ncmd_sema_keep_cmd = 0;
static volatile int cb_semid = -1;
static volatile int Init_seq = 0;
volatile int _sceCd_ncmd_semid = -1;
volatile int _sceCd_scmd_semid = -1;
volatile int _sceCd_rcmd_semid = -1;
volatile int _sceCd_c_cb_sem = 0;
volatile int _sceCd_ee_read_mode = 0;
static int _ncmd_bind = -1;
static int _icmd_bind = -1;
static int _sf_bind = -1;
static int _scmd_dr_bind = -1;
static int _scmd_bind = -1;
static int _it_bind = -1;

static CdCallback sceCdCbfunc;
static void *sceCdCb_Gp;
static CdPowerOffCallback sceCdPoffCbfunc;
static void *sceCdCbPoff_Gp;
static void *sceCdPoffCbdata;
static volatile int sceCdPoffCbfunc_num;
static int init_thid;
static struct ThreadParam init_thparam;
static struct ThreadParam cb_tp;
static CdSearchBuffer _sf_data __attribute__((aligned(64)));
static int sfrdata[16] __attribute__((aligned(64)));
static sceSifClientData cdrdsf;
static sceSifClientData cdit;
static sceSifClientData cddr;
static int _i_mode[4] __attribute__((aligned(16)));
static int _dr_mode;

CdCallback sceCdCallback(CdCallback func)
{
    CdCallback old;
    int enabled;

    if (sceCdSync(1)) {
        return 0;
    }
    enabled = DIntr();
    old = sceCdCbfunc;
    sceCdCbfunc = func;
    __asm__("sw $28,%0" : : "m"(sceCdCb_Gp));
    if (enabled) {
        EIntr();
    }
    return old;
}

void _sceCd_cd_callback(void *reason)
{
    sceCdCbfunc_num = *(int *)reason;
    sceCdCbfunc_number = sceCdCbfunc_num;
    if (sceCdCbfunc_num == CD_FUNC_EXIT) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
    } else {
        iSignalSema(_sceCd_ncmd_semid);
        if (cb_thid != 0 && sceCdCbfunc != 0) {
            iSignalSema(cb_semid);
        } else {
            _sceCd_c_cb_sem = 0;
        }
        sceCdCbfunc_num = 0;
    }
}

static void _sceCd_cbLoop(void *arg)
{
    void *gp;

    while (1) {
        WaitSema(cb_semid);
        if (sceCdCbfunc_num == -1) {
            _sceCd_c_cb_sem = 0;
            sceCdCbfunc_num = 0;
            cb_thid = 0;
            sceCdPoffCbfunc_num = 0;
            ExitDeleteThread();
        }
        if (SCE_CD_debug > 0) {
            scePrintf("sceCdCbfunc= %d sceCdCbfunc_num= %d\n", sceCdCbfunc, sceCdCbfunc_number);
        }
        if (sceCdCbfunc != 0 && sceCdCbfunc_number != 0) {
            /* the callback runs on the $gp sceCdCallback recorded */
            __asm__ volatile("move %0, $28\n\tlw $28, %1" : "=&r"(gp) : "m"(sceCdCb_Gp));
            sceCdCbfunc(sceCdCbfunc_number);
            __asm__("move $28, %0" : : "r"(gp));
        }
        _sceCd_c_cb_sem = 0;
    }
}

int sceCdInitEeCB(int cb_prio, void *stack_addr, int stack_size)
{
    int ret = 1;

    if (cb_thid == 0) {
        init_thid = GetThreadId();
        ReferThreadStatus(init_thid, &init_thparam);
        cb_tp.stackSize = stack_size;
        cb_tp.entry = _sceCd_cbLoop;
        cb_tp.stack = stack_addr;
        cb_tp.gpReg = 0;
        cb_tp.initPriority = cb_prio;
        cb_thid = CreateThread(&cb_tp);
        _StartThread(cb_thid, 0);
    } else {
        ChangeThreadPriority(cb_thid, cb_prio);
        ret = 0;
    }
    return ret;
}

void _sceCd_cd_read_intr(void *param)
{
    CdReadIntrData *data = UNCACHED(param);
    unsigned char *cached;
    unsigned char *uncached;
    int i;

    if (data->headSize > 0) {
        uncached = UNCACHED(data->headDest);
        cached = data->headDest;
        for (i = 0; i < data->headSize; i++) {
            cached[i] = uncached[i] = data->head[i];
        }
    }
    if (data->tailSize > 0) {
        uncached = UNCACHED(data->tailDest);
        cached = data->tailDest;
        for (i = 0; i < data->tailSize; i++) {
            cached[i] = uncached[i] = data->tail[i];
        }
    }
    _sceCd_cd_callback((void *)&sceCdCbfunc_num);
}

static void cmd_sem_init(void)
{
    struct SemaParam sema;

    if (_sceCd_ncmd_semid == -1 || _sceCd_scmd_semid == -1 || _sceCd_rcmd_semid == -1) {
        sema.option = 0;
        sema.initCount = 1;
        sema.maxCount = 1;
        _sceCd_ncmd_semid = CreateSema(&sema);
        _sceCd_scmd_semid = CreateSema(&sema);
        _sceCd_rcmd_semid = CreateSema(&sema);
        sema.initCount = 0;
        cb_semid = CreateSema(&sema);
        _sceCd_c_cb_sem = 0;
    }
}

static void cdvd_exit(void)
{
    int enabled;

    if (cb_thid != 0) {
        sceCdCbfunc_num = -1;
        SignalSema(cb_semid);
    }
    DeleteSema(_sceCd_ncmd_semid);
    DeleteSema(_sceCd_scmd_semid);
    DeleteSema(_sceCd_rcmd_semid);
    DeleteSema(cb_semid);
    enabled = DIntr();
    sceSifRemoveCmdHandler(CD_CMD_POWER_OFF);
    if (enabled) {
        EIntr();
    }
}

CdPowerOffCallback sceCdPOffCallback(CdPowerOffCallback func, void *data)
{
    CdPowerOffCallback old;
    int enabled;

    if (_icmd_bind < 0) {
        PowerOffCB();
    }
    enabled = DIntr();
    old = sceCdPoffCbfunc;
    sceCdPoffCbdata = data;
    sceCdPoffCbfunc = func;
    __asm__("sw $28,%0" : : "m"(sceCdCbPoff_Gp));
    if (enabled) {
        EIntr();
    }
    return old;
}

static void _sceCd_Poff_Intr(void *packet, void *arg)
{
    void *gp;

    if (sceCdPoffCbfunc != 0 && Init_seq == 0) {
        /* the callback runs on the $gp sceCdPOffCallback recorded */
        __asm__ volatile("move %0, $28\n\tlw $28, %1" : "=&r"(gp) : "m"(sceCdCbPoff_Gp));
        sceCdPoffCbfunc(sceCdPoffCbdata);
        __asm__("move $28, %0" : : "r"(gp));
    }
}

static int PowerOffCB(void)
{
    int enabled;

    Init_seq = 1;
    enabled = DIntr();
    sceSifAddCmdHandler(CD_CMD_POWER_OFF, _sceCd_Poff_Intr, 0);
    if (enabled) {
        EIntr();
    }
    Init_seq = 0;
    _icmd_bind = 1;
    return 1;
}

int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer)
{
    int i;
    int spin;
    int ret;

    cmd_sem_init();
    if (_sceCd_ncmd_semid != PollSema(_sceCd_ncmd_semid)) {
        return 0;
    }
    ncmd_sema_keep_cmd = 1;
    ReferThreadStatus(init_thid, &init_thparam);
    if (sceCdSync(1)) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (_sf_bind < 0) {
        while (1) {
            if (sceSifBindRpc(&cdrdsf, CD_SEARCH_SERVER, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err CdSearchFile\n");
                }
                spin = 0x100000;
                while (spin--);
                continue;
            }
            if (cdrdsf.serve != 0) {
                _sf_bind = 0;
                break;
            }
            spin = 0x100000;
            while (spin--);
        }
    }
    for (i = 0; i < 256 && (_sf_data.name[i] = name[i]) != 0; i++);
    if (i == 256) {
        _sf_data.name[255] = 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("ee call cmd search %s\n", _sf_data.name);
    }
    _sf_data.layer = layer;
    _sf_data.self = &_sf_data;
    sceSifWriteBackDCache(&_sf_data, sizeof(CdSearchBuffer));
    if (sceSifCallRpc(&cdrdsf, CD_NCMD_SEARCH, 0, &_sf_data, sizeof(CdSearchBuffer), sfrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    memcpy(fp, UNCACHED(&_sf_data), sizeof(sceCdlFILE));
    if (SCE_CD_debug > 0) {
        scePrintf("search name %s\n", fp->name);
    }
    if (SCE_CD_debug > 0) {
        scePrintf("search size %d\n", fp->size);
    }
    if (SCE_CD_debug > 0) {
        scePrintf("search loc lbn %d\n", fp->lsn);
    }
    ret = UNCACHED_WORD(sfrdata);
    SignalSema(_sceCd_ncmd_semid);
    return ret;
}

int sceCdSearchFile(sceCdlFILE *fp, const char *name)
{
    return sceCdLayerSearchFile(fp, name, 0);
}

int _sceCd_ncmd_prechk(int cmd)
{
    int spin;

    cmd_sem_init();
    if (_sceCd_ncmd_semid != PollSema(_sceCd_ncmd_semid)) {
        if (SCE_CD_debug > 0) {
            scePrintf("Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", cmd, ncmd_sema_keep_cmd);
        }
        return 0;
    }
    ncmd_sema_keep_cmd = cmd;
    ReferThreadStatus(init_thid, &init_thparam);
    if (sceCdSync(1)) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (_ncmd_bind < 0) {
        while (1) {
            if (sceSifBindRpc(&_sceCd_cd_ncmd, CD_NCMD_SERVER, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err N CMD\n");
                }
                spin = 0x100000;
                while (spin--);
                continue;
            }
            if (_sceCd_cd_ncmd.serve != 0) {
                break;
            }
            spin = 0x100000;
            while (spin--);
        }
        _ncmd_bind = 0;
    }
    return 1;
}

int sceCdNcmdDiskReady(void)
{
    int ret;

    if (_sceCd_ncmd_prechk(CD_PRECHK_NCMD_DISK_READY) == 0) {
        return 0;
    }
    if (sceSifCallRpc(&_sceCd_cd_ncmd, CD_NCMD_DISK_READY, 0, 0, 0, _sceCd_ncmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    ret = UNCACHED_WORD(_sceCd_ncmdrdata);
    SignalSema(_sceCd_ncmd_semid);
    return ret;
}

int sceCdSync(int mode)
{
    if (mode == 0) {
        if (SCE_CD_debug > 0) {
            scePrintf("N cmd wait\n");
        }
        while (_sceCd_c_cb_sem || sceSifCheckStatRpc(&_sceCd_cd_ncmd.rpcd)) {
            DelayThread(4000);
        }
        return 0;
    }
    if (_sceCd_c_cb_sem || sceSifCheckStatRpc(&_sceCd_cd_ncmd.rpcd)) {
        return 1;
    }
    return 0;
}

int sceCdSyncS(int mode)
{
    if (mode == 0) {
        if (SCE_CD_debug > 0) {
            scePrintf("S cmd wait\n");
        }
        while (sceSifCheckStatRpc(&_sceCd_cd_scmd.rpcd)) {
            DelayThread(4000);
        }
        return 0;
    }
    return sceSifCheckStatRpc(&_sceCd_cd_scmd.rpcd);
}

int _sceCd_scmd_prechk(int cmd)
{
    int spin;

    cmd_sem_init();
    if (_sceCd_scmd_semid != PollSema(_sceCd_scmd_semid)) {
        if (SCE_CD_debug > 0) {
            scePrintf("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", cmd, scmd_sema_keep_cmd);
        }
        return 0;
    }
    scmd_sema_keep_cmd = cmd;
    ReferThreadStatus(init_thid, &init_thparam);
    if (sceCdSyncS(1)) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (_scmd_bind < 0) {
        while (1) {
            if (sceSifBindRpc(&_sceCd_cd_scmd, CD_SCMD_SERVER, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err S cmd\n");
                }
                spin = 0x100000;
                while (spin--);
                continue;
            }
            if (_sceCd_cd_scmd.serve != 0) {
                break;
            }
            spin = 0x100000;
            while (spin--);
        }
        _scmd_bind = 0;
    }
    return 1;
}

/* Hands out a channel's internals: 0x800N the N-command channel's, 0x801N the S-command channel's
 * semaphore (1), send buffer (2), receive buffer (3) and client (4). */
int _sceCdSC(int cmd, int *result)
{
    *result = cmd == 0x8001 ? _sceCd_ncmd_semid
            : cmd == 0x8003 ? (int)_sceCd_ncmdrdata
            : cmd == 0x8002 ? (int)_sceCd_ncmdsdata
            : cmd == 0x8004 ? (int)&_sceCd_cd_ncmd
            : cmd == 0x8011 ? _sceCd_scmd_semid
            : cmd == 0x8013 ? (int)_sceCd_scmdrdata
            : cmd == 0x8012 ? (int)_sceCd_scmdsdata
            : cmd == 0x8014 ? (int)&_sceCd_cd_scmd
            : 0;
    return 1;
}

int sceCdInit(int init_mode)
{
    static int c_cnt = 0;
    int spin;
    int ret;
    int bind;
    int version1;
    int version2;
    int status;

    if (sceCdSyncS(1)) {
        return 0;
    }
    sceSifInitRpc(0);
    init_thid = GetThreadId();
    /* matching construct: order search (720 bind orders x 6 placements) — order of the six bind resets */
    _sf_bind = -1;
    _ncmd_bind = -1;
    _scmd_bind = -1;
    _scmd_dr_bind = -1;
    _it_bind = -1;
    _icmd_bind = -1;
    Init_seq = 1;
    _sceCd_ee_read_mode = 0;
    c_cnt++;
    while (1) {
        bind = sceSifBindRpc(&cdit, CD_INIT_SERVER, 0);
        if (bind < 0) {
            if (SCE_CD_debug > 0) {
                scePrintf("Libcdvd bind err %d CD_Init %d\n", bind, c_cnt);
            }
            spin = 0x100000;
            while (spin--);
            continue;
        }
        if (cdit.serve != 0) {
            _i_mode[0] = init_mode;
            _it_bind = 0;
            break;
        }
        spin = 0x100000;
        while (spin--);
    }
    sceSifWriteBackDCache(_i_mode, 4);
    if (sceSifCallRpc(&cdit, 0, 0, _i_mode, 4, _sceCd_scmdrdata, 16, 0, 0) < 0) {
        Init_seq = 0;
        return 0;
    }
    version1 = UNCACHED_WORD(&_sceCd_scmdrdata[1]);
    version2 = UNCACHED_WORD(&_sceCd_scmdrdata[2]);
    status = UNCACHED_WORD(&_sceCd_scmdrdata[3]);
    ret = 1;
    if (status != 255) {
        if (status == 254) {
            SCE_CD_debug = 1;
        } else if (version1 / 256 < 2 || version2 / 256 < 2) {
            ret = 2;
        }
    }
    Init_seq = 0;
    switch (init_mode) {
    case SCECdEXIT:
        if (SCE_CD_debug > 0) {
            scePrintf("Libcdvd Exit\n");
        }
        cdvd_exit();
        _sceCd_ncmd_semid = -1;
        _sceCd_scmd_semid = -1;
        cb_semid = -1;
        break;
    case SCECdINIT:
    case SCECdINoD:
    default:
        cmd_sem_init();
        PowerOffCB();
        break;
    }
    return ret;
}

int sceCdDiskReady_old(int mode)
{
    int spin;
    int ret;

    if (SCE_CD_debug > 0) {
        scePrintf("OLD DiskReady Call\n");
    }
    cmd_sem_init();
    if (_sceCd_scmd_semid != PollSema(_sceCd_scmd_semid)) {
        return 6;
    }
    if (sceCdSyncS(1)) {
        SignalSema(_sceCd_scmd_semid);
        return mode != 8 ? 6 : -1;
    }
    sceSifInitRpc(0);
    if (_scmd_dr_bind < 0) {
        while (1) {
            if (sceSifBindRpc(&cddr, CD_DISK_READY_OLD_SERVER, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err CdDiskReady\n");
                }
                spin = 0x100000;
                while (spin--);
                continue;
            }
            if (cddr.serve != 0) {
                _scmd_dr_bind = 0;
                break;
            }
            spin = 0x100000;
            while (spin--);
        }
    }
    _dr_mode = mode;
    sceSifWriteBackDCache(&_dr_mode, 4);
    if (sceSifCallRpc(&cddr, 0, 0, &_dr_mode, 4, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return mode != 8 ? 6 : -1;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("DiskReady ended\n");
    }
    ret = UNCACHED_WORD(_sceCd_scmdrdata);
    SignalSema(_sceCd_scmd_semid);
    return ret;
}

/* Tries the newer disk-ready server for 17 binds, then falls back to the old one. */
int sceCdDiskReady(int mode)
{
    int tries;
    int spin;
    int ret;

    if (SCE_CD_debug > 0) {
        scePrintf("NEW DiskReady Call\n");
    }
    cmd_sem_init();
    if (_sceCd_rcmd_semid != PollSema(_sceCd_rcmd_semid)) {
        return mode != 8 ? 6 : -1;
    }
    sceSifInitRpc(0);
    tries = 0;
    if (_scmd_dr_bind < 0) {
        while (1) {
            if (sceSifBindRpc(&cddr, CD_DISK_READY_SERVER, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err CdDiskReady\n");
                }
                spin = 0x100000;
                while (spin--);
                continue;
            }
            if (cddr.serve != 0) {
                _scmd_dr_bind = 0;
                break;
            }
            if (tries >= 17) {
                SignalSema(_sceCd_rcmd_semid);
                return sceCdDiskReady_old(mode);
            }
            spin = 0x100000;
            while (spin--);
            tries++;
        }
    }
    _dr_mode = mode;
    sceSifWriteBackDCache(&_dr_mode, 4);
    if (sceSifCallRpc(&cddr, 0, 0, &_dr_mode, 4, _sceCd_rcmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_rcmd_semid);
        return mode != 8 ? 6 : -1;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("DiskReady ended\n");
    }
    ret = UNCACHED_WORD(_sceCd_rcmdrdata);
    SignalSema(_sceCd_rcmd_semid);
    return ret;
}

volatile int sceCdCbfunc_num = 0;
volatile int sceCdCbfunc_number = 0;
int _sceCd_ncmdrdata[24] __attribute__((aligned(64))) = {0};
int _sceCd_ncmdsdata[1024] __attribute__((aligned(64))) = {0};
CdReadIntrData _sceCd_rd_intr_data __attribute__((aligned(64))) = {0};
int _sceCd_Read_cur_pos[4] __attribute__((aligned(64))) = {0};
sceSifClientData _sceCd_cd_ncmd = {0};
int _sceCd_scmdrdata[264] __attribute__((aligned(64))) = {0};
int _sceCd_scmdsdata[258] __attribute__((aligned(64))) = {0};
int _sceCd_rcmdrdata[64] __attribute__((aligned(64))) = {0};
sceSifClientData _sceCd_cd_scmd = {0};

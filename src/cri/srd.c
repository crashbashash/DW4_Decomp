#include <string.h>
#include "dw4/libkernl.h"
#include "dw4/sony/libcdvd.h"
#include "dw4/sony/sifdev.h"
#include "dw4/cri/svm.h"
#include "dw4/cri/cri_srd.h"

struct SrdObj {
    signed char used;        /* 0x00 */
    signed char devtype;     /* 0x01: 1 DVD, 2 host */
    signed char stat;        /* 0x02 */
    signed char mode;        /* 0x03 */
    int abort_request;       /* 0x04 */
    int lsn;                 /* 0x08 */
    int sectors;             /* 0x0c */
    void *buf;               /* 0x10 */
    sceCdRMode rmode;        /* 0x14 */
    void *host_buf;          /* 0x18 */
    int pad1c;
    long long host_size;     /* 0x20 */
    long long host_sector;   /* 0x28 */
    int fd;                  /* 0x30 */
    int error;               /* 0x34 */
};

extern SrdObj srd_obj;
extern char *volatile srd_build;
extern int srd_enter_fg;
extern volatile int srd_dvd_exec_locked;
extern volatile int srd_hst_exec_locked;
extern volatile int DAT_004a92d0;
extern volatile int DAT_004a92d4;
extern volatile unsigned int DAT_004a92d8;
extern volatile int DAT_004a92dc;
extern volatile int DAT_004a92e0;
extern volatile int DAT_004a92e4;
extern volatile int DAT_004a92e8;
extern int srd_destroy_cnt;
extern volatile int srd_history_pre;
extern volatile int srd_history;
extern int srd_host_mode;
extern int srd_host_lock;

extern char DAT_004efbc0[];
extern char DAT_004efc00[];
extern char DAT_004efc20[];
extern char DAT_004efc40[];
extern char DAT_004efc60[];
extern char DAT_004efc78[];
extern char D_004efca8[];
extern char SRD_SRD_WaitForExecServer_timeout_10sec[];
extern char SRD_SRD_Info[];
extern char srd_enter_fg_d[];
extern char srd_debug_geterror_d[];
extern char srd_obj_stat_d[];
extern char srd_obj_devtype_DVD[];
extern char srd_obj_devtype_HOST[];
extern char Read_Status_DVD_2_HST_1_d[];
extern char DAT_004efe28[];
extern const char SRD_Enable_HostLock[];
extern char SRD_sceLseek64_error[];
extern char SRD_sceLseek_error[];
extern char DAT_004efea0[];
extern char DAT_004efec0[];
extern char DAT_004efee0[];
extern char DAT_004eff00[];


void srd_sw_lock(void);
void srd_sw_unlock(void);

void srd_reset_obj(void)
{
    srd_build;
    memset(&srd_obj, 0, sizeof(srd_obj));
}

SrdObj *SRD_Create(void)
{
    SrdObj *srd = 0;

    SVM_LockVar();
    if (srd_obj.used == 0) {
        srd_reset_obj();
        srd_obj.used = 1;
        srd_obj.stat = 0;
        srd_obj.mode = -1;
        srd_obj.abort_request = 0;
        DAT_004a92e8++;
        srd = &srd_obj;
    }
    SVM_UnlockVar();
    return srd;
}

void SRD_Destroy(SrdObj *h)
{
    SVM_LockVar();
    if (h != &srd_obj) {
        scePrintf(DAT_004efbc0, h, &srd_obj);
    } else {
        if (h->stat != 0 && h->stat != 3 && h->stat != 9) {
            scePrintf(DAT_004efc00);
        }
        srd_reset_obj();
        srd_obj.used = 0;
        srd_destroy_cnt++;
    }
    SVM_UnlockVar();
}

int SRD_ReqRdDvd(SrdObj *srd, int lsn, int sectors, void *buf, sceCdRMode *mode)
{
    int ret;
    int busy;

    ret = 0;
    SRD_SetHistory(0x1200);
    busy = sceCdSync(1);
    SRD_SetHistory(0x1201);
    if (busy == 1) {
        return 0;
    }
    SVM_LockVar();
    if (srd->stat == 0 || srd->stat == 3 || srd->stat == 9) {
        srd->devtype = 1;
        srd->stat = 1;
        srd->lsn = lsn;
        srd->rmode = *mode;
        srd->sectors = sectors;
        srd->buf = buf;
        srd->abort_request = 0;
        ret = 1;
    }
    SVM_UnlockVar();
    return ret;
}

int SRD_ReqRdHst(SrdObj *srd, int fd, long long sector, long long size, void *buf)
{
    int queued = 0;

    SVM_LockVar();
    /* matching construct: permuter — the request store follows the state bytes (register allocation) */
    if (srd->stat == 0 || srd->stat == 3 || srd->stat == 9) {
        srd->devtype = 2;
        srd->stat = 1;
        queued = 1;
        srd->fd = fd;
        srd->host_buf = buf;
        srd->host_size = size;
        srd->host_sector = sector;
        srd->abort_request = 0;
    }
    SVM_UnlockVar();
    return queued;
}

char SRD_GetStat(SrdObj *srd)
{
    return srd->stat;
}

void srd_wait(void)
{
    int i;

    for (i = 0x3FFF; i > -1; i -= 32) {
    }
}

void srd_wait_dvd(SrdObj *srd)
{
    SRD_SetHistory(0x1300);
    sceCdSync(0);
    SRD_SetHistory(0x1301);
}

void srd_wait_hst(SrdObj *f)
{
    int busy;
    int ret;
    int count;

    busy = 1;
    count = 0;
    for (;;) {
        if (busy != 1) {
            return;
        }
        SRD_SetHistory(0x1100);
        ret = SRD_SceIoctl(f->fd, 1, &busy);
        SRD_SetHistory(0x1101);
        if (ret < 0) {
            f->stat = 9;
            f->error = ret;
            return;
        }
        srd_wait();
        if (++count > 0x9000) {
            scePrintf(DAT_004efc20);
            return;
        }
    }
}

void FUN_00271a68(SrdObj *h)
{
    short i;
    int stat;
    SrdObj *srd;

    for (i = 0; i < 1000; i++) {
        SVM_Lock();
        if (srd_enter_fg == 1) {
            SVM_Unlock();
            srd_wait();
            continue;
        }
        srd_enter_fg = 1;
        SVM_Unlock();
        break;
    }
    stat = h->stat;
    if (stat == 2) {
        srd = &srd_obj;
        if (srd->devtype == 1) {
            srd_wait_dvd(h);
        }
        if (srd->devtype == stat) {
            srd_wait_hst(h);
        }
        if (h->stat != 9) {
            h->stat = 3;
            DAT_004a92e4++;
        }
    }
    srd_enter_fg = 0;
}

void FUN_00271b78(void)
{
    FUN_00271a68(&srd_obj);
}

void SRD_Break(SrdObj *object)
{
    SVM_LockVar();
    if (object == 0) {
        scePrintf(DAT_004efc40);
    } else if (object->abort_request == 1) {
        scePrintf(DAT_004efc60);
    } else {
        object->abort_request = 1;
    }
    SVM_UnlockVar();
}

int srd_check_dvd_error(SrdObj *h)
{
    int err;

    if (DAT_004a92d4 == 0) {
        return 0;
    }
    if (h->stat != 2) {
        return 0;
    }
    DAT_004a92dc = 1;
    if (DAT_004a92d0 == 1) {
        SVM_LockDev();
        SRD_SetHistory(0x1400);
        err = sceCdGetError();
        SRD_SetHistory(0x1401);
        SVM_UnlockDev();
    } else {
        SRD_SetHistory(0x1500);
        err = sceCdGetError();
        SRD_SetHistory(0x1501);
    }
    DAT_004a92dc = 0;
    if (err != 0 && err != -1) {
        if (err != 32) {
            h->error = err;
            scePrintf(DAT_004efc78, err);
            return 1;
        }
    }
    return 0;
}

void FUN_00271d10(unsigned char value)
{
    srd_spindlctrl = value;
}

void FUN_00271d20(int value)
{
    srd_spindlctrl_sw = value;
}

unsigned char FUN_00271d30(void)
{
    return srd_spindlctrl;
}

int FUN_00271d40(void)
{
    return srd_spindlctrl_sw;
}

void srd_exec_dvd(SrdObj *srd)
{
    int busy;
    int result;

    if (srd->abort_request == 1) {
        switch (srd->stat) {
        case 2:
            SRD_SetHistory(0x1600);
            busy = sceCdBreak();
            SRD_SetHistory(0x1601);
            if (busy == 0)
                scePrintf(D_004efca8, DAT_004a92dc);
            SRD_SetHistory(0x1700);
            sceCdSync(0);
            SRD_SetHistory(0x1701);
            srd->stat = 0;
            DAT_004a92e4++;
            break;
        case 1:
        case 3:
        case 9:
            srd->stat = 0;
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        }
        srd->abort_request = 0;
    }
    if (srd->stat == 1) {
        SRD_SetHistory(0x1800);
        if (srd_spindlctrl_sw == 1)
            srd->rmode.spindlctrl = srd_spindlctrl;
        busy = sceCdRead(srd->lsn, srd->sectors, srd->buf, &srd->rmode);
        SRD_SetHistory(0x1801);
        if (busy == 1) {
            DAT_004a92e0++;
            srd->stat = 2;
        } else {
            srd->stat = 9;
            srd->error = -1;
        }
    }
    if (srd->stat == 2) {
        SRD_SetHistory(0x1900);
        busy = sceCdSync(1);
        SRD_SetHistory(0x1901);
        result = srd_check_dvd_error(srd);
        if (busy == 0) {
            srd->stat = (result == 1) ? 9 : 3;
            DAT_004a92e4++;
        }
    }
}

void srd_exec_hst(SrdObj *srd)
{
    long ret;
    int busy;

    if (srd->abort_request == 1) {
        switch (srd->stat) {
        case 2:
            srd_wait_hst(srd);
            srd->stat = 0;
            DAT_004a92e4++;
            /* fall through */
        case 1:
        case 3:
        case 9:
            srd->stat = 0;
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        }
        srd->abort_request = 0;
    }
    if (srd->stat == 1) {
        SRD_SetHistory(0x2000);
        ret = SRD_SceLseek(srd->fd, srd->host_sector << 11, 0);
        SRD_SetHistory(0x2001);
        if (ret < 0) {
            srd->stat = 9;
            srd->error = (int) ret;
        }
        SRD_SetHistory(0x2100);
        ret = SRD_SceRead(srd->fd, srd->host_buf, srd->host_size);
        SRD_SetHistory(0x2101);
        if (ret >= 0) {
            srd->stat = 2;
            DAT_004a92e0++;
        } else {
            srd->stat = 9;
            srd->error = (int) ret;
        }
    }
    if (srd->stat == 2) {
        SRD_SetHistory(0x2200);
        if (SRD_SceIoctl(srd->fd, 1, &busy) < 0) {
            SRD_SetHistory(0x2201);
            srd->stat = 9;
            srd->error = -1;
        } else {
            SRD_SetHistory(0x2202);
            if (busy == 0) {
                srd->stat = 3;
                DAT_004a92e4++;
            }
        }
    }
}

int FUN_00272108(void)
{
    return srd_enter_fg;
}

void SRD_ExecServer(void)
{
    SrdObj *srd = &srd_obj;

    if (SVM_TestAndSet(&srd_enter_fg) == 0) {
        return;
    }
    if (srd->devtype == 1) {
        if (srd_dvd_exec_locked == 1) {
            SVM_LockDev();
        }
        srd_exec_dvd(srd);
        if (srd_dvd_exec_locked == 1) {
            SVM_UnlockDev();
        }
    }
    if (srd->devtype == 2) {
        if (srd_hst_exec_locked == 1) {
            SVM_LockDev();
        }
        srd_exec_hst(srd);
        if (srd_hst_exec_locked == 1) {
            SVM_UnlockDev();
        }
    }
    srd_enter_fg = 0;
}

signed char SRD_GetDevTypeNow(void)
{
    return srd_obj.devtype;
}

int SRD_GetErrCode(void)
{
    return srd_obj.error;
}

void SRD_WaitForExecServer(void)
{
    DAT_004a92d8 = 0;
    while (srd_enter_fg == 1) {
        DAT_004a92d8++;
        if (DAT_004a92d8 > 0x19640000) {
            scePrintf(SRD_SRD_WaitForExecServer_timeout_10sec);
            break;
        }
    }
}

void SRD_LockedForDvdExec(int value)
{
    SRD_WaitForExecServer();
    srd_dvd_exec_locked = (signed char)value;
}

void SRD_LockedForHstExec(int value)
{
    SRD_WaitForExecServer();
    srd_hst_exec_locked = (char)value;
}

void SRD_LockedForGetError(int value)
{
    SRD_WaitForExecServer();
    DAT_004a92d0 = (char)value;
}

void SRD_CallForGetError(int value)
{
    SRD_WaitForExecServer();
    DAT_004a92d4 = (char)value;
}

void SRD_SetError(void)
{
    srd_obj.stat = 9;
}

int SRD_GetReadStatusDvd(void)
{
    int busy;

    SRD_SetHistory(0x2300);
    busy = sceCdSync(1);
    SRD_SetHistory(0x2301);
    return busy;
}

int SRD_GetReadStatusHost(void)
{
    int status;

    if (srd_obj.stat == 2) {
        SVM_Lock();
        SRD_SetHistory(0x2400);
        if (SRD_SceIoctl(srd_obj.fd, 1, &status) < 0) {
            SRD_SetHistory(0x2401);
        } else {
            SRD_SetHistory(0x2402);
            if (status != 0) {
                SVM_Unlock();
                return 1;
            }
        }
        SVM_Unlock();
    }
    return 0;
}

int SRD_GetReadStatus(void)
{
    if (srd_obj.devtype == 1) {
        return SRD_GetReadStatusDvd() * 2;
    }
    if (srd_obj.devtype == 2) {
        return SRD_GetReadStatusHost();
    }
    return 0;
}

int SRD_DebugPrint(void)
{
    scePrintf(SRD_SRD_Info);
    scePrintf(srd_enter_fg_d, srd_enter_fg);
    scePrintf(srd_debug_geterror_d, DAT_004a92dc);
    scePrintf(srd_obj_stat_d, srd_obj.stat);
    if (srd_obj.devtype == 1) {
        scePrintf(srd_obj_devtype_DVD);
    }
    if (srd_obj.devtype == 2) {
        scePrintf(srd_obj_devtype_HOST);
    }
    scePrintf(Read_Status_DVD_2_HST_1_d, SRD_GetReadStatus());
    return 0;
}

int SRD_GetReadEndCount(void)
{
    return DAT_004a92e4;
}

int SRD_GetReadBeginCount(void)
{
    return DAT_004a92e0;
}

void SRD_SetHistory(int value)
{
    srd_history_pre = srd_history;
    srd_history = value;
}

int SRD_GetHistory(void)
{
    return srd_history;
}

void FUN_002725d0(int mode)
{
    srd_host_mode = mode;
    if (mode == 1) {
        scePrintf(DAT_004efe28);
    }
}

int FUN_00272610(void)
{
    return srd_host_mode;
}

void FUN_00272620(int value)
{
    srd_hst_exec_locked = (char)value;
    srd_host_lock = srd_hst_exec_locked;
    if (value == 1) {
        scePrintf(SRD_Enable_HostLock);
    }
}

int FUN_00272678(void)
{
    return srd_host_lock;
}

void srd_sw_lock(void)
{
    if (srd_host_lock == 1) {
        SVM_LockDev();
    }
}

void srd_sw_unlock(void)
{
    if (srd_host_lock == 1) {
        SVM_UnlockDev();
    }
}

int FUN_002726f8(int lsn)
{
    int ok;
    int err;
    int ret;

    ret = SVM_TestAndSet(&srd_enter_fg);
    err = 0;
    if (ret != 0) {
        SRD_SetHistory(0x9600);
        ok = sceCdSeek(lsn);
        SRD_SetHistory(0x9601);
        if (ok == 0) {
            err = sceCdGetError();
        }
        srd_enter_fg = 0;
        ret = err;
    }
    return ret;
}

/* Seek on a host file: the 64-bit seek when the host mode word is 1, else the 32-bit seek, whose int
   result widens into the long. */
long long SRD_SceLseek(int fd, long long offset, int whence)
{
    long long ret;

    srd_sw_lock();
    if (srd_host_mode == 1) {
        ret = sceLseek64(fd, offset, whence);
        if (ret < 0) {
            scePrintf(SRD_sceLseek64_error, ret);
        }
    } else {
        ret = sceLseek(fd, offset, whence);
        if (ret < 0) {
            scePrintf(SRD_sceLseek_error, ret);
        }
    }
    srd_sw_unlock();
    return ret;
}

int SRD_SceIoctl(int fd, int cmd, int *result)
{
    int ret;

    srd_sw_lock();
    ret = sceIoctl(fd, cmd, result);
    if (ret < 0) {
        scePrintf(DAT_004efea0, ret);
    }
    srd_sw_unlock();
    return ret;
}

int SRD_SceOpen(const char *name, int flags)
{
    int ret;

    srd_sw_lock();
    ret = sceOpen(name, flags);
    if (ret < 0) {
        scePrintf(DAT_004efec0, ret);
    }
    srd_sw_unlock();
    return ret;
}

int SRD_SceClose(int fd)
{
    int ret;

    srd_sw_lock();
    ret = sceClose(fd);
    if (ret < 0) {
        scePrintf(DAT_004efee0, ret);
    }
    srd_sw_unlock();
    return ret;
}

int SRD_SceRead(int fd, void *buf, int size)
{
    int ret;

    srd_sw_lock();
    ret = sceRead(fd, buf, size);
    if (ret < 0) {
        scePrintf(DAT_004eff00, ret);
    }
    srd_sw_unlock();
    return ret;
}

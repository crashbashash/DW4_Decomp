typedef struct CdReadMode {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdReadMode;

typedef struct SrdObj {
    signed char used;        /* 0x00 */
    signed char devtype;     /* 0x01: 1 DVD, 2 host */
    signed char stat;        /* 0x02 */
    signed char mode;        /* 0x03 */
    int abort_request;       /* 0x04 */
    int lsn;                 /* 0x08 */
    int sectors;             /* 0x0c */
    void *buf;               /* 0x10 */
    CdReadMode rmode;        /* 0x14 */
    void *host_buf;          /* 0x18 */
    int pad1c;
    long host_size;          /* 0x20 */
    long host_sector;        /* 0x28 */
    int fd;                  /* 0x30 */
    int error;               /* 0x34 */
} SrdObj;

extern SrdObj DAT_004a9288;
extern char *volatile DAT_004a92c0;
extern int DAT_004a92c4;
extern volatile int DAT_004a92c8;
extern volatile int DAT_004a92cc;
extern volatile int DAT_004a92d0;
extern volatile int DAT_004a92d4;
extern volatile unsigned int DAT_004a92d8;
extern volatile int DAT_004a92dc;
extern volatile int DAT_004a92e0;
extern volatile int DAT_004a92e4;
extern volatile int DAT_004a92e8;
extern int DAT_004a92ec;
extern volatile int DAT_004a92f0;
extern volatile int DAT_004a92f4;
extern int srd_host_mode;
extern int DAT_004a92fc;
extern int srd_spindlctrl_sw;
extern unsigned char srd_spindlctrl;

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

void *memset(void *dst, int value, unsigned int size);
void scePrintf(const char *format, ...);
int sceCdSync(int mode);
int sceCdRead(int lsn, int sectors, void *buf, void *mode);
int sceCdBreak(void);
int sceCdSeek(int lsn);
int sceCdGetError(void);
int sceIoctl(int fd, int cmd, void *arg);
int sceOpen(int name, int flags);
int sceClose(int fd);
int sceRead(int fd, void *buf, int size);
long sceLseek64(int fd, long offset, int whence);
int sceLseek(int fd, int offset, int whence);
void SVM_Lock(void);
void SVM_Unlock(void);
void SVM_LockVar(void);
void SVM_UnlockVar(void);
void SVM_LockDev(void);
void SVM_UnlockDev(void);
int SVM_TestAndSet(int *lock);

void FUN_002725a0(int value);
void srd_Lock(void);
void srd_Unlock(void);
long SRD_Lseek(int fd, long offset, int whence);
int FUN_00272838(int fd, int cmd, int *result);
int FUN_00272970(int fd, void *buf, int size);

void FUN_00271640(void)
{
    DAT_004a92c0;
    memset(&DAT_004a9288, 0, sizeof(DAT_004a9288));
}

SrdObj *FUN_00271670(void)
{
    SrdObj *srd = 0;

    SVM_LockVar();
    if (DAT_004a9288.used == 0) {
        FUN_00271640();
        DAT_004a9288.used = 1;
        DAT_004a9288.mode = -1;
        DAT_004a9288.stat = 0;
        DAT_004a92e8++;
        DAT_004a9288.abort_request = 0;
        srd = &DAT_004a9288;
    }
    SVM_UnlockVar();
    return srd;
}

void FUN_002716f8(SrdObj *h)
{
    SVM_LockVar();
    if (h != &DAT_004a9288) {
        scePrintf(DAT_004efbc0, h, &DAT_004a9288);
    } else {
        if (h->stat != 0 && h->stat != 3 && h->stat != 9) {
            scePrintf(DAT_004efc00);
        }
        FUN_00271640();
        DAT_004a9288.used = 0;
        DAT_004a92ec++;
    }
    SVM_UnlockVar();
}

int FUN_00271798(SrdObj *srd, int lsn, int sectors, void *buf, CdReadMode *mode)
{
    int ret;
    int busy;

    ret = 0;
    FUN_002725a0(0x1200);
    busy = sceCdSync(1);
    FUN_002725a0(0x1201);
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

int FUN_00271888(SrdObj *srd, int fd, long sector, long size, void *buf)
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

char FUN_00271938(SrdObj *srd)
{
    return srd->stat;
}

void FUN_00271940(void)
{
    int i;

    for (i = 0x3FFF; i > -1; i -= 32) {
    }
}

void FUN_00271970(SrdObj *srd)
{
    FUN_002725a0(0x1300);
    sceCdSync(0);
    FUN_002725a0(0x1301);
}

void FUN_00271998(SrdObj *f)
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
        FUN_002725a0(0x1100);
        ret = FUN_00272838(f->fd, 1, &busy);
        FUN_002725a0(0x1101);
        if (ret < 0) {
            f->stat = 9;
            f->error = ret;
            return;
        }
        FUN_00271940();
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
        if (DAT_004a92c4 == 1) {
            SVM_Unlock();
            FUN_00271940();
            continue;
        }
        DAT_004a92c4 = 1;
        SVM_Unlock();
        break;
    }
    stat = h->stat;
    if (stat == 2) {
        srd = &DAT_004a9288;
        if (srd->devtype == 1) {
            FUN_00271970(h);
        }
        if (srd->devtype == stat) {
            FUN_00271998(h);
        }
        if (h->stat != 9) {
            h->stat = 3;
            DAT_004a92e4++;
        }
    }
    DAT_004a92c4 = 0;
}

void FUN_00271b78(void)
{
    FUN_00271a68(&DAT_004a9288);
}

void FUN_00271b98(SrdObj *object)
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

int FUN_00271c00(SrdObj *h)
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
        FUN_002725a0(0x1400);
        err = sceCdGetError();
        FUN_002725a0(0x1401);
        SVM_UnlockDev();
    } else {
        FUN_002725a0(0x1500);
        err = sceCdGetError();
        FUN_002725a0(0x1501);
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

void FUN_00271d50(SrdObj *srd)
{
    int busy;
    int result;

    if (srd->abort_request == 1) {
        switch (srd->stat) {
        case 2:
            FUN_002725a0(0x1600);
            busy = sceCdBreak();
            FUN_002725a0(0x1601);
            if (busy == 0)
                scePrintf(D_004efca8, DAT_004a92dc);
            FUN_002725a0(0x1700);
            sceCdSync(0);
            FUN_002725a0(0x1701);
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
        FUN_002725a0(0x1800);
        if (srd_spindlctrl_sw == 1)
            srd->rmode.spindlctrl = srd_spindlctrl;
        busy = sceCdRead(srd->lsn, srd->sectors, srd->buf, &srd->rmode);
        FUN_002725a0(0x1801);
        if (busy == 1) {
            DAT_004a92e0++;
            srd->stat = 2;
        } else {
            srd->stat = 9;
            srd->error = -1;
        }
    }
    if (srd->stat == 2) {
        FUN_002725a0(0x1900);
        busy = sceCdSync(1);
        FUN_002725a0(0x1901);
        result = FUN_00271c00(srd);
        if (busy == 0) {
            srd->stat = (result == 1) ? 9 : 3;
            DAT_004a92e4++;
        }
    }
}

void FUN_00271f38(SrdObj *srd)
{
    long ret;
    int busy;

    if (srd->abort_request == 1) {
        switch (srd->stat) {
        case 2:
            FUN_00271998(srd);
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
        FUN_002725a0(0x2000);
        ret = SRD_Lseek(srd->fd, srd->host_sector << 11, 0);
        FUN_002725a0(0x2001);
        if (ret < 0) {
            srd->stat = 9;
            srd->error = (int) ret;
        }
        FUN_002725a0(0x2100);
        ret = FUN_00272970(srd->fd, srd->host_buf, srd->host_size);
        FUN_002725a0(0x2101);
        if (ret >= 0) {
            srd->stat = 2;
            DAT_004a92e0++;
        } else {
            srd->stat = 9;
            srd->error = (int) ret;
        }
    }
    if (srd->stat == 2) {
        FUN_002725a0(0x2200);
        if (FUN_00272838(srd->fd, 1, &busy) < 0) {
            FUN_002725a0(0x2201);
            srd->stat = 9;
            srd->error = -1;
        } else {
            FUN_002725a0(0x2202);
            if (busy == 0) {
                srd->stat = 3;
                DAT_004a92e4++;
            }
        }
    }
}

int FUN_00272108(void)
{
    return DAT_004a92c4;
}

void FUN_00272118(void)
{
    SrdObj *srd = &DAT_004a9288;

    if (SVM_TestAndSet(&DAT_004a92c4) == 0) {
        return;
    }
    if (srd->devtype == 1) {
        if (DAT_004a92c8 == 1) {
            SVM_LockDev();
        }
        FUN_00271d50(srd);
        if (DAT_004a92c8 == 1) {
            SVM_UnlockDev();
        }
    }
    if (srd->devtype == 2) {
        if (DAT_004a92cc == 1) {
            SVM_LockDev();
        }
        FUN_00271f38(srd);
        if (DAT_004a92cc == 1) {
            SVM_UnlockDev();
        }
    }
    DAT_004a92c4 = 0;
}

signed char FUN_00272208(void)
{
    return DAT_004a9288.devtype;
}

int FUN_00272218(void)
{
    return DAT_004a9288.error;
}

void FUN_00272228(void)
{
    DAT_004a92d8 = 0;
    while (DAT_004a92c4 == 1) {
        DAT_004a92d8++;
        if (DAT_004a92d8 > 0x19640000) {
            scePrintf(SRD_SRD_WaitForExecServer_timeout_10sec);
            break;
        }
    }
}

void FUN_00272290(int value)
{
    FUN_00272228();
    DAT_004a92c8 = (signed char)value;
}

void FUN_002722c8(int value)
{
    FUN_00272228();
    DAT_004a92cc = (char)value;
}

void FUN_00272300(int value)
{
    FUN_00272228();
    DAT_004a92d0 = (char)value;
}

void FUN_00272338(int value)
{
    FUN_00272228();
    DAT_004a92d4 = (char)value;
}

void FUN_00272370(void)
{
    DAT_004a9288.stat = 9;
}

int FUN_00272380(void)
{
    int busy;

    FUN_002725a0(0x2300);
    busy = sceCdSync(1);
    FUN_002725a0(0x2301);
    return busy;
}

int FUN_002723c0(void)
{
    int status;

    if (DAT_004a9288.stat == 2) {
        SVM_Lock();
        FUN_002725a0(0x2400);
        if (FUN_00272838(DAT_004a9288.fd, 1, &status) < 0) {
            FUN_002725a0(0x2401);
        } else {
            FUN_002725a0(0x2402);
            if (status != 0) {
                SVM_Unlock();
                return 1;
            }
        }
        SVM_Unlock();
    }
    return 0;
}

int FUN_00272460(void)
{
    if (DAT_004a9288.devtype == 1) {
        return FUN_00272380() * 2;
    }
    if (DAT_004a9288.devtype == 2) {
        return FUN_002723c0();
    }
    return 0;
}

int FUN_002724b0(void)
{
    scePrintf(SRD_SRD_Info);
    scePrintf(srd_enter_fg_d, DAT_004a92c4);
    scePrintf(srd_debug_geterror_d, DAT_004a92dc);
    scePrintf(srd_obj_stat_d, DAT_004a9288.stat);
    if (DAT_004a9288.devtype == 1) {
        scePrintf(srd_obj_devtype_DVD);
    }
    if (DAT_004a9288.devtype == 2) {
        scePrintf(srd_obj_devtype_HOST);
    }
    scePrintf(Read_Status_DVD_2_HST_1_d, FUN_00272460());
    return 0;
}

int FUN_00272580(void)
{
    return DAT_004a92e4;
}

int FUN_00272590(void)
{
    return DAT_004a92e0;
}

void FUN_002725a0(int value)
{
    DAT_004a92f0 = DAT_004a92f4;
    DAT_004a92f4 = value;
}

int FUN_002725c0(void)
{
    return DAT_004a92f4;
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
    DAT_004a92cc = (char)value;
    DAT_004a92fc = DAT_004a92cc;
    if (value == 1) {
        scePrintf(SRD_Enable_HostLock);
    }
}

int FUN_00272678(void)
{
    return DAT_004a92fc;
}

void srd_Lock(void)
{
    if (DAT_004a92fc == 1) {
        SVM_LockDev();
    }
}

void srd_Unlock(void)
{
    if (DAT_004a92fc == 1) {
        SVM_UnlockDev();
    }
}

int FUN_002726f8(int lsn)
{
    int ok;
    int err;
    int ret;

    ret = SVM_TestAndSet(&DAT_004a92c4);
    err = 0;
    if (ret != 0) {
        FUN_002725a0(0x9600);
        ok = sceCdSeek(lsn);
        FUN_002725a0(0x9601);
        if (ok == 0) {
            err = sceCdGetError();
        }
        DAT_004a92c4 = 0;
        ret = err;
    }
    return ret;
}

/* Seek on a host file: the 64-bit seek when the host mode word is 1, else the 32-bit seek, whose int
   result widens into the long. */
long SRD_Lseek(int fd, long offset, int whence)
{
    long ret;

    srd_Lock();
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
    srd_Unlock();
    return ret;
}

int FUN_00272838(int fd, int cmd, int *result)
{
    int ret;

    srd_Lock();
    ret = sceIoctl(fd, cmd, result);
    if (ret < 0) {
        scePrintf(DAT_004efea0, ret);
    }
    srd_Unlock();
    return ret;
}

int FUN_002728b0(int name, int flags)
{
    int ret;

    srd_Lock();
    ret = sceOpen(name, flags);
    if (ret < 0) {
        scePrintf(DAT_004efec0, ret);
    }
    srd_Unlock();
    return ret;
}

int FUN_00272918(int fd)
{
    int ret;

    srd_Lock();
    ret = sceClose(fd);
    if (ret < 0) {
        scePrintf(DAT_004efee0, ret);
    }
    srd_Unlock();
    return ret;
}

int FUN_00272970(int fd, void *buf, int size)
{
    int ret;

    srd_Lock();
    ret = sceRead(fd, buf, size);
    if (ret < 0) {
        scePrintf(DAT_004eff00, ret);
    }
    srd_Unlock();
    return ret;
}

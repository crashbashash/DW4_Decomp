/* filestub.c - libkernl's EE side of the IOP file system: each sce* file call packs its arguments into
 * one shared send buffer and calls fileio's RPC server, which writes the result back by SIF DMA. */
#include "dw4/eekernel.h"
#include "dw4/sony/sif.h"

#define FS_MAX_IOB 32
#define FS_PATH_MAX 1024

/* sceFsSifCallRpc's command numbers: fileio.irx's RPC functions */
#define FS_CLOSE 1
#define FS_REMOVE 6
#define FS_MKDIR 7
#define FS_RMDIR 8
#define FS_DOPEN 9
#define FS_DCLOSE 10
#define FS_DREAD 11
#define FS_GETSTAT 12
#define FS_CHSTAT 13
#define FS_FORMAT 14
#define FS_ADDDRV 15
#define FS_DELDRV 16
#define FS_RENAME 17
#define FS_CHDIR 18
#define FS_SYNC 19
#define FS_MOUNT 20
#define FS_UMOUNT 21
#define FS_DEVCTL 23
#define FS_SYMLINK 24
#define FS_READLINK 25
#define FS_IOCTL2 26
#define FS_POWEROFF 27

/* The IOP writes the RPC reply by DMA, so the first reply word is read through the uncached segment. */
#define UNCACHED_WORD(p) (*(int *)((unsigned int)(p) | 0x20000000))

/* sce error codes the calls return */
#define SCE_ENXIO (-6)
#define SCE_E2BIG (-7)
#define SCE_EBADF (-9)
#define SCE_EAGAIN (-11)
#define SCE_ENODEV (-19)
#define SCE_EINVAL (-22)

/* One open descriptor: fileio's descriptor and the mode it was opened with (0 = free). */
typedef struct {
    int fd;
    int mode;
    int pad[2];
} _sceFsIob;

/* Every request starts with the semaphore the reply handler signals and where it writes the result. */
typedef struct {
    int sema;
    int *result;
    int resultSize;
    int fd;
    int mode;
    char name[FS_PATH_MAX];
} FsOpenRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    char name[FS_PATH_MAX];
} FsPathRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    int mode;
    char name[FS_PATH_MAX];
} FsMkdirRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    void *stat;
    unsigned char name[FS_PATH_MAX];
} FsGetstatRequest;

/* struct sce_stat travels as its 64 bytes. */
typedef struct {
    char bytes[64];
} FsStatBlock;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    unsigned int mask;
    FsStatBlock stat;
    unsigned char name[FS_PATH_MAX];
} FsChstatRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    int fd;
    void *buf;
} FsDreadRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    void *device;
} FsAddDrvRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    char from[FS_PATH_MAX];
    char to[FS_PATH_MAX];
} FsRenameRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    char device[FS_PATH_MAX];
    char path[FS_PATH_MAX];
    char arg[FS_PATH_MAX];
    int arglen;
} FsFormatRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    char device[FS_PATH_MAX];
    char path[FS_PATH_MAX];
    char arg[FS_PATH_MAX];
    int flag;
    int arglen;
} FsMountRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    char name[FS_PATH_MAX];
    char arg[FS_PATH_MAX];
    int cmd;
    unsigned int arglen;
    void *buf;
    unsigned int buflen;
} FsDevctlRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    unsigned int buflen;
    void *buf;
    char name[FS_PATH_MAX];
} FsReadlinkRequest;

typedef struct {
    int sema;
    int *result;
    int resultSize;
    int fd;
    int cmd;
    char arg[FS_PATH_MAX];
    void *buf;
    unsigned int buflen;
    unsigned int arglen;
} FsIoctl2Request;

typedef void (*scePowerOffFunc)(void *data);

typedef struct {
    scePowerOffFunc func;
    void *data;
} FsPowerOffData;

int DIntr(void);
int EIntr(void);
int memcmp(const void *a, const void *b, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
void *memset(void *dst, int value, unsigned int size);
int sceFsInit(void);

extern char __ps2_klibinfo__[];
extern int _fs_init;
extern int _fs_semid;
extern int _fs_iob_semid;
extern int _fs_fsq_semid;
extern char *_fswildcard;
extern FsOpenRequest _send_data;
extern int _rcv_data_rpc[];
extern _sceFsIob _iob[FS_MAX_IOB];
extern sceSifClientData _fs_cd;
extern char _fsversion[];
extern FsPowerOffData _sif_FsPoff_Data;
extern void *sceCbPoff_Gp;

void _sceFsIobSemaMK(void)
{
    struct SemaParam param;
    if (_fs_iob_semid == -1) {
        param.option = 0;
        param.initCount = 1;
        param.maxCount = 1;
        _fs_iob_semid = CreateSema(&param);
        _fs_fsq_semid = CreateSema(&param);
    }
}

_sceFsIob *new_iob(void)
{
    _sceFsIob *io;
    _sceFsIobSemaMK();
    WaitSema(_fs_iob_semid);
    for (io = _iob; io < _iob + FS_MAX_IOB; io++) {
        if (io->mode == 0) {
            io->mode = 0x10000000;
            SignalSema(_fs_iob_semid);
            return io;
        }
    }
    SignalSema(_fs_iob_semid);
    return 0;
}

_sceFsIob *get_iob(unsigned int fd)
{
    _sceFsIob *io;
    _sceFsIobSemaMK();
    WaitSema(_fs_iob_semid);
    if (fd >= FS_MAX_IOB) {
        SignalSema(_fs_iob_semid);
        return 0;
    }
    io = &_iob[fd];
    SignalSema(_fs_iob_semid);
    return io;
}

void _sceFsSemInit(void)
{
    struct SemaParam param;
    if (_fs_semid == -1) {
        param.initCount = 1;
        param.maxCount = 1;
        param.option = 0;
        _fs_semid = CreateSema(&param);
    }
}

/* Takes the send buffer for one call; the command number is unused. */
int _sceFsWaitS(int cmd)
{
    _sceFsSemInit();
    WaitSema(_fs_semid);
    return 0;
}

void _sceFsSigSema(void)
{
    SignalSema(_fs_semid);
}

scePowerOffFunc scePowerOffHandler(scePowerOffFunc func, void *data)
{
    FsPowerOffData *poff = &_sif_FsPoff_Data;
    scePowerOffFunc old;
    int enabled;
    _sceFsWaitS(FS_POWEROFF);
    if (_fs_init == 0) {
        sceFsInit();
    }
    enabled = DIntr();
    old = _sif_FsPoff_Data.func;
    poff->data = data;
    _sif_FsPoff_Data.func = func;
    __asm__("sw $28,%0" : : "m"(sceCbPoff_Gp));
    if (enabled) {
        EIntr();
    }
    _sceFsSigSema();
    return old;
}

/* Nonzero when fileio's version differs from libkernl's and neither is the wildcard. */
int _fs_version(void)
{
    char *expected = &__ps2_klibinfo__[12];
    char *version = _fsversion;
    int result = 0;
    if (memcmp(version, expected, 4) != 0 && memcmp(version, _fswildcard, 4) != 0) {
        result = memcmp(expected, _fswildcard, 4) != 0;
    }
    return result;
}

int sceFsReset(void)
{
    _fs_init = 0;
    memset(_fsversion, 0, 4);
    return 0;
}

int sceClose(int fd)
{
    FsOpenRequest *req = &_send_data;
    _sceFsIob *io;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    io = get_iob(fd);
    _sceFsWaitS(FS_CLOSE);
    if (_fs_init == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (io == 0 || io->mode == 0) {
        _sceFsSigSema();
        return SCE_EBADF;
    }
    req->fd = io->fd;
    req->mode = io - _iob;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->sema = sema;
    req->result = &result;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_CLOSE, 0, req, 20, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    io->mode = 0;
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (result < 0) {
        return result;
    }
    return 0;
}

int sceIoctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
    _sceFsIob *io = get_iob(fd);
    FsIoctl2Request *req = (FsIoctl2Request *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    _sceFsWaitS(FS_IOCTL2);
    if (_fs_init == 0) {
        sceFsInit();
    }
    if (io == 0 || io->mode == 0) {
        _sceFsSigSema();
        return SCE_EBADF;
    }
    if (arglen > FS_PATH_MAX || buflen > FS_PATH_MAX) {
        _sceFsSigSema();
        return SCE_EINVAL;
    }
    if (arg == 0) {
        req->arglen = 0;
    } else {
        memcpy(req->arg, arg, arglen);
    }
    req->fd = io->fd;
    req->cmd = cmd;
    req->arglen = arglen;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->buflen = buflen;
    req->result = &result;
    req->resultSize = 4;
    req->buf = buf;
    req->sema = sema;
    sceSifWriteBackDCache(&_send_data, sizeof(FsIoctl2Request));
    if (sceSifCallRpc(&_fs_cd, FS_IOCTL2, 0, &_send_data, sizeof(FsIoctl2Request), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

/* The calls that send one path: remove, rmdir, dopen, deldrv, chdir, umount. */
static int _sceCallCode(const char *name, int cmd)
{
    FsPathRequest *req = (FsPathRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(cmd);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
        i = FS_PATH_MAX - 1;
    }
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, cmd, 0, &_send_data, i + 13, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceRemove(const char *name)
{
    return _sceCallCode(name, FS_REMOVE);
}

int sceMkdir(const char *name, int mode)
{
    FsMkdirRequest *req = (FsMkdirRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_MKDIR);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
        i = FS_PATH_MAX - 1;
    }
    req->mode = mode;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_MKDIR, 0, &_send_data, i + 17, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceRmdir(const char *name)
{
    return _sceCallCode(name, FS_RMDIR);
}

int sceFormat(const char *device, const char *blockdev, const void *arg, int arglen)
{
    FsFormatRequest *req = (FsFormatRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_FORMAT);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->device[i] = device[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->device[FS_PATH_MAX - 1] = 0;
    }
    if (blockdev == 0) {
        req->path[0] = 0;
    } else {
        for (i = 0; i < FS_PATH_MAX; i++) {
            if ((req->path[i] = blockdev[i]) == 0) {
                break;
            }
        }
        if (i == FS_PATH_MAX) {
            req->path[FS_PATH_MAX - 1] = 0;
        }
    }
    if (arglen > FS_PATH_MAX) {
        _sceFsSigSema();
        return SCE_E2BIG;
    }
    for (i = 0; i < arglen; i++) {
        req->arg[i] = ((const unsigned char *)arg)[i];
    }
    req->arglen = arglen;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    sceSifWriteBackDCache(&_send_data, sizeof(FsFormatRequest));
    if (sceSifCallRpc(&_fs_cd, FS_FORMAT, 0, &_send_data, sizeof(FsFormatRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceAddDrv(void *device)
{
    FsAddDrvRequest *req = (FsAddDrvRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    _sceFsWaitS(FS_ADDDRV);
    if (_fs_init == 0) {
        sceFsInit();
    }
    req->device = device;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->sema = sema;
    req->result = &result;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_ADDDRV, 0, req, sizeof(FsAddDrvRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return -1;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return -1;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceDelDrv(const char *name)
{
    return _sceCallCode(name, FS_DELDRV);
}

int sceDopen(const char *name)
{
    _sceFsIob *io;
    int fd;
    _sceFsWaitS(FS_DOPEN);
    if (_fs_init == 0) {
        sceFsInit();
    }
    _sceFsSigSema();
    io = new_iob();
    if (io == 0) {
        return SCE_ENODEV;
    }
    fd = _sceCallCode(name, FS_DOPEN);
    if (fd < 0) {
        WaitSema(_fs_iob_semid);
        io->mode = 0;
        SignalSema(_fs_iob_semid);
        return fd;
    }
    WaitSema(_fs_iob_semid);
    io->fd = fd;
    fd = io - _iob;
    SignalSema(_fs_iob_semid);
    return fd;
}

int sceDclose(int fd)
{
    FsOpenRequest *req = &_send_data;
    _sceFsIob *io;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    io = get_iob(fd);
    _sceFsWaitS(FS_DCLOSE);
    if (_fs_init == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (io == 0 || io->mode == 0) {
        _sceFsSigSema();
        return SCE_EBADF;
    }
    req->fd = io->fd;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->sema = sema;
    req->result = &result;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_DCLOSE, 0, req, 20, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    io->mode = 0;
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (result < 0) {
        return result;
    }
    return 0;
}

int sceDread(int fd, void *buf)
{
    FsDreadRequest *req = (FsDreadRequest *)&_send_data;
    _sceFsIob *io;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    io = get_iob(fd);
    _sceFsWaitS(FS_DREAD);
    if (_fs_init == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (io == 0 || io->mode == 0) {
        _sceFsSigSema();
        return SCE_EBADF;
    }
    req->fd = io->fd;
    req->buf = buf;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->sema = sema;
    req->result = &result;
    req->resultSize = 4;
    /* Sony's send size covers more than the request; fileio reads only fd and buf. */
    if (sceSifCallRpc(&_fs_cd, FS_DREAD, 0, req, 32, _rcv_data_rpc, 4, 0, 0) < 0) {
        WaitSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceGetstat(const char *name, void *stat)
{
    FsGetstatRequest *req = (FsGetstatRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_GETSTAT);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
        i = FS_PATH_MAX - 1;
    }
    req->stat = stat;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_GETSTAT, 0, &_send_data, i + 17, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceChstat(const char *name, const FsStatBlock *stat, unsigned int mask)
{
    FsChstatRequest *req = (FsChstatRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_CHSTAT);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
        i = FS_PATH_MAX - 1;
    }
    req->stat = *stat;
    req->mask = mask;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    sceSifWriteBackDCache(&_send_data, sizeof(FsChstatRequest));
    if (sceSifCallRpc(&_fs_cd, FS_CHSTAT, 0, &_send_data, i + 81, _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceRename(const char *from, const char *to)
{
    FsRenameRequest *req = (FsRenameRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_RENAME);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->from[i] = from[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->from[FS_PATH_MAX - 1] = 0;
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->to[i] = to[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->to[FS_PATH_MAX - 1] = 0;
    }
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    sceSifWriteBackDCache(&_send_data, sizeof(FsRenameRequest));
    if (sceSifCallRpc(&_fs_cd, FS_RENAME, 0, &_send_data, sizeof(FsRenameRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceChdir(const char *name)
{
    return _sceCallCode(name, FS_CHDIR);
}

int sceSync(const char *device, int flag)
{
    FsOpenRequest *req = &_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_SYNC);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = device[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
    }
    req->mode = flag;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_SYNC, 0, &_send_data, sizeof(FsOpenRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceMount(const char *device, const char *blockdev, int flag, const void *arg, int arglen)
{
    FsMountRequest *req = (FsMountRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_MOUNT);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->device[i] = device[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->device[FS_PATH_MAX - 1] = 0;
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->path[i] = blockdev[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->path[FS_PATH_MAX - 1] = 0;
    }
    if (arglen > FS_PATH_MAX) {
        _sceFsSigSema();
        return SCE_E2BIG;
    }
    for (i = 0; i < arglen; i++) {
        req->arg[i] = ((const unsigned char *)arg)[i];
    }
    req->arglen = arglen;
    req->flag = flag;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    sceSifWriteBackDCache(&_send_data, sizeof(FsMountRequest));
    if (sceSifCallRpc(&_fs_cd, FS_MOUNT, 0, &_send_data, sizeof(FsMountRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

int sceUmount(const char *device)
{
    return _sceCallCode(device, FS_UMOUNT);
}

int sceDevctl(const char *name, int cmd, const void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
    FsDevctlRequest *req = (FsDevctlRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_DEVCTL);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
    }
    if (arglen > FS_PATH_MAX || buflen > FS_PATH_MAX) {
        _sceFsSigSema();
        return SCE_EINVAL;
    }
    for (i = 0; i < arglen; i++) {
        req->arg[i] = ((const unsigned char *)arg)[i];
    }
    req->arglen = arglen;
    req->cmd = cmd;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    req->buf = buf;
    req->buflen = buflen;
    sceSifWriteBackDCache(&_send_data, sizeof(FsDevctlRequest));
    if (sceSifCallRpc(&_fs_cd, FS_DEVCTL, 0, &_send_data, sizeof(FsDevctlRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

/* Takes the send buffer under FS_RENAME's number, as Sony's code does. */
int sceSymlink(const char *existing, const char *newname)
{
    FsRenameRequest *req = (FsRenameRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_RENAME);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->from[i] = existing[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->from[FS_PATH_MAX - 1] = 0;
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->to[i] = newname[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->to[FS_PATH_MAX - 1] = 0;
    }
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_SYMLINK, 0, &_send_data, sizeof(FsRenameRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

/* Takes the send buffer under FS_RENAME's number and sends a rename-sized request, as Sony's code does. */
int sceReadlink(const char *name, void *buf, unsigned int buflen)
{
    FsReadlinkRequest *req = (FsReadlinkRequest *)&_send_data;
    struct SemaParam param;
    int result;
    int sema;
    int sent;
    int i;
    _sceFsWaitS(FS_RENAME);
    if (_fs_init == 0) {
        sceFsInit();
    }
    for (i = 0; i < FS_PATH_MAX; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == FS_PATH_MAX) {
        req->name[FS_PATH_MAX - 1] = 0;
    }
    if (buflen >= FS_PATH_MAX) {
        buflen = FS_PATH_MAX - 1;
    }
    req->buf = buf;
    req->buflen = buflen;
    sceSifWriteBackDCache(buf, buflen);
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->resultSize = 4;
    if (sceSifCallRpc(&_fs_cd, FS_READLINK, 0, &_send_data, sizeof(FsRenameRequest), _rcv_data_rpc, 4, 0, 0) < 0) {
        DeleteSema(sema);
        _sceFsSigSema();
        return SCE_EAGAIN;
    }
    sent = UNCACHED_WORD(_rcv_data_rpc);
    _sceFsSigSema();
    if (sent == 0) {
        DeleteSema(sema);
        return SCE_EAGAIN;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}

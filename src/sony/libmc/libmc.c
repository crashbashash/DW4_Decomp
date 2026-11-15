#include "dw4/eekernel.h"
#include "dw4/libkernl.h"
#include "dw4/sony/sif.h"

typedef struct sceMcStDateTime {
    unsigned char Resv2;
    unsigned char Sec;
    unsigned char Min;
    unsigned char Hour;
    unsigned char Day;
    unsigned char Month;
    unsigned short Year;
} sceMcStDateTime;

typedef struct sceMcTblGetDir {
    sceMcStDateTime _Create;
    sceMcStDateTime _Modify;
    unsigned int FileSizeByte;
    unsigned short AttrFile;
    unsigned short Reserve1;
    unsigned int Reserve2;
    unsigned int PdaAplNo;
    unsigned char EntryName[32];
} sceMcTblGetDir;

/* mcserv.irx's RPC function numbers; also the value of mcRunCmdNo while a call is outstanding */
#define sceMcFuncNoCardInfo (1)
#define sceMcFuncNoOpen (2)
#define sceMcFuncNoClose (3)
#define sceMcFuncNoSeek (4)
#define sceMcFuncNoRead (5)
#define sceMcFuncNoWrite (6)
#define sceMcFuncNoFlush (10)
#define sceMcFuncNoMkdir (11)
#define sceMcFuncNoChDir (12)
#define sceMcFuncNoGetDir (13)
#define sceMcFuncNoFileInfo (14)
#define sceMcFuncNoDelete (15)
#define sceMcFuncNoFormat (16)
#define sceMcFuncNoUnformat (17)
#define sceMcFuncNoEntSpace (18)
#define sceMcFuncNoRename (19)
#define sceMcFuncChgPrior (20)
#define sceMcFuncSlotMax (21)
#define sceMcFuncNoUdCheckNewCard 53
#define sceMcFuncNoInit 254

#define sceMcFileInfoCreate 0x01
#define sceMcFileInfoModify 0x02
#define sceMcFileInfoAttr 0x04

#define sceMcErrUnbind (-100)
#define sceMcErrSemapho (-200)
#define sceMcErrNullStr (-210)
#define sceMcIniOldMcserv (-120)
#define sceMcIniOldMcman (-121)

#define MC_SERVER_ID 0x80000400
#define UNCACHED_SEGMENT 0x20000000

/* Parameter block for every RPC that names no path. Which of the words are used depends on the call. */
typedef struct McCommand {
    int fd;
    int port;
    int slot;
    int size;
    int offset;
    unsigned int count;
    unsigned char *buffer;
    void *apdx;
    unsigned char head[16];
} McCommand;

/* Parameter block for the RPCs that name a path. */
typedef struct McPathCommand {
    int port;
    int slot;
    int flags;
    int maxent;
    void *table;
    char path[1024];
} McPathCommand;

/* What the IOP writes back for sceMcGetInfo. */
typedef struct McInfoApdx {
    int type;
    int free;
    int reserved[34];
    int format;
} McInfoApdx;

/* What the IOP writes back for sceMcRead: the unaligned head and tail of the transfer. */
typedef struct McReadApdx {
    int head_size;
    int tail_size;
    unsigned char *head_dest;
    unsigned char *tail_dest;
    unsigned char head[64];
    unsigned char tail[64];
} McReadApdx;

typedef union McApdx {
    McInfoApdx info;
    McReadApdx read;
    unsigned char raw[192];
} McApdx;

int PollSema(int sema);
int scePrintf(const char *format, ...);
char *strncpy(char *dst, const char *src, unsigned int n);
unsigned int strlen(const char *s);
void *memcpy(void *dst, const void *src, unsigned int n);

int sceMcSync(int mode, int *cmd, int *result);

static char __ps2_libinfo__[16] = "PsIIlibmc   2810";
static int mcRunCmdNo = 0;
static int semaidRegFunc = -1;
static int semaid_timerfunc = -1;

static sceSifClientData mcClientID;
static int *typeAddr;
static int *freeAddr;
static int *formAddr;
static sceMcTblGetDir buffFileInfo __attribute__((aligned(64)));
static McCommand sifParamOrd;
static McPathCommand sifParamFname;
static McApdx sifParamNext __attribute__((aligned(64)));
static char currentDir[4096] __attribute__((aligned(64)));
static int retval[16] __attribute__((aligned(64)));

int sceMcInit(void)
{
    struct SemaParam sema;
    int result;
    int retry;

    if (semaidRegFunc < 0) {
        sema.initCount = 1;
        sema.maxCount = 1;
        sema.option = 0;
        semaidRegFunc = CreateSema(&sema);
        sema.initCount = 0;
        sema.maxCount = 1;
        sema.option = 0;
        semaid_timerfunc = CreateSema(&sema);
    }
    sceMcSync(0, 0, 0);
    WaitSema(semaidRegFunc);
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&mcClientID, MC_SERVER_ID, 0) < 0) {
            scePrintf("bind error libmc \n");
            while (1);
        }
        if (mcClientID.serve != 0) break;
        retry = 0x100000;
        while (--retry);
    }
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoInit, 0, &sifParamOrd, 48, retval, 12, 0, 0);
    SignalSema(semaidRegFunc);
    if (result < 0) {
        mcClientID.serve = 0;
        return result - 100;
    }
    if (retval[1] < 522) {
        scePrintf("libmc: too old release of mcserv.irx\n");
        mcClientID.serve = 0;
        return sceMcIniOldMcserv;
    }
    if (retval[2] < 526) {
        scePrintf("libmc: too old release of mcman.irx\n");
        mcClientID.serve = 0;
        return sceMcIniOldMcman;
    }
    return retval[0];
}

int sceMcEnd(void)
{
    if (semaidRegFunc >= 0) {
        DeleteSema(semaidRegFunc);
        semaidRegFunc = -1;
        DeleteSema(semaid_timerfunc);
    }
    return 1;
}

void *mceGetClientState(int **result, int **cmd)
{
    *result = retval;
    *cmd = &mcRunCmdNo;
    retval[15] = semaidRegFunc;
    return &mcClientID;
}

static void mceSifRpcEndFunc(void *param)
{
    iSignalSema(semaid_timerfunc);
}

int sceMcChangeThreadPriority(int priority)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.count = priority;
    result = sceSifCallRpc(&mcClientID, sceMcFuncChgPrior, 1, &sifParamOrd, 48, retval, 4,
                           mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncChgPrior;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcGetSlotMax(int port)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.port = port;
    result = sceSifCallRpc(&mcClientID, sceMcFuncSlotMax, 0, &sifParamOrd, 48, retval, 4, 0, 0);
    if (result != 0) {
        SignalSema(semaidRegFunc);
        return result;
    }
    SignalSema(semaidRegFunc);
    return retval[0];
}

int sceMcOpen(int port, int slot, char *name, int mode)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.port = port;
    sifParamFname.flags = mode;
    sifParamFname.slot = slot;
    sifParamFname.path[1023] = 0;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoOpen, 1, &sifParamFname, 1044, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoOpen;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcMkdir(int port, int slot, char *name)
{
    int result;

    result = sceMcOpen(port, slot, name, 0x40);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoMkdir;
    }
    return result;
}

int sceMcClose(int fd)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.fd = fd;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoClose, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoClose;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcSeek(int fd, int offset, int origin)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.fd = fd;
    sifParamOrd.offset = offset;
    sifParamOrd.count = origin;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoSeek, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoSeek;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

static void mceIntrReadFixAlign(void *apdx)
{
    McReadApdx *read;
    unsigned char *dest;
    int i;

    read = (McReadApdx *)((unsigned int)apdx | UNCACHED_SEGMENT);
    if (read->head_size != 0) {
        dest = read->head_dest;
        for (i = 0; i < read->head_size; i++) *dest++ = read->head[i];
    }
    if (read->tail_size != 0) {
        dest = read->tail_dest;
        for (i = 0; i < read->tail_size; i++) *dest++ = read->tail[i];
    }
    iSignalSema(semaid_timerfunc);
}

int sceMcRead(int fd, void *buffer, int size)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.fd = fd;
    sifParamOrd.buffer = buffer;
    sifParamOrd.size = size;
    sifParamOrd.apdx = &sifParamNext;
    sceSifWriteBackDCache(buffer, size);
    sceSifWriteBackDCache(&sifParamNext, 192);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoRead, 1, &sifParamOrd, 48, retval, 4, mceIntrReadFixAlign,
                           &sifParamNext);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoRead;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcWrite(int fd, void *buffer, int size)
{
    unsigned char *src;
    unsigned int head;
    unsigned int i;
    int result;

    src = buffer;
    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.fd = fd;
    if (size < 17) {
        sifParamOrd.count = size;
        sifParamOrd.size = 0;
        sifParamOrd.buffer = 0;
    } else {
        head = (((int)src - 1) & 0xfffffff0) + 16 - (int)src;
        sifParamOrd.count = head;
        sifParamOrd.size = size - head;
        sifParamOrd.buffer = src + head;
    }
    for (i = 0; i < sifParamOrd.count; i++) sifParamOrd.head[i] = src[i];
    FlushCache(0);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoWrite, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoWrite;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcSync(int mode, int *cmd, int *result)
{
    int finished;

    if (mcRunCmdNo == 0) return -1;
    finished = 0;
    if (PollSema(semaid_timerfunc) < 0) finished = 1;
    if (mode == 0 && finished) {
        WaitSema(semaid_timerfunc);
        finished = 0;
    }
    finished = !finished;
    if (cmd) *cmd = mcRunCmdNo;
    if (finished) {
        mcRunCmdNo = 0;
        if (result) *result = retval[0];
        SignalSema(semaidRegFunc);
    }
    return finished;
}

static void mceGetInfoApdx(void *apdx)
{
    McInfoApdx *info;

    info = (McInfoApdx *)((unsigned int)apdx | UNCACHED_SEGMENT);
    if (typeAddr) *typeAddr = info->type;
    if (freeAddr) *freeAddr = info->free;
    if (formAddr) *formAddr = info->format;
    iSignalSema(semaid_timerfunc);
}

int sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.port = port;
    sifParamOrd.slot = slot;
    sifParamOrd.apdx = &sifParamNext;
    if (type) sifParamOrd.count = 1; else sifParamOrd.count = 0;
    if (free) sifParamOrd.offset = 1; else sifParamOrd.offset = 0;
    if (format) sifParamOrd.size = 1; else sifParamOrd.size = 0;
    typeAddr = type;
    freeAddr = free;
    formAddr = format;
    sceSifWriteBackDCache(&sifParamNext, 192);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoCardInfo, 1, &sifParamOrd, 48, retval, 4, mceGetInfoApdx,
                           &sifParamNext);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoCardInfo;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcUdCheckNewCard(void)
{
    if (sceSifCallRpc(&mcClientID, sceMcFuncNoUdCheckNewCard, 0, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0)) {
        scePrintf("sceMcUdCheckNewCard RPC faild\n");
        return -1;
    }
    return retval[0];
}

int sceMcGetDir(int port, int slot, char *name, int mode, int maxent, sceMcTblGetDir *table)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    sifParamFname.flags = mode;
    sifParamFname.maxent = maxent;
    sifParamFname.table = table;
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.path[1023] = 0;
    if (maxent >= 0) sceSifWriteBackDCache(table, maxent << 6);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoGetDir, 1, &sifParamFname, 1044, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoGetDir;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

static void mceStorePwd(char *dir)
{
    unsigned int length;

    if (dir) {
        if (strlen((char *)((unsigned int)currentDir | UNCACHED_SEGMENT)) < 1024) {
            length = strlen((char *)((unsigned int)currentDir | UNCACHED_SEGMENT));
        } else {
            length = 1023;
        }
        memcpy(dir, (char *)((unsigned int)currentDir | UNCACHED_SEGMENT), length);
        dir[length] = 0;
    }
    iSignalSema(semaid_timerfunc);
}

int sceMcChdir(int port, int slot, char *name, char *dir)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    sifParamFname.table = currentDir;
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.path[1023] = 0;
    sceSifWriteBackDCache(currentDir, 1024);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoChDir, 1, &sifParamFname, 1044, retval, 4, mceStorePwd, dir);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoChDir;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcFormat(int port, int slot)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.port = port;
    sifParamOrd.slot = slot;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoFormat, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoFormat;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcDelete(int port, int slot, char *name)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    sifParamFname.path[1023] = 0;
    sifParamFname.flags = 0;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoDelete, 1, &sifParamFname, 1044, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoDelete;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcFlush(int fd)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.fd = fd;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoFlush, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoFlush;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcSetFileInfo(int port, int slot, char *name, sceMcTblGetDir *info, unsigned int flags)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    flags &= sceMcFileInfoCreate | sceMcFileInfoModify | sceMcFileInfoAttr;
    sifParamFname.flags = flags;
    buffFileInfo = *info;
    sifParamFname.table = &buffFileInfo;
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.path[1023] = 0;
    FlushCache(0);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoFileInfo, 1, &sifParamFname, 1044, retval, 4,
                           mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoFileInfo;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcRename(int port, int slot, char *name, char *newname)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0 || newname == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    sifParamFname.flags = 16;
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.path[1023] = 0;
    strncpy((char *)buffFileInfo.EntryName, newname, 32);
    buffFileInfo.EntryName[31] = 0;
    sifParamFname.table = &buffFileInfo;
    FlushCache(0);
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoFileInfo, 1, &sifParamFname, 1044, retval, 4,
                           mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoRename;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcUnformat(int port, int slot)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    sifParamOrd.port = port;
    sifParamOrd.slot = slot;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoUnformat, 1, &sifParamOrd, 48, retval, 4, mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoUnformat;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

int sceMcGetEntSpace(int port, int slot, char *name)
{
    int result;

    if (mcClientID.serve == 0) return sceMcErrUnbind;
    if (PollSema(semaidRegFunc) < 0) return sceMcErrSemapho;
    if (name == 0 || *name == 0) {
        SignalSema(semaidRegFunc);
        return sceMcErrNullStr;
    }
    sifParamFname.port = port;
    sifParamFname.slot = slot;
    strncpy(sifParamFname.path, name, 1023);
    sifParamFname.path[1023] = 0;
    result = sceSifCallRpc(&mcClientID, sceMcFuncNoEntSpace, 1, &sifParamFname, 1044, retval, 4,
                           mceSifRpcEndFunc, 0);
    if (result == 0) {
        mcRunCmdNo = sceMcFuncNoEntSpace;
    } else {
        SignalSema(semaidRegFunc);
    }
    return result;
}

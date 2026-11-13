#include "dw4/reflected.h"

/* igFile's OpenMode meta-enum. */
enum OpenMode {
    kRead,
    kWrite,
    kAppend,
    kReadWrite,
    kReadBinary,
    kWriteBinary,
    kAppendBinary,
    kReadWriteBinary,
    kDefaultOpenMode
};

/* CRI ADXF: the status a finished read reports, and the seek origins. */
enum { ADXF_STAT_READEND = 3 };
enum { ADXF_SEEK_SET, ADXF_SEEK_CUR, ADXF_SEEK_END };

/* The warning reporter's answers. */
enum { kReportContinue = 1, kReportIgnoreAlways = 2 };

struct igResult {
    int value;
    bool succeeded();
};

extern "C" {
/* CRI ADXF, on the handle in `_adxf` */
int ADXF_Open(char *fname, int dir);   /* open by name */
int FUN_00261b78(int ptid, int flid);     /* open an AFS partition entry */
void FUN_00261c88(int adxf);              /* close */
int ADXF_ReadNw(int adxf, int nsct, char *buf); /* start a read of nsct sectors */
int FUN_002623f8(int adxf, int nsct, int type);  /* seek */
int FUN_00262510(int adxf);               /* tell, in sectors */
int FUN_00262540(int adxf);               /* file size in sectors */
int ADXF_GetStat(int adxf);               /* status */

void Gap__Core__igObject__constructFields(igObject *self);
void Gap__Core__igObject__userConstruct(igObject *self);
void Gap__Core__igObject__userDestruct(igObject *self);
void Gap__Core__igObject__resetFields(igObject *self);
void *igObject_GetAllocator(igObject *self);
int igMetaObject_CountInstances(int meta, int recursive);
char *Memory_AllocateAlignedWithAllocator(int size, int align, void *allocator); /* aligned allocation */
int Memory_FreeBufferWithAllocator(int buffer, int allocator);
void FUN_002e30b0(igObject *file, const char *fileName); /* sets igFile::_fileName */
int FUN_003082b0(const char *format, ...);  /* reports a warning */
int FUN_00304430(const char *format, ...);  /* prints */
int FUN_00304680(...);
int igAdx_FindAfsFile(int fileName);  /* the file's index in the AFS file list, or -1 */
void igAdx_ExecVsync(void);
void igAdx_ExecServer(int);
int strcmp(const char *, const char *);
int strcpy(char *, int);
int memcpy(char *, char *, int);

extern int g_resultSuccess[4];
extern int g_resultFailure[4];
extern int g_igAdxFile_metaObject[4];
extern const char DAT_00500060[8]; /* "rb" */
extern const char DAT_00500068[8]; /* "r" */
extern unsigned char GPR_00554de8; /* set while igAdx is initialised */
extern unsigned char g_igAdxFile_ignoreReadModeWarning;
extern unsigned char g_igAdxFile_ignoreWriteWarning;
extern unsigned char g_igAdxFile_ignoreOpenModeWarning;
}

inline bool igResult::succeeded() { return value == g_resultSuccess[0]; }

/* The two igAdxFile virtuals the class calls on itself: the meta-object getter (slot 20,
 * Gap::igAdxFile::vfunc_20) and open (slot 21, Gap::igAdxFile::vfunc_21). */
class igAdxFileVirtuals {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vfunc_20();
    virtual igResult vfunc_21(OpenMode mode);
};

/* The thread the asynchronous wait sleeps on; sleep is its slot 23. */
class SleepingThread {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual igResult sleep(unsigned long long time);
};
struct ThreadList { int _vtable; unsigned int _refCount; int _count; int _capacity; SleepingThread **_data; };
struct ThreadManager { int _vtable; unsigned int _refCount; ThreadList *_threads; };

extern "C" {
extern ThreadManager *g_threadManager;
extern igAdxAfsFileList *DAT_00587620[4]; /* the files the AFS partitions hold */

void Gap__igAdxFile__vfunc_01(igAdxFile *self)
{
    Gap__Core__igObject__constructFields(self);
}

void Gap__igAdxFile__vfunc_11(igAdxFile *self)
{
    Gap__Core__igObject__resetFields(self);
    self->_pBufferPtr = self->_pBuffer;
    self->_bBufferFilled = 0;
    self->_iBufferPos = 0;
    self->_adxf = 0;
}

void Gap__igAdxFile__vfunc_07(igAdxFile *self)
{
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igAdxFileVirtuals *)self)->vfunc_20(), 1);
    self->_pBuffer = (int)Memory_AllocateAlignedWithAllocator(self->_iBufferSize, 0x40, igObject_GetAllocator(self));
    /* matching construct: hand search — the failed-allocation return folds into the epilogue, leaving the reload of
       _pBuffer; the GameCube build keeps the same compare with no branch after it */
    if (self->_pBuffer == 0) {
        return;
    }
}

int Gap__igAdxFile__vfunc_20(void)
{
    return g_igAdxFile_metaObject[0];
}

void Gap__igAdxFile__vfunc_02(igAdxFile *self)
{
    if (self->_pBuffer != 0) {
        Memory_FreeBufferWithAllocator(self->_pBuffer, (int)igObject_GetAllocator(self));
        self->_pBufferPtr = 0;
    }
    if (self->_pTmpBuffer != 0) {
        Memory_FreeBufferWithAllocator(self->_pTmpBuffer, (int)igObject_GetAllocator(self));
    }
}

void Gap__igAdxFile__vfunc_08(igAdxFile *self)
{
    igMetaObject_CountInstances(((igAdxFileVirtuals *)self)->vfunc_20(), 1);
    Gap__Core__igObject__userDestruct(self);
}

int igAdxFile_GetReadStatus(igAdxFile *self)
{
    return ADXF_GetStat(self->_adxf);
}

int igAdxFile_WaitForReadEnd(igAdxFile *self)
{
    while (igAdxFile_GetReadStatus(self) != ADXF_STAT_READEND) {
        if (self->_bUseAsync && self->_bUseAlchemyAsync) {
            g_threadManager->_threads->_data[0]->sleep(self->_lSleepTime);
        } else {
            igAdx_ExecVsync();
        }
        igAdx_ExecServer(0);
    }
    return ADXF_STAT_READEND;
}

void igAdxFile_SetUseBuffer(igAdxFile *self, bool useBuffer)
{
    self->_bUseBuffer = useBuffer;
}

void igAdxFile_SetUseAsync(igAdxFile *self, bool useAsync)
{
    self->_bUseAsync = useAsync;
}

void Gap__igAdxFile__vfunc_21(igResult *result, igAdxFile *self, OpenMode mode)
{
    char fileName[256];
    int answer;
    int index;
    igAdxAfsFile *entry;

    if (GPR_00554de8 == 0) {
        result->value = g_resultFailure[0];
        return;
    }
    if (self->_bIsOpen) {
        result->value = g_resultSuccess[0];
        return;
    }
    if (mode == kDefaultOpenMode) {
        mode = (OpenMode)self->_openMode;
    }
    switch (mode) {
    case kRead:
        if (!g_igAdxFile_ignoreReadModeWarning) {
            answer = FUN_003082b0("Only binary read mode is supported for an igAdxFile file (\"%s\")",
                                 self->_fileName);
            if (answer == kReportContinue) {
            } else if (answer == kReportIgnoreAlways) {
                g_igAdxFile_ignoreReadModeWarning = 1;
            }
        }
        goto open;
    case kWrite:
    case kAppend:
    case kReadWrite:
    case kWriteBinary:
    case kAppendBinary:
        if (!g_igAdxFile_ignoreWriteWarning) {
            answer = FUN_003082b0("Only file reading is supported for an igAdxFile file (\"%s\")",
                                 self->_fileName);
            if (answer == kReportContinue) {
            } else if (answer == kReportIgnoreAlways) {
                g_igAdxFile_ignoreWriteWarning = 1;
            }
        }
        result->value = g_resultFailure[0];
        return;
    default:
        if (!g_igAdxFile_ignoreOpenModeWarning) {
            answer = FUN_003082b0("Unrecognized file open mode");
            if (answer == kReportContinue) {
            } else if (answer == kReportIgnoreAlways) {
                g_igAdxFile_ignoreOpenModeWarning = 1;
            }
        }
        result->value = g_resultFailure[0];
        return;
    case kReadBinary:
    open:
        index = igAdx_FindAfsFile(self->_fileName);
        if (index != -1) {
            entry = ((igAdxAfsFile **)DAT_00587620[0]->_data)[index];
            self->_adxf = FUN_00261b78(entry->_ptNumber, entry->_fileNumber);
        } else {
            strcpy(fileName, self->_fileName);
            self->_adxf = ADXF_Open(fileName, 0);
        }
        if (self->_adxf == 0) {
            result->value = g_resultFailure[0];
            return;
        }
        self->_bIsOpen = 1;
        result->value = g_resultSuccess[0];
        return;
    }
}

void Gap__igAdxFile__vfunc_22(igAdxFile *self)
{
    self->_bBufferFilled = 0;
    self->_iBufferPos = 0;
    if (self->_adxf != 0) {
        FUN_00261c88(self->_adxf);
    }
}

igAdxFile *Gap__igAdxFile__vfunc_23(igAdxFile *self, const char *fileName, const char *mode)
{
    bool opened;

    FUN_002e30b0(self, fileName);
    if (strcmp(mode, DAT_00500060) == 0) {
        opened = ((igAdxFileVirtuals *)self)->vfunc_21(kReadBinary).succeeded();
    } else if (strcmp(mode, DAT_00500068) == 0) {
        opened = ((igAdxFileVirtuals *)self)->vfunc_21(kRead).succeeded();
    } else {
        return 0;
    }
    return opened ? self : 0;
}

void Gap__igAdxFile__vfunc_24(igAdxFile *self)
{
    FUN_00261c88(self->_adxf);
}

int Gap__igAdxFile__vfunc_25(igAdxFile *self, char *dest, int size, int count)
{
    int total;
    int sectors;
    int remaining;
    int done;
    int bufferSize;
    int position;

    total = size * count;
    if (self->_bUseBuffer == 0) {
        sectors = total / self->_iSectorSize;
        if (total % self->_iSectorSize != 0) {
            sectors += 1;
        }
        position = FUN_00262510(self->_adxf);
        if (position < FUN_00262540(self->_adxf)) {
            position = sectors + FUN_00262510(self->_adxf);
            if (FUN_00262540(self->_adxf) < position) {
                sectors = FUN_00262540(self->_adxf) - FUN_00262510(self->_adxf);
            }
            ADXF_ReadNw(self->_adxf, sectors, dest);
        }
        if (self->_bUseAsync == 0 || self->_bUseAlchemyAsync != 0) {
            igAdxFile_WaitForReadEnd(self);
        }
        return count;
    }
    if (self->_bBufferFilled == 0) {
        sectors = self->_iBufferSize / self->_iSectorSize;
        position = FUN_00262510(self->_adxf);
        if (position < FUN_00262540(self->_adxf)) {
            position = sectors + FUN_00262510(self->_adxf);
            if (FUN_00262540(self->_adxf) < position) {
                sectors = FUN_00262540(self->_adxf) - FUN_00262510(self->_adxf);
            }
            ADXF_ReadNw(self->_adxf, sectors, (char *)self->_pBuffer);
        }
        if (self->_bUseAsync == 0 || self->_bUseAlchemyAsync != 0) {
            igAdxFile_WaitForReadEnd(self);
        }
        self->_iBufferPos = 0;
        self->_bBufferFilled = 1;
    }
    remaining = self->_iBufferSize - self->_iBufferPos;
    if (total < remaining) {
        self->_pBufferPtr = self->_pBuffer + self->_iBufferPos;
        memcpy(dest, (char *)self->_pBufferPtr, total);
        self->_iBufferPos = self->_iBufferPos + total;
        if (self->_iBufferPos > self->_iBufferSize - 1) {
            self->_bBufferFilled = 0;
        }
        return count;
    }
    if (self->_pTmpBuffer == 0) {
        self->_pTmpBuffer = (int)Memory_AllocateAlignedWithAllocator(self->_iBufferSize, 0x40, igObject_GetAllocator(self));
        if (self->_pTmpBuffer == 0) {
            return 0;
        }
    }
    done = 0;
    if (0 < total) {
        do {
            sectors = self->_iBufferSize / self->_iSectorSize;
            position = FUN_00262510(self->_adxf);
            if (position < FUN_00262540(self->_adxf)) {
                position = sectors + FUN_00262510(self->_adxf);
                if (FUN_00262540(self->_adxf) < position) {
                    sectors = FUN_00262540(self->_adxf) - FUN_00262510(self->_adxf);
                }
                ADXF_ReadNw(self->_adxf, sectors, (char *)self->_pTmpBuffer);
            } else {
                FUN_00304430("igAdxFile::3 read cancel\n");
                FUN_00304680();
            }
            if (self->_bUseAsync == 0 || self->_bUseAlchemyAsync != 0) {
                igAdxFile_WaitForReadEnd(self);
            }
            if (self->_iBufferPos < self->_iBufferSize - 1) {
                self->_pBufferPtr = self->_pBuffer + self->_iBufferPos;
                memcpy(dest, (char *)self->_pBufferPtr, remaining);
                done += remaining;
                remaining = total - done;
            }
            self->_iBufferPos = 0;
            bufferSize = self->_iBufferSize;
            if (bufferSize < remaining) {
                remaining = bufferSize;
            }
            self->_pBufferPtr = self->_pTmpBuffer;
            self->_pTmpBuffer = self->_pBuffer;
            self->_pBuffer = self->_pBufferPtr;
            memcpy(dest + done, (char *)self->_pBufferPtr, remaining);
            done += remaining;
            self->_iBufferPos = self->_iBufferPos + remaining;
        } while (done < total);
    }
    return count;
}

int Gap__igAdxFile__vfunc_27(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_28(igAdxFile *self, const char *format, ...)
{
    return -1;
}

int Gap__igAdxFile__vfunc_29(igAdxFile *self, const char *format, ...)
{
    return -1;
}

int Gap__igAdxFile__vfunc_30(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_31(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_33(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_34(void)
{
    return 0;
}

int Gap__igAdxFile__vfunc_35(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_36(igAdxFile *self, int offset, int whence)
{
    int sector;
    int end;

    sector = offset / self->_iSectorSize;
    self->_bBufferFilled = 0;
    switch (whence) {
    case ADXF_SEEK_SET:
        self->_iSeekPosition = offset;
        FUN_002623f8(self->_adxf, sector, ADXF_SEEK_SET);
        break;
    case ADXF_SEEK_CUR:
        self->_iSeekPosition = self->_iSeekPosition + offset;
        FUN_002623f8(self->_adxf, sector, ADXF_SEEK_CUR);
        break;
    case ADXF_SEEK_END:
        end = FUN_002623f8(self->_adxf, sector, ADXF_SEEK_END);
        self->_iSeekPosition = end * self->_iSectorSize;
        break;
    }
    return -1;
}

int Gap__igAdxFile__vfunc_37(igAdxFile *self)
{
    FUN_00262510(self->_adxf);
    return self->_iSeekPosition;
}

int Gap__igAdxFile__vfunc_32(void)
{
    return -1;
}

int igAdxFile_GetFileSize(igAdxFile *self)
{
    if (self->_bIsOpen) {
        return FUN_00262540(self->_adxf) * 0x800 + 0x800;
    }
    return 0;
}
}

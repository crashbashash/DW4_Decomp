#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/igAdxFile.h"

#pragma push
#pragma readonly_strings on

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

#include "dw4/igObject.h"
#include "dw4/igMetaObject.h"
#include "dw4/igFile.h"
#include "dw4/igMemory.h"
#include "dw4/igReport.h"
#include "dw4/igAdx.h"
#include <string.h>
#include "dw4/cri/sndf.h"
#include "dw4/igResult.h"
extern "C" {
/* CRI ADXF, on the handle in `_adxf` */

int igReport_Printf(const char *format, ...);  /* prints */
int igReport_Flush(...);

unsigned char g_igAdxFile_ignoreReadModeWarning;
unsigned char g_igAdxFile_ignoreWriteWarning;
unsigned char g_igAdxFile_ignoreOpenModeWarning;
}

/* igAdxFile's own virtual function it calls on itself: open with a mode (slot 21,
 * igAdxFile_OpenWithMode).
 * ABI view only: never instantiated. */
class igAdxFileDispatchView : public igObjectDispatchView {
public:
    virtual igResult OpenWithMode(OpenMode mode);                           /* slot 21 */
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

#include "dw4/igThread.h"
#include "dw4/cri/cri_adxf.h"
extern "C" {

void igAdxFile_constructFields(igAdxFile *self, int flags)
{
    Gap__Core__igObject__constructFields(self, flags);
}

void igAdxFile_resetFields(igAdxFile *self, int flags)
{
    Gap__Core__igObject__resetFields(self, flags);
    self->_pBufferPtr = self->_pBuffer;
    self->_bBufferFilled = 0;
    self->_iBufferPos = 0;
    self->_adxf = 0;
}

void igAdxFile_userConstruct(igAdxFile *self)
{
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    self->_pBuffer = (int)Memory_AllocateAlignedWithAllocator(self->_iBufferSize, 0x40, igObject_GetAllocator(self));
    /* matching construct: hand search — the failed-allocation return folds into the epilogue, leaving the reload of
       _pBuffer; the GameCube build keeps the same compare with no branch after it */
    if (self->_pBuffer == 0) {
        return;
    }
}

int igAdxFile_GetMeta(void)
{
    return (int)g_igAdxFile_metaObject;
}

void igAdxFile_destructFields(igAdxFile *self)
{
    if (self->_pBuffer != 0) {
        Memory_FreeBufferWithAllocator((void *)self->_pBuffer, igObject_GetAllocator(self));
        self->_pBufferPtr = 0;
    }
    if (self->_pTmpBuffer != 0) {
        Memory_FreeBufferWithAllocator((void *)self->_pTmpBuffer, igObject_GetAllocator(self));
    }
}

void igAdxFile_userDestruct(igAdxFile *self)
{
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

int igAdxFile_GetReadStatus(igAdxFile *self)
{
    return ADXF_GetStat((AdxfHandle *)self->_adxf);
}

int igAdxFile_WaitForReadEnd(igAdxFile *self)
{
    while (igAdxFile_GetReadStatus(self) != ADXF_STAT_READEND) {
        if (self->_bUseAsync && self->_bUseAlchemyAsync) {
            ((SleepingThread *)g_threadManager->_threadList->_data[0])->sleep(self->_lSleepTime);
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

void igAdxFile_OpenWithMode(igResult *result, igAdxFile *self, OpenMode mode)
{
    char fileName[256];
    int answer;
    int index;
    igAdxAfsFile *entry;

    if (g_adxIopReady == 0) {
        *result = g_resultFailure;
        return;
    }
    if (self->_bIsOpen) {
        *result = g_resultSuccess;
        return;
    }
    if (mode == kDefaultOpenMode) {
        mode = (OpenMode)self->_openMode;
    }
    switch (mode) {
    case kRead:
        if (!g_igAdxFile_ignoreReadModeWarning) {
            answer = igReport_Info("Only binary read mode is supported for an igAdxFile file (\"%s\")",
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
            answer = igReport_Info("Only file reading is supported for an igAdxFile file (\"%s\")",
                                 self->_fileName);
            if (answer == kReportContinue) {
            } else if (answer == kReportIgnoreAlways) {
                g_igAdxFile_ignoreWriteWarning = 1;
            }
        }
        *result = g_resultFailure;
        return;
    default:
        if (!g_igAdxFile_ignoreOpenModeWarning) {
            answer = igReport_Info("Unrecognized file open mode");
            if (answer == kReportContinue) {
            } else if (answer == kReportIgnoreAlways) {
                g_igAdxFile_ignoreOpenModeWarning = 1;
            }
        }
        *result = g_resultFailure;
        return;
    case kReadBinary:
    open:
        index = igAdx_FindAfsFile((const char *)self->_fileName);
        if (index != -1) {
            entry = ((igAdxAfsFile **)g_adxAfsFileList->_data)[index];
            self->_adxf = (int)ADXF_OpenAfs(entry->_ptNumber, entry->_fileNumber);
        } else {
            strcpy(fileName, (const char *)self->_fileName);
            self->_adxf = (int)ADXF_Open(fileName, 0);
        }
        if (self->_adxf == 0) {
            *result = g_resultFailure;
            return;
        }
        self->_bIsOpen = 1;
        *result = g_resultSuccess;
        return;
    }
}

void igAdxFile_Close(igAdxFile *self)
{
    self->_bBufferFilled = 0;
    self->_iBufferPos = 0;
    if (self->_adxf != 0) {
        ADXF_Close((AdxfHandle *)self->_adxf);
    }
}

igAdxFile *igAdxFile_OpenFile(igAdxFile *self, const char *fileName, const char *mode)
{
    bool opened;

    igFile_SetFileName((igFile *)self, fileName); /* igAdxFile extends igFile; reflected.h derives it from igObject */
    if (strcmp(mode, "rb") == 0) {
        opened = ((igAdxFileDispatchView *)self)->OpenWithMode(kReadBinary) == g_resultSuccess;
    } else if (strcmp(mode, "r") == 0) {
        opened = ((igAdxFileDispatchView *)self)->OpenWithMode(kRead) == g_resultSuccess;
    } else {
        return 0;
    }
    return opened ? self : 0;
}

void igAdxFile_CloseFile(igAdxFile *self)
{
    ADXF_Close((AdxfHandle *)self->_adxf);
}

int igAdxFile_Read(igAdxFile *self, char *dest, int size, int count)
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
        position = ADXF_Tell((AdxfHandle *)self->_adxf);
        if (position < ADXF_GetFsizeSct((AdxfHandle *)self->_adxf)) {
            position = sectors + ADXF_Tell((AdxfHandle *)self->_adxf);
            if (ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) < position) {
                sectors = ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) - ADXF_Tell((AdxfHandle *)self->_adxf);
            }
            ADXF_ReadNw((AdxfHandle *)self->_adxf, sectors, dest);
        }
        if (self->_bUseAsync == 0 || self->_bUseAlchemyAsync != 0) {
            igAdxFile_WaitForReadEnd(self);
        }
        return count;
    }
    if (self->_bBufferFilled == 0) {
        sectors = self->_iBufferSize / self->_iSectorSize;
        position = ADXF_Tell((AdxfHandle *)self->_adxf);
        if (position < ADXF_GetFsizeSct((AdxfHandle *)self->_adxf)) {
            position = sectors + ADXF_Tell((AdxfHandle *)self->_adxf);
            if (ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) < position) {
                sectors = ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) - ADXF_Tell((AdxfHandle *)self->_adxf);
            }
            ADXF_ReadNw((AdxfHandle *)self->_adxf, sectors, (char *)self->_pBuffer);
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
            position = ADXF_Tell((AdxfHandle *)self->_adxf);
            if (position < ADXF_GetFsizeSct((AdxfHandle *)self->_adxf)) {
                position = sectors + ADXF_Tell((AdxfHandle *)self->_adxf);
                if (ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) < position) {
                    sectors = ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) - ADXF_Tell((AdxfHandle *)self->_adxf);
                }
                ADXF_ReadNw((AdxfHandle *)self->_adxf, sectors, (char *)self->_pTmpBuffer);
            } else {
                igReport_Printf("igAdxFile::3 read cancel\n");
                igReport_Flush();
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

int igAdxFile_Write(void)
{
    return -1;
}

int igAdxFile_Scanf(igAdxFile *self, const char *format, ...)
{
    return -1;
}

int igAdxFile_Printf(igAdxFile *self, const char *format, ...)
{
    return -1;
}

int igAdxFile_Flush(void)
{
    return -1;
}

int igAdxFile_GetChar(void)
{
    return -1;
}

int igAdxFile_PutChar(void)
{
    return -1;
}

int igAdxFile_GetString(void)
{
    return 0;
}

int igAdxFile_PutString(void)
{
    return -1;
}

int igAdxFile_Seek(igAdxFile *self, int offset, int whence)
{
    int sector;
    int end;

    sector = offset / self->_iSectorSize;
    self->_bBufferFilled = 0;
    switch (whence) {
    case ADXF_SEEK_SET:
        self->_iSeekPosition = offset;
        ADXF_Seek((AdxfHandle *)self->_adxf, sector, ADXF_SEEK_SET);
        break;
    case ADXF_SEEK_CUR:
        self->_iSeekPosition = self->_iSeekPosition + offset;
        ADXF_Seek((AdxfHandle *)self->_adxf, sector, ADXF_SEEK_CUR);
        break;
    case ADXF_SEEK_END:
        end = ADXF_Seek((AdxfHandle *)self->_adxf, sector, ADXF_SEEK_END);
        self->_iSeekPosition = end * self->_iSectorSize;
        break;
    }
    return -1;
}

int igAdxFile_Tell(igAdxFile *self)
{
    ADXF_Tell((AdxfHandle *)self->_adxf);
    return self->_iSeekPosition;
}

int igAdxFile_UngetChar(void)
{
    return -1;
}

int igAdxFile_GetFileSize(igAdxFile *self)
{
    if (self->_bIsOpen) {
        return ADXF_GetFsizeSct((AdxfHandle *)self->_adxf) * 0x800 + 0x800;
    }
    return 0;
}
}
#pragma pop

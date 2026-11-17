#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beSaveApiDispatchView.h"
#include "dw4/beSaveDataDeliver.h"
#include "dw4/beSvConnectCheck.h"
#include "dw4/beSaveApi.h"
#include "dw4/beSaveMemoryObj.h"
#include "dw4/beSvEndApi.h"
#include "dw4/beSvFileFindApi.h"
#include "dw4/beSvFileMakeApi.h"
#include "dw4/beSvFormatApi.h"
#include "dw4/beSvGetFreeSizeApi.h"
#include "dw4/beSvReadMediaApi.h"
#include "dw4/beSvStartApi.h"
#include "dw4/beSvUseCheckApi.h"
#include "dw4/beSvWriteMediaApi.h"
#include "dw4/igDataLists.h"
#include "dw4/igMemory.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igMetaObject.h"
#include "dw4/igObject.h"
#include <stdio.h>
#include <string.h>
#include "dw4/sony/libmc.h"
#include "dw4/igPsx2File.h"
#include "dw4/sony/libmtap.h"
#pragma push
#pragma readonly_strings on

/* The registered fields every save request shares, with the retry counter each one keeps in the
 * word the metadata leaves unlisted at +60. */
struct beSvApiWork : igObject {
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    int _connect;
    int _result;
    unsigned char _isEnd;
    int _st0;
    int _st1;
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;
};

/* beSvUseCheckApi's unlisted tail: the card type and format flag sceMcGetInfo fills. */
struct beSvUseCheckApiWork : beSvApiWork {
    int _cardType;
    int _unused68;
    int _format;
};

/* beSvGetFreeSizeApi's registered capacities plus the sceMcGetInfo outputs after them. */
struct beSvGetFreeSizeApiWork : beSvApiWork {
    int _memNeed;
    int _memCapa;
    int _fileCapa;
    int _cardType;
    int _freeKb;
    int _format;
};

/* beSvConnectCheck's unlisted tail: per-slot free size and format flag, the slot being probed and
 * the outputs of its sceMcGetInfo request. */
struct beSvConnectCheckWork : beSvApiWork {
    int _freeSizes[8];
    int _formats[8];
    int _slot;
    int _unused132;
    int _free;
    int _format;
};

/* libmc request numbers: sceMcSync reports the number of the request that finished. */
enum SceMcFuncNo {
    SCE_MC_FUNC_GET_INFO = 1,
    SCE_MC_FUNC_OPEN = 2,
    SCE_MC_FUNC_CLOSE = 3,
    SCE_MC_FUNC_SEEK = 4,
    SCE_MC_FUNC_READ = 5,
    SCE_MC_FUNC_WRITE = 6,
    SCE_MC_FUNC_FLUSH = 10,
    SCE_MC_FUNC_MKDIR = 11,
    SCE_MC_FUNC_GET_DIR = 13,
    SCE_MC_FUNC_DELETE = 15,
    SCE_MC_FUNC_FORMAT = 16
};

/* Request state per libmc request number: 1 while issued, 2 once beSvConnectCheck_Poll stores its
 * result. */
enum { SV_MC_REQUEST_ISSUED = 1, SV_MC_REQUEST_DONE = 2 };

struct CardSlot { int port; int slot; };

extern "C" void beSaveMemoryObj_userDestruct(beSaveMemoryObj *self);
extern "C" igMetaObject *beSaveMemoryObj_GetMeta(void);
extern "C" int beSvConnectCheck_ProbeSlot(int check, int slot);
extern "C" int beSvConnectCheck_ProbeSlots(int check, int onlyPresent);
extern "C" void beSvConnectCheck_Start(void);
extern "C" int beSvConnectCheck_Update(void);
extern "C" void beSvConnectCheck_Report(void);
extern "C" igMetaObject *beSvConnectCheck_GetMeta(void);
extern "C" void beSvConnectCheck_userConstruct(igObjectDispatchView *self);
extern "C" igMetaObject *beSaveApi_GetMeta(void);
extern "C" void beSvConnectCheck_userDestruct(beSvConnectCheck *self);
extern "C" igMetaObject *beSvEndApi_GetMeta(void);
extern "C" void beSvEndApi_userConstruct(igObjectDispatchView *self);
extern "C" void beSvEndApi_userDestruct(beSvEndApi *self);
extern "C" igMetaObject *beSvStartApi_GetMeta(void);
extern "C" void beSvStartApi_userConstruct(igObjectDispatchView *self);
extern "C" void beSvStartApi_userDestruct(beSvStartApi *self);
extern "C" igMetaObject *beSvGetFreeSizeApi_GetMeta(void);
extern "C" void beSvGetFreeSizeApi_userConstruct(igObjectDispatchView *self);
extern "C" void beSvGetFreeSizeApi_userDestruct(beSvGetFreeSizeApi *self);
extern "C" igMetaObject *beSvWriteMediaApi_GetMeta(void);
extern "C" void beSvWriteMediaApi_userConstruct(igObjectDispatchView *self);
extern "C" igMetaObject *beSvReadMediaApi_GetMeta(void);
extern "C" void beSvReadMediaApi_userConstruct(igObjectDispatchView *self);
extern "C" igMetaObject *beSvUseCheckApi_GetMeta(void);
extern "C" void beSvUseCheckApi_userDestruct(beSvUseCheckApi *self);
extern "C" void beSaveApi_userConstruct(igObjectDispatchView *self);
extern "C" igMetaObject *beSvFormatApi_GetMeta(void);
extern "C" void beSvFormatApi_userDestruct(beSvFormatApi *self);
extern "C" igMetaObject *beSvFileFindApi_GetMeta(void);
extern "C" void beSvFileFindApi_userDestruct(beSvFileFindApi *self);
extern "C" igMetaObject *beSvFileMakeApi_GetMeta(void);
extern "C" void beSvFileMakeApi_userConstruct(igObjectDispatchView *self);
extern "C" void beSaveApi_userDestruct(beSaveApi *self);
extern "C" void beSaveMemoryObj_userConstruct(igObjectDispatchView *self);
extern "C" void beSaveMemoryObj_Allocate(beSaveMemoryObj *self, int size, int alignment);
extern "C" void beSaveMemoryObj_Free(beSaveMemoryObj *self);
extern "C" void beSvFileMakeApi_Report(beSvFileMakeApi *self, beSvDeliver *deliver);
extern "C" unsigned char g_svCardBusy;
extern "C" void beSvFileFindApi_Start(beSvApiWork *self, beSvDeliver *deliver);
extern "C" void beSvFileFindApi_Report(beSvFileFindApi *self, beSvDeliver *deliver);
extern "C" void beSvFormatApi_Start(beSvApiWork *self, beSvDeliver *deliver);
extern "C" int g_svMcRequestState[24];
extern "C" int g_svMcRequestResult[24];
extern "C" unsigned char g_svConnectCheckPending;
extern "C" unsigned char beSvFormatApi_Update(beSvApiWork *self);
extern "C" void beSvFormatApi_Report(beSvFormatApi *self, beSvDeliver *deliver);
extern "C" void beSvUseCheckApi_Start(beSvApiWork *self, beSvDeliver *deliver);
extern "C" unsigned char beSvUseCheckApi_Update(beSvUseCheckApiWork *self);
extern "C" void beSvUseCheckApi_Report(beSvUseCheckApi *self, beSvDeliver *deliver);
extern "C" void beSvReadMediaApi_Report(beSvReadMediaApi *self, beSvDeliver *deliver);
/* beSvWriteMediaApi with the retry counter at +60 and the image pass at +72, which the registered
 * metadata does not list. */
typedef struct beSvWriteMediaApiWork {
    int _vtable;
    unsigned int _refCount;
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    char _pad17[3];
    int _connect;
    int _result;
    unsigned char _isEnd;
    char _pad29[3];
    int _phase;             /* _st0 */
    int _step;              /* _st1 */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;
    int _nowGamedata;
    beSaveMemoryObj *_saveWork;
    int _imagePass;
} beSvWriteMediaApiWork;
extern "C" beSvPlatDataPS2 *g_svPlatformData[1];
extern "C" CardSlot g_svCardSlots[8];
extern "C" int g_svSaveFd[1];
extern "C" int beSvWriteMediaApi_Update(beSvWriteMediaApiWork *self);
extern "C" void beSvWriteMediaApi_Report(beSvWriteMediaApi *self, beSvDeliver *deliver);
extern "C" void beSvGetFreeSizeApi_Start(beSvApiWork *self, beSvDeliver *deliver);
extern "C" unsigned char beSvGetFreeSizeApi_Update(beSvGetFreeSizeApiWork *self);
extern "C" void beSvGetFreeSizeApi_Report(beSvGetFreeSizeApiWork *self, beSvDeliver *deliver);
extern "C" int g_svConnectMax[1];
extern "C" int g_svSaveVersion[1];
extern "C" char g_svMultitapState;
extern "C" unsigned char g_svMcModulesLoaded;
extern "C" char g_svMultitapChanged;
extern "C" void beSvStartApi_Start(beSvApiWork *self, beSvDeliver *deliver);
extern "C" int beSvStartApi_Update(beSvStartApi *self);
extern "C" void beSvStartApi_Report(beSvStartApi *self, beSvDeliver *deliver);
extern "C" void beSvEndApi_Start(beSvEndApi *self);
extern "C" int beSvEndApi_Update(beSvEndApi *self);
extern "C" void beSvEndApi_Report(beSvEndApi *self, beSvDeliver *deliver);
extern "C" int g_svSlotPresent[8];
extern "C" int g_svMultitapPollCount[1];
extern "C" int g_svMultitapPollSuspended[1];
extern "C" int g_svSlotAbsent[1];
extern "C" void beSvWriteMediaApi_userDestruct(beSvWriteMediaApi *self);
extern "C" void beSvReadMediaApi_userDestruct(beSvReadMediaApi *self);
extern "C" void beSvFileMakeApi_userDestruct(beSvFileMakeApi *self);

/* The PS2 icon.sys record (libmc's sceMcIconSys) the save writes next to the data. */
struct sceMcIconSys {
    unsigned char Head[4];
    unsigned short rsv1;
    unsigned short OffsLF;
    unsigned int rsv2;
    unsigned int TransRate;
    int BgColor[4][4];
    float LightDir[3][4];
    float LightColor[3][4];
    float Ambient[4];
    char TitleName[68];
    char FnameView[64];
    char FnameCopy[64];
    char FnameDel[64];
    unsigned char zero2[512];
};

/* beSvFileMakeApi with the unlisted words after its registered fields: the retry counter at +60,
 * the directory listing count and file index at +76 and +80, and the icon.sys record at +84. */
struct beSvFileMakeApiWork : igObject {
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    int _connect;
    int _result;
    unsigned char _isEnd;
    int _phase;             /* _st0 */
    int _step;              /* _st1 */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;
    int _earlyGamedata;
    beSaveMemoryObj *_saveWork;
    int _imagePass;
    int _entryCount;
    int _fileIndex;
    sceMcIconSys _iconSys;
};


/* beSvFileFindApi with the retry counter at +60 and the file being looked for at +68, which the
 * registered metadata does not list: 0 icon.sys, 1..3 the icon files, 4 the save file. */
struct beSvFileFindApiWork : igObject {
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    int _connect;
    int _result;
    unsigned char _isEnd;
    int _phase;             /* _st0 */
    int _step;              /* _st1 */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;
    int _unused64;
    int _stage;
};

extern "C" int beSvFileMakeApi_Update(beSvFileMakeApiWork *self);
extern "C" sceMcTblGetDir g_svDirEntries[8];
extern "C" int beSvFileFindApi_Update(beSvFileFindApiWork *self);

/* beSvReadMediaApi with the retry counter at +60 and the buffer pass at +84, which the registered
 * metadata does not list. */
struct beSvReadMediaApiWork : igObject {
    int _dummyCount;
    int _orderType;
    unsigned char _isConAllChk;
    int _connect;
    int _result;
    unsigned char _isEnd;
    int _phase;             /* _st0 */
    int _step;              /* _st1 */
    int getPhase() const { return _phase; }
    int getStep() const { return _step; }
    int _st2;
    int _st3;
    int _imageWork;
    int _mountWork;
    int _iconWork;
    int _retryCount;
    int _gameData;
    int _outputGamedata;
    int _oneSvDataSize;
    igObject *_lodeData;
    int _loadWorkList;
    int _readPass;
};

extern "C" void beSvReadMediaApi_Start(beSvReadMediaApiWork *self, beSvDeliver *deliver);
extern "C" int beSvReadMediaApi_Update(beSvReadMediaApiWork *self);
extern "C" void beSvFileMakeApi_Start(beSvFileMakeApiWork *self, beSvDeliver *deliver);
extern "C" void beSvWriteMediaApi_Start(beSvWriteMediaApiWork *self, beSvDeliver *deliver);

void beSaveDataDeliver_AllocateData(beSaveDataDeliver *deliver, int size) {
    int own;
    int allocator;
    deliver->_size = size;
    own = (int)igObject_GetAllocator(deliver);
    if (g_useOwnerAllocator != 0) {
        allocator = own;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    deliver->_data = (int)(Memory_AllocateBufferDirect(size, (igMemoryPoolView *)allocator));
}

void beSaveDataDeliver_FreeData(beSaveDataDeliver *deliver) {
    int allocator;

    if (deliver->_data != 0) {
        allocator = (int)igObject_GetAllocator(deliver);
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        Memory_FreeBufferWithAllocator((void *)deliver->_data, (igMemoryPoolView *)allocator);
    }
    deliver->_data = 0;
    deliver->_size = 0;
}

void beSaveMemoryObj_Allocate(beSaveMemoryObj *self, int size, int alignment) {
    int own, allocator;

    if (alignment == 0) {
        own = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        self->_mem = (int)(Memory_AllocateBufferDirect(size, (igMemoryPoolView *)allocator));
    } else {
        own = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        self->_mem = (int)(Memory_AllocateAlignedWithAllocator(size, alignment & 0xFFFF, (igMemoryPoolView *)allocator));
    }
    memset((void *)self->_mem, 0, size);
}

void beSaveMemoryObj_Free(beSaveMemoryObj *self) {
    igMemoryPoolView *allocator;

    if (self->_mem != 0) {
        allocator = igObject_GetAllocator((igObject *)self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        Memory_FreeBufferWithAllocator((void *)self->_mem, allocator);
    }
    self->_mem = 0;
}

void beSaveMemoryObj_userDestruct(beSaveMemoryObj *self) {
    beSaveMemoryObj_Free(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSaveMemoryObj_GetMeta(void)
{
    return g_beSaveMemoryObj_metaObject;
}

extern "C" int beSaveApi_Checksum(beSvApiWork *self, int *data, int size);

/* Sums the words that follow the leading checksum word. */
int beSaveApi_Checksum(beSvApiWork *self, int *data, int size) {
    int sum = 0;
    size = size - sizeof(int);
    int count = size / sizeof(int);
    data++;
    for (int i = 0; i < count; i++) {
        sum += *data++;
    }
    return sum;
}

/* Starts a save: builds the save image in a new beSaveMemoryObj of the platform's data size: the checksum word,
 * the save version, then the game data. */
void beSvFileMakeApi_Start(beSvFileMakeApiWork *self, beSvDeliver *deliver) {
    beSvPlatDataPS2 *platform;
    int own;
    int allocator;
    igObject *old;
    int *image;
    int *field;
    beSaveDataDeliver *gameData;

    platform = (beSvPlatDataPS2 *)deliver->_platformData;
    g_svPlatformData[0] = platform;
    self->_connect = deliver->_targetConnect;
    self->_isEnd = 0;
    self->_result = 1;
    own = (int)igObject_GetAllocator(self);
    allocator = g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    old = self->_saveWork;
    IG_OBJECT_RELEASE(old);
    self->_saveWork = beSaveMemoryObj_CreateInstance(allocator);
    beSaveMemoryObj_Allocate(self->_saveWork, platform->_dataSize, 0);
    image = (int *)self->_saveWork->_mem;
    field = image;
    field++;
    *field++ = g_svSaveVersion[0];
    gameData = (beSaveDataDeliver *)deliver->_gameData;
    memcpy(field, (void *)gameData->_data, gameData->_size);
    image[0] = ((beSaveApiDispatchView *)self)->checksum(image, platform->_dataSize);
    self->_imagePass = 0;
    g_svCardBusy = 1;
}

#define SV_NEXT_STEP(self)  ((self)->_step = (self)->getStep() + 1, (self)->_st3 = 0, (self)->_st2 = 0)
#define SV_FIRST_STEP(self) ((self)->_st3 = 0, (self)->_st2 = 0, (self)->_step = 0)
#define SV_RETRY_STEP(self) ((self)->_step = 1, (self)->_st3 = 0, (self)->_st2 = 0)
/* True while a failed request may be issued again: three attempts in all.
 * matching construct: variant trials — the test is a flag compared with 1 (`== TRUE`); a plain `< 3` branches on the compare */
#define SV_MAY_RETRY(self)  (((self)->_retryCount < 3) == 1)
#define SV_NEXT_SUB(self)      ((self)->_st2 = (self)->_st2 + 1, (self)->_st3 = 0)
#define SV_RETRY_SUB(self, n)  ((self)->_st2 = (n), (self)->_st3 = 0)
#define SV_FINISH(self, code)  ((self)->_result = (code), (self)->_isEnd = 1)

static inline beSvPs2McImage128k *platformImage(beSvPlatDataPS2 *platform, int index) {
    return ((beSvPs2McImage128k **)((igObjectList *)platform->_image)->_data)[index];
}


/* Steps to the next icon file; false once every icon has been written. */
static inline int moreIcons(beSvFileMakeApiWork *self, int count) {
    int next = self->_fileIndex + 1;
    self->_fileIndex = next;
    return next < count;
}

/* Memory-card save-creation state machine, polled once per frame. _phase selects the phase, _step
 * the step inside it, _st2 the sub-step of a step that issues two requests. Every request is issued,
 * then polled for its result and retried up to three times; a failure past that ends the machine with
 * _result = 3 (card unusable) or 12. Phases: 0 makes the save directory and deletes what a previous
 * save left in it, 1-4 create each icon file (open, write, close), 5-7 the save file (open, write both
 * passes, close), 8-11 icon.sys (open, build the record, write, close), 12 lists the directory to
 * confirm it (_result = 2). */
int beSvFileMakeApi_Update(beSvFileMakeApiWork *self) {
    beSvPlatDataPS2 *platform;
    int i;
    int res;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (g_svConnectCheckPending == 1) {
        return 0;
    }
    platform = g_svPlatformData[0];
    switch (self->getPhase()) {
    case 0:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            switch (self->_st2) {
            case 0: {
                char path[256];
                sprintf(path, "/%s", platform->_dirName);
                if (sceMcMkdir(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path) >= 0) {
                    g_svMcRequestState[SCE_MC_FUNC_MKDIR] = SV_MC_REQUEST_ISSUED;
                    SV_NEXT_SUB(self);
                }
                break;
            }
            case 1:
                if (g_svMcRequestState[SCE_MC_FUNC_MKDIR] == SV_MC_REQUEST_ISSUED) {
                    return 0;
                }
                res = g_svMcRequestResult[SCE_MC_FUNC_MKDIR];
                if (res >= 0) {
                    self->_retryCount = 0;
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                } else {
                    self->_retryCount = self->_retryCount + 1;
                    if (SV_MAY_RETRY(self)) {
                        SV_RETRY_SUB(self, 0);
                    } else {
                        switch (res) {
                        case -4:
                            SV_NEXT_STEP(self);
                            break;
                        case -2:
                        case -3:
                        case -5:
                            SV_FINISH(self, 3);
                            break;
                        default:
                            SV_FINISH(self, 12);
                            break;
                        }
                    }
                }
                break;
            }
            break;
        case 2:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 3:
            switch (self->_st2) {
            case 0: {
                char path[256];
                sprintf(path, "/%s/*", platform->_dirName);
                if (sceMcGetDir(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 0, 7, g_svDirEntries) >= 0) {
                    g_svMcRequestState[SCE_MC_FUNC_GET_DIR] = SV_MC_REQUEST_ISSUED;
                    SV_NEXT_SUB(self);
                }
                break;
            }
            case 1:
                if (g_svMcRequestState[SCE_MC_FUNC_GET_DIR] == SV_MC_REQUEST_ISSUED) {
                    return 0;
                }
                res = g_svMcRequestResult[SCE_MC_FUNC_GET_DIR];
                if (res >= 0) {
                    self->_entryCount = res;
                    if (self->_entryCount > 2) {    /* more than "." and ".." */
                        SV_NEXT_STEP(self);
                    } else {
                        self->_phase = self->_phase + 1;
                        SV_FIRST_STEP(self);
                    }
                } else {
                    self->_retryCount = self->_retryCount + 1;
                    if (SV_MAY_RETRY(self)) {
                        SV_RETRY_SUB(self, 0);
                    } else {
                        switch (res) {
                        case -2:
                        case -4:
                        case -5:
                        case -6:
                            SV_FINISH(self, 3);
                            break;
                        default:
                            SV_FINISH(self, 12);
                            break;
                        }
                    }
                }
                break;
            }
            break;
        case 4:
            self->_fileIndex = 2;
            SV_NEXT_STEP(self);
            /* fall through */
        case 5:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 6:
            switch (self->_st2) {
            case 0: {
                char path[256];
                sprintf(path, "/%s/%s", platform->_dirName, g_svDirEntries[self->_fileIndex].EntryName);
                if (sceMcDelete(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path) >= 0) {
                    g_svMcRequestState[SCE_MC_FUNC_DELETE] = SV_MC_REQUEST_ISSUED;
                    SV_NEXT_SUB(self);
                }
                break;
            }
            case 1:
                if (g_svMcRequestState[SCE_MC_FUNC_DELETE] == SV_MC_REQUEST_ISSUED) {
                    return 0;
                }
                res = g_svMcRequestResult[SCE_MC_FUNC_DELETE];
                if (res >= 0) {
                    if (++self->_fileIndex < self->_entryCount) {
                        self->_step = self->getStep() - 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    } else {
                        self->_phase = 1;
                        SV_FIRST_STEP(self);
                    }
                } else {
                    self->_retryCount = self->_retryCount + 1;
                    if (SV_MAY_RETRY(self)) {
                        SV_RETRY_SUB(self, 0);
                    } else {
                        switch (res) {
                        case 0:
                        case -2:
                        case -4:
                        case -5:
                        case -6:
                            SV_FINISH(self, 3);
                            break;
                        default:
                            SV_FINISH(self, 12);
                            break;
                        }
                    }
                }
                break;
            }
            break;
        }
        break;
    case 1:
        self->_fileIndex = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 2:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1: {
            char path[256];
            const char *name;
            switch (self->_fileIndex) {
            default:
                name = (const char *)platform->_fnameIcon0;
                break;
            case 1:
                name = (const char *)platform->_fnameIcon1;
                break;
            case 2:
                name = (const char *)platform->_fnameIcon2;
                break;
            }
            sprintf(path, "/%s/%s", platform->_dirName, name);
            if (sceMcOpen(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 514) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_OPEN] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        }
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_OPEN] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_OPEN];
            if (res >= 0) {
                g_svSaveFd[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
                self->_retryCount = 0;
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 3:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcWrite(g_svSaveFd[0], (void *)platformImage(platform, self->_fileIndex)->_data, platformImage(platform, self->_fileIndex)->_dataSize) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_WRITE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_WRITE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_WRITE];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 4:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcClose(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_CLOSE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_CLOSE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_CLOSE];
            if (res >= 0) {
                if (!moreIcons(self, platform->_iconCount)) {
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                } else {
                    self->_phase = 2;
                    SV_FIRST_STEP(self);
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case 0:
                    case -2:
                    case -4:
                    case -5:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 5:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1: {
            char path[256];
            sprintf(path, "/%s/%s", platform->_dirName, platform->_dirName);
            if (sceMcOpen(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 514) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_OPEN] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        }
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_OPEN] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_OPEN];
            if (res >= 0) {
                g_svSaveFd[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->_step) {
        case 0:
            switch (self->_st2) {
            case 0:
                self->_retryCount = 0;
                SV_NEXT_SUB(self);
                break;
            case 1:
                if (sceMcSeek(g_svSaveFd[0], platform->_dataOffSet[self->_imagePass], 0) >= 0) {
                    g_svMcRequestState[SCE_MC_FUNC_SEEK] = SV_MC_REQUEST_ISSUED;
                    SV_NEXT_SUB(self);
                }
                break;
            case 2:
                if (g_svMcRequestState[SCE_MC_FUNC_SEEK] == SV_MC_REQUEST_ISSUED) {
                    return 0;
                }
                res = g_svMcRequestResult[SCE_MC_FUNC_SEEK];
                if (res >= 0) {
                    SV_NEXT_STEP(self);
                } else {
                    self->_retryCount = self->_retryCount + 1;
                    if (SV_MAY_RETRY(self)) {
                        SV_RETRY_SUB(self, 1);
                    } else {
                        switch (res) {
                        case -2:
                        case -4:
                        case -5:
                            SV_FINISH(self, 3);
                            break;
                        default:
                            SV_FINISH(self, 12);
                            break;
                        }
                    }
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                self->_retryCount = 0;
                SV_NEXT_SUB(self);
                break;
            case 1:
                if (sceMcWrite(g_svSaveFd[0], (void *)self->_saveWork->_mem, platform->_dataSize) >= 0) {
                    g_svMcRequestState[SCE_MC_FUNC_WRITE] = SV_MC_REQUEST_ISSUED;
                    SV_NEXT_SUB(self);
                }
                break;
            case 2:
                if (g_svMcRequestState[SCE_MC_FUNC_WRITE] == SV_MC_REQUEST_ISSUED) {
                    return 0;
                }
                res = g_svMcRequestResult[SCE_MC_FUNC_WRITE];
                if (res >= 0) {
                    if (self->_imagePass == 0) {
                        self->_imagePass = 1;
                        self->_step = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    } else {
                        self->_phase = self->_phase + 1;
                        SV_FIRST_STEP(self);
                    }
                } else {
                    self->_retryCount = self->_retryCount + 1;
                    if (SV_MAY_RETRY(self)) {
                        SV_RETRY_SUB(self, 1);
                    } else {
                        switch (res) {
                        case -2:
                        case -4:
                        case -5:
                        case -8:
                            SV_FINISH(self, 3);
                            break;
                        default:
                            SV_FINISH(self, 12);
                            break;
                        }
                    }
                }
                break;
            }
            break;
        }
        break;
    case 7:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcClose(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_CLOSE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_CLOSE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_CLOSE];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 8:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1: {
            char path[256];
            sprintf(path, "/%s/icon.sys", platform->_dirName);
            if (sceMcOpen(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 514) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_OPEN] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        }
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_OPEN] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_OPEN];
            if (res >= 0) {
                g_svSaveFd[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 9:
        self->_iconSys.Head[0] = 'P';
        self->_iconSys.Head[1] = 'S';
        self->_iconSys.Head[2] = '2';
        self->_iconSys.Head[3] = 'D';
        self->_iconSys.rsv1 = 0;
        self->_iconSys.OffsLF = platform->_offsLF;
        self->_iconSys.rsv2 = 0;
        self->_iconSys.TransRate = platform->_transRate;
        for (i = 0; i < 4; i++) {
            self->_iconSys.BgColor[0][i] = platform->_bgColor0[i];
        }
        for (i = 0; i < 4; i++) {
            self->_iconSys.BgColor[1][i] = platform->_bgColor1[i];
        }
        for (i = 0; i < 4; i++) {
            self->_iconSys.BgColor[2][i] = platform->_bgColor2[i];
        }
        for (i = 0; i < 4; i++) {
            self->_iconSys.BgColor[3][i] = platform->_bgColor3[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightDir[0][i] = platform->_lightDir0[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightDir[1][i] = platform->_lightDir1[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightDir[2][i] = platform->_lightDir2[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightColor[0][i] = platform->_lightColor0[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightColor[1][i] = platform->_lightColor1[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.LightColor[2][i] = platform->_lightColor2[i];
        }
        for (i = 0; i < 3; i++) {
            self->_iconSys.Ambient[i] = platform->_ambient[i];
        }
        strcpy(self->_iconSys.TitleName, (const char *)platform->_title);
        strcpy(self->_iconSys.FnameView, (const char *)platform->_fnameIcon0);
        strcpy(self->_iconSys.FnameCopy, (const char *)platform->_fnameIcon1);
        strcpy(self->_iconSys.FnameDel, (const char *)platform->_fnameIcon2);
        memset(self->_iconSys.zero2, 0, sizeof(self->_iconSys.zero2));
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 10:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcWrite(g_svSaveFd[0], &self->_iconSys, sizeof(sceMcIconSys)) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_WRITE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_WRITE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_WRITE];
            if (res >= 0) {
                char buffer[256];
                /* Shift-JIS "Icon Sys he no kakikomi %d baito": "wrote %d bytes to icon.sys" */
                sprintf(buffer, "Icon Sys \x82\xd6\x82\xcc\x8f\x91\x82\xab\x8d\x9e\x82\xdd %d \x83o\x83" "C\x83g\n", res);
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -8:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 11:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcClose(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_CLOSE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_CLOSE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_CLOSE];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 12:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1: {
            char path[256];
            sprintf(path, "/%s/*", platform->_dirName);
            if (sceMcGetDir(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 0, 7, g_svDirEntries) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_GET_DIR] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        }
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_GET_DIR] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_GET_DIR];
            if (res >= 0) {
                SV_FINISH(self, 2);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -6:
                        SV_FINISH(self, 3);
                        break;
                    default:
                        SV_FINISH(self, 12);
                        break;
                    }
                }
            }
            break;
        }
        break;
    }
    if (self->_isEnd != 0) {
        beSaveMemoryObj_Free(self->_saveWork);
        g_svCardBusy = 0;
    }
    return self->_isEnd;
}

void beSvFileMakeApi_Report(beSvFileMakeApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void beSvFileFindApi_Start(beSvApiWork *self, beSvDeliver *deliver) {
    int target;

    target = deliver->_targetConnect;
    if (target == -1) {
        self->_connect = 0;
        self->_isConAllChk = 1;
    } else {
        self->_connect = target;
        self->_isConAllChk = 0;
    }
    self->_isEnd = 0;
    self->_result = 1;
    g_svPlatformData[0] = (beSvPlatDataPS2 *)deliver->_platformData;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

/* Looks for the save on the card in slot _connect: lists the save directory and checks that icon.sys,
 * the icon files and the save file are all in it, one listing per file (_stage). A listing that fails
 * three times ends the search with _result = 4 (not found) for the codes below, or 12 otherwise; a
 * missing file is _result = 4, the save file present is _result = 2. When every card is being searched
 * (_isConAllChk) a miss restarts the search on the next slot (up to 2, or 5 with a multitap). */
int beSvFileFindApi_Update(beSvFileFindApiWork *self) {
    char path[256];
    beSvPlatDataPS2 *platform;
    int res;
    unsigned char found;
    int i;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (g_svConnectCheckPending == 1) {
        return 0;
    }
    platform = g_svPlatformData[0];
    switch (self->getPhase()) {
    case 0:
        self->_stage = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 1:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            switch (self->_stage) {
            default:
                sprintf(path, "/%s/icon.sys", platform->_dirName);
                break;
            case 1:
                sprintf(path, "/%s/%s", platform->_dirName, platform->_fnameIcon0);
                break;
            case 2:
                sprintf(path, "/%s/%s", platform->_dirName, platform->_fnameIcon1);
                break;
            case 3:
                sprintf(path, "/%s/%s", platform->_dirName, platform->_fnameIcon2);
                break;
            case 4:
                sprintf(path, "/%s/%s", platform->_dirName, platform->_dirName);
                break;
            }
            if (sceMcGetDir(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 0, 7, g_svDirEntries) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_GET_DIR] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_GET_DIR] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_GET_DIR];
            if (res >= 0) {
                if (res < 8) {
                    found = 0;
                    for (i = 0; i < res; i++) {
                        switch (self->_stage) {
                        case 0:
                            if (strcmp("icon.sys", (const char *)g_svDirEntries[i].EntryName) == 0) {
                                self->_stage = 1;
                                SV_RETRY_STEP(self);
                                found = 1;
                            }
                            break;
                        case 1:
                            if (strcmp((const char *)platform->_fnameIcon0, (const char *)g_svDirEntries[i].EntryName) == 0) {
                                if (platform->_iconCount >= 3) {
                                    self->_stage = 2;
                                    SV_RETRY_STEP(self);
                                } else {
                                    self->_stage = 4;
                                    SV_RETRY_STEP(self);
                                }
                                found = 1;
                            }
                            break;
                        case 2:
                            if (strcmp((const char *)platform->_fnameIcon1, (const char *)g_svDirEntries[i].EntryName) == 0) {
                                self->_stage = 3;
                                found = 1;
                                SV_RETRY_STEP(self);
                            }
                            break;
                        case 3:
                            if (strcmp((const char *)platform->_fnameIcon2, (const char *)g_svDirEntries[i].EntryName) == 0) {
                                self->_stage = 4;
                                found = 1;
                                SV_RETRY_STEP(self);
                            }
                            break;
                        case 4:
                            if (strcmp((const char *)platform->_dirName, (const char *)g_svDirEntries[i].EntryName) == 0) {
                                self->_result = 2;
                                found = 1;
                                self->_isEnd = 1;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        self->_result = 4;
                        self->_isEnd = 1;
                    }
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -6:
                    case -4:
                        self->_result = 4;
                        self->_isEnd = 1;
                        break;
                    case -5:
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    }
    if (self->_isConAllChk != 0 && self->_isEnd != 0 && self->_result != 2) {
        int connectMax = g_svMultitapState == 1 ? 5 : 2;
        self->_connect = self->_connect + 1;
        if (self->_connect < connectMax) {
            self->_isEnd = 0;
            self->_result = 1;
            self->_phase = 0;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_step = 0;
        }
    }
    if (self->_isEnd != 0) {
        g_svCardBusy = 0;
    }
    return self->_isEnd;
}

void beSvFileFindApi_Report(beSvFileFindApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void beSvFormatApi_Start(beSvApiWork *self, beSvDeliver *deliver) {
    self->_isEnd = 0;
    self->_connect = deliver->_targetConnect;
    self->_result = 1;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

unsigned char beSvFormatApi_Update(beSvApiWork *self) {
    int connect;
    int res;
    unsigned char retry;
    if (self->_isEnd != 0) return 1;
    if (g_svConnectCheckPending == 1) return 0;
    switch (self->_st0) {
    case 0:
        self->_retryCount = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        break;
    case 1:
        connect = self->_connect;
        if (sceMcFormat(g_svCardSlots[connect].port, g_svCardSlots[connect].slot) >= 0) {
            g_svMcRequestState[SCE_MC_FUNC_FORMAT] = SV_MC_REQUEST_ISSUED;
            self->_st0 = self->_st0 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st1 = 0;
        }
        break;
    case 2:
        if (g_svMcRequestState[SCE_MC_FUNC_FORMAT] == SV_MC_REQUEST_ISSUED) return 0;
        res = g_svMcRequestResult[SCE_MC_FUNC_FORMAT];
        if (res >= 0) {
            self->_isEnd = 1;
            self->_result = 2;
        } else {
            self->_retryCount = self->_retryCount + 1;
            retry = self->_retryCount < 3;
            if (retry == 1) {
                self->_st0 = 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            } else {
                switch (res) {
                case -5:
                    self->_result = 12;
                    self->_isEnd = 1;
                    break;
                default:
                    self->_result = 12;
                    self->_isEnd = 1;
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    if (self->_isEnd != 0) g_svCardBusy = 0;
    return self->_isEnd;
}

void beSvFormatApi_Report(beSvFormatApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void beSvUseCheckApi_Start(beSvApiWork *self, beSvDeliver *deliver) {
    self->_connect = deliver->_targetConnect;
    self->_isEnd = 0;
    self->_result = 1;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

unsigned char beSvUseCheckApi_Update(beSvUseCheckApiWork *self) {
    int connect;
    int res;
    unsigned char retry;
    if (self->_isEnd != 0) return 1;
    if (g_svConnectCheckPending == 1) return 0;
    switch (self->_st0) {
    case 0:
        self->_retryCount = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        break;
    case 1:
        connect = self->_connect;
        if (sceMcGetInfo(g_svCardSlots[connect].port, g_svCardSlots[connect].slot, &self->_cardType, 0, &self->_format) >= 0) {
            g_svMcRequestState[SCE_MC_FUNC_GET_INFO] = SV_MC_REQUEST_ISSUED;
            self->_st0 = self->_st0 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st1 = 0;
        }
        break;
    case 2:
        if (g_svMcRequestState[SCE_MC_FUNC_GET_INFO] == SV_MC_REQUEST_ISSUED) return 0;
        res = g_svMcRequestResult[SCE_MC_FUNC_GET_INFO];
        if (res >= 0) {
            switch (self->_cardType) {
            case 2:
                if (self->_format == 1) {
                    self->_result = 2;
                } else {
                    self->_result = 7;
                }
                break;
            case 0:
            case 1:
            case 3:
                self->_result = 12;
                break;
            }
            self->_isEnd = 1;
        } else {
            self->_retryCount = self->_retryCount + 1;
            retry = self->_retryCount < 3;
            if (retry == 1) {
                self->_st0 = 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            } else {
                switch (res) {
                case -5:
                    self->_result = 5;
                    break;
                case -1:
                case -2:
                default:
                    self->_result = 12;
                    break;
                }
                self->_isEnd = 1;
            }
        }
        break;
    default:
        break;
    }
    if (self->_isEnd != 0) g_svCardBusy = 0;
    return self->_isEnd;
}

void beSvUseCheckApi_Report(beSvUseCheckApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

/* Starts a read: keeps the game data to fill and queues two save-sized buffers for the passes. */
void beSvReadMediaApi_Start(beSvReadMediaApiWork *self, beSvDeliver *deliver) {
    beSvPlatDataPS2 *platform;
    igObject *gameData;
    igObject *old;
    int i;
    int own;
    int allocator;

    platform = (beSvPlatDataPS2 *)deliver->_platformData;
    self->_connect = deliver->_targetConnect;
    gameData = (igObject *)deliver->_gameData;
    if (gameData != 0) {
        gameData->_refCount = gameData->_refCount + 1;
    }
    old = self->_lodeData;
    IG_OBJECT_RELEASE(old);
    self->_lodeData = gameData;
    self->_gameData = deliver->_gameData;
    self->_isEnd = 0;
    self->_result = 1;
    g_svPlatformData[0] = (beSvPlatDataPS2 *)deliver->_platformData;
    for (i = 0; i < 2; i++) {
        own = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<beSaveMemoryObj> buffer(beSaveMemoryObj_CreateInstance(allocator));
        beSaveMemoryObj_Allocate(buffer, platform->_dataSize, 0);
        ObjectList_AppendRetained((igObjectList *)self->_loadWorkList, buffer);
    }
    self->_phase = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_step = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

static inline beSaveMemoryObj *loadBuffer(beSvReadMediaApiWork *self, int index) {
    return ((beSaveMemoryObj **)((igObjectList *)self->_loadWorkList)->_data)[index];
}

/* Memory-card read state machine, the mirror of beSvWriteMediaApi's: phase 0 opens the save file
 * read-only, 1 resets the pass, 2 seeks to the pass's data offset, 3 reads the save-sized buffer,
 * 4 closes, and 5 checks both copies against their checksum and copies the first intact one into
 * the game data (_result = 2; 8 when neither is intact). A request that fails three times ends the
 * machine with _result = 4 (no save file) or 3 (card unusable) for the codes listed per phase, or
 * 12 for any other. */
int beSvReadMediaApi_Update(beSvReadMediaApiWork *self) {
    char path[256];
    int res;
    beSvPlatDataPS2 *platform;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (g_svConnectCheckPending == 1) {
        return 0;
    }
    platform = g_svPlatformData[0];
    switch (self->getPhase()) {
    case 0:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            sprintf(path, "/%s/%s", platform->_dirName, platform->_dirName);
            if (sceMcOpen(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 1) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_OPEN] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_OPEN] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_OPEN];
            if (res >= 0) {
                g_svSaveFd[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        self->_result = 4;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 1:
        self->_readPass = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 2:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcSeek(g_svSaveFd[0], platform->_dataOffSet[self->_readPass], 0) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_SEEK] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_SEEK] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_SEEK];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 3:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcRead(g_svSaveFd[0], (void *)loadBuffer(self, self->_readPass)->_mem, platform->_dataSize) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_READ] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_READ] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_READ];
            if (res >= 0) {
                if (self->_readPass == 0) {
                    self->_readPass = 1;
                    self->_phase = 2;
                    SV_FIRST_STEP(self);
                } else {
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 4:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcClose(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_CLOSE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_CLOSE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_CLOSE];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 5: {
        int stored;
        int i;
        int *image;
        bool intact;
        beSaveDataDeliver *gameData;
        int j;
        intact = false;
        for (i = 0; i < 2; i++) {
            int actual;
            image = (int *)loadBuffer(self, i)->_mem;
            stored = image[0];
            image[1] = g_svSaveVersion[0];
            actual = ((beSaveApiDispatchView *)self)->checksum(image, platform->_dataSize);
            if (actual == stored) {
                gameData = (beSaveDataDeliver *)self->_gameData;
                image++;    /* past the checksum */
                image++;    /* past the save version */
                memcpy((void *)gameData->_data, image, gameData->_size);
                self->_result = 2;
                intact = true;
                break;
            }
        }
        for (j = 0; j < 2; j++) {
            ((beSaveApiDispatchView *)self)->checksum((int *)loadBuffer(self, j)->_mem, platform->_dataSize);
        }
        if (!intact) {
            self->_result = 8;
        }
        self->_isEnd = 1;
        break;
    }
    }
    if (self->_isEnd != 0) {
        int i;
        for (i = 0; i < 2; i++) {
            beSaveMemoryObj_Free(loadBuffer(self, i));
        }
        g_svCardBusy = 0;
    }
    return self->_isEnd;
}

void beSvReadMediaApi_Report(beSvReadMediaApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

/* Starts a write: builds the save image like beSvFileMakeApi_Start, in a 32-byte aligned buffer, and
 * resets the passes. */
void beSvWriteMediaApi_Start(beSvWriteMediaApiWork *self, beSvDeliver *deliver) {
    beSvPlatDataPS2 *platform;
    int own;
    int allocator;
    igObject *old;
    int *image;
    int *field;
    beSaveDataDeliver *gameData;

    platform = (beSvPlatDataPS2 *)deliver->_platformData;
    self->_connect = deliver->_targetConnect;
    self->_isEnd = 0;
    self->_result = 1;
    g_svPlatformData[0] = (beSvPlatDataPS2 *)deliver->_platformData;
    self->_imagePass = 0;
    own = (int)(igObject_GetAllocator((igObject *)self));
    allocator = g_useOwnerAllocator != 0 ? own : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    old = self->_saveWork;
    IG_OBJECT_RELEASE(old);
    self->_saveWork = beSaveMemoryObj_CreateInstance(allocator);
    beSaveMemoryObj_Allocate(self->_saveWork, platform->_dataSize, 32);
    image = (int *)self->_saveWork->_mem;
    field = image;
    field++;
    *field++ = g_svSaveVersion[0];
    gameData = (beSaveDataDeliver *)deliver->_gameData;
    memcpy(field, (void *)gameData->_data, gameData->_size);
    image[0] = ((beSaveApiDispatchView *)self)->checksum(image, platform->_dataSize);
    self->_phase = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_step = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

/* Memory-card write state machine, polled once per frame by the save-data pipeline. _phase (_st0)
 * selects the phase and _step (_st1) the step inside it. Every phase runs three steps: 0 clears
 * the retry counter, 1 issues one asynchronous memory-card request and raises its in-flight flag,
 * 2 polls the flag (returning 0 while it is set) and reads the result code. A failed request is
 * retried up to three times, then the machine ends with _isEnd = 1 and _result = 3 for the card-
 * unusable codes (-2, -4, -5, ...) or 12 for anything else. Phases: 0 opens /<dir>/<dir>, 1
 * resets the image pass, 2 seeks to the pass's data offset, 3 writes the save buffer and flushes
 * it (then repeats phases 2-3 for the second pass), 4 closes the file (_result = 2, saved).
 * Returns 1 when already finished, 0 while a request is pending, else _isEnd. */
int beSvWriteMediaApi_Update(beSvWriteMediaApiWork *self)
{
    char path[256];
    int res;
    beSvPlatDataPS2 *platform;

    if (self->_isEnd != 0) {
        return 1;
    }
    if (g_svConnectCheckPending == 1) {
        return 0;
    }
    platform = g_svPlatformData[0];
    switch (self->getPhase()) {
    case 0:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            sprintf(path, "/%s/%s", platform->_dirName, platform->_dirName);
            if (sceMcOpen(g_svCardSlots[self->_connect].port, g_svCardSlots[self->_connect].slot, path, 3) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_OPEN] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_OPEN] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_OPEN];
            if (res >= 0) {
                g_svSaveFd[0] = res;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -3:
                    case -4:
                    case -5:
                    case -7:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 1:
        self->_imagePass = 0;
        self->_phase = self->_phase + 1;
        SV_FIRST_STEP(self);
        /* fall through */
    case 2:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcSeek(g_svSaveFd[0], platform->_dataOffSet[self->_imagePass], 0) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_SEEK] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_SEEK] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_SEEK];
            if (res >= 0) {
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 3:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcWrite(g_svSaveFd[0], (void *)self->_saveWork->_mem, platform->_dataSize) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_WRITE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_WRITE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_WRITE];
            if (res >= 0) {
                SV_NEXT_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        case 3:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 4:
            if (sceMcFlush(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_FLUSH] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 5:
            if (g_svMcRequestState[SCE_MC_FUNC_FLUSH] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_FLUSH];
            if (res >= 0) {
                if (self->_imagePass == 0) {
                    self->_imagePass = 1;
                    self->_phase = self->_phase - 1;
                    SV_FIRST_STEP(self);
                } else {
                    self->_phase = self->_phase + 1;
                    SV_FIRST_STEP(self);
                }
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else switch (res) {
                case -2:
                    self->_result = 3;
                    self->_isEnd = 1;
                    break;
                default:
                    self->_result = 12;
                    self->_isEnd = 1;
                    break;
                }
            }
            break;
        }
        break;
    case 4:
        switch (self->_step) {
        case 0:
            self->_retryCount = 0;
            SV_NEXT_STEP(self);
            break;
        case 1:
            if (sceMcClose(g_svSaveFd[0]) >= 0) {
                g_svMcRequestState[SCE_MC_FUNC_CLOSE] = SV_MC_REQUEST_ISSUED;
                SV_NEXT_STEP(self);
            }
            break;
        case 2:
            if (g_svMcRequestState[SCE_MC_FUNC_CLOSE] == SV_MC_REQUEST_ISSUED) {
                return 0;
            }
            res = g_svMcRequestResult[SCE_MC_FUNC_CLOSE];
            if (res >= 0) {
                self->_isEnd = 1;
                self->_result = 2;
                self->_phase = self->_phase + 1;
                SV_FIRST_STEP(self);
            } else {
                self->_retryCount = self->_retryCount + 1;
                if (SV_MAY_RETRY(self)) {
                    SV_RETRY_STEP(self);
                } else {
                    switch (res) {
                    case -2:
                    case -4:
                    case -5:
                    case -8:
                        self->_result = 3;
                        self->_isEnd = 1;
                        break;
                    default:
                        self->_result = 12;
                        self->_isEnd = 1;
                        break;
                    }
                }
            }
            break;
        }
        break;
    case 5:
        break;
    }
    if (self->_isEnd != 0) {
        beSaveMemoryObj_Free(self->_saveWork);
        g_svCardBusy = 0;
    }
    return self->_isEnd;
}

#undef SV_RETRY_STEP
#undef SV_FIRST_STEP
#undef SV_NEXT_STEP

void beSvWriteMediaApi_Report(beSvWriteMediaApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void beSvGetFreeSizeApi_Start(beSvApiWork *self, beSvDeliver *deliver) {
    self->_connect = deliver->_targetConnect;
    self->_isEnd = 0;
    self->_result = 1;
    g_svPlatformData[0] = (beSvPlatDataPS2 *)deliver->_platformData;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
    g_svCardBusy = 1;
    self->_retryCount = 0;
}

unsigned char beSvGetFreeSizeApi_Update(beSvGetFreeSizeApiWork *self) {
    int connect;
    beSvPlatDataPS2 *platform;
    int res;

    if (self->_isEnd != 0) {
        return 1U;
    }
    if (g_svConnectCheckPending == 1) {
        return 0U;
    }
    platform = g_svPlatformData[0];
    switch (self->_st0) {
    case 0:
        self->_retryCount = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        break;
    case 1:
        connect = self->_connect;
        if (sceMcGetInfo(g_svCardSlots[connect].port, g_svCardSlots[connect].slot, &self->_cardType, &self->_freeKb, &self->_format) >= 0) {
            g_svMcRequestState[SCE_MC_FUNC_GET_INFO] = SV_MC_REQUEST_ISSUED;
            self->_st0 = self->_st0 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st1 = 0;
        }
        break;
    case 2:
        if (g_svMcRequestState[SCE_MC_FUNC_GET_INFO] == SV_MC_REQUEST_ISSUED) {
            return 0U;
        }
        res = g_svMcRequestResult[SCE_MC_FUNC_GET_INFO];
        if (res >= 0) {
            switch (self->_cardType) {
            case 2:
                self->_result = 2;
                self->_fileCapa = 0x80;
                self->_isEnd = 1U;
                switch (self->_format) {
                case 0:
                    self->_memCapa = 0x04E00000U;
                    break;
                case 1:
                    self->_memCapa = self->_freeKb << 0xA;
                    break;
                }
                if (!(platform->_memNeed > (unsigned int)self->_memCapa)) {
                    self->_result = 2;
                } else {
                    self->_result = 9;
                }
                break;
            case 0:
            case 3:
            case 1:
                self->_result = 0xC;
                break;
            }
            self->_isEnd = 1U;
            break;
        }
        self->_retryCount = self->_retryCount + 1;
        if ((unsigned char)(self->_retryCount < 3) == 1) {
            self->_st0 = 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st1 = 0;
        } else {
            switch (res) {
            case -2:
                self->_memCapa = 0x04E00000U;
                self->_fileCapa = 0x80;
                self->_result = 2;
                self->_isEnd = 1U;
                break;
            case -5:
                self->_result = 5;
                self->_isEnd = 1U;
                break;
            default:
            case -1:
                self->_result = 0xC;
                self->_isEnd = 1U;
                break;
            }
        }
        break;
    }
    if (self->_isEnd == 1) {
        g_svCardBusy = 0;
    }
    return self->_isEnd;
}

void beSvGetFreeSizeApi_Report(beSvGetFreeSizeApiWork *self, beSvDeliver *deliver) {
    beSvPlatDataPS2 *platform = g_svPlatformData[0];

    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
    if (self->_format == 1) {
        deliver->_memCapa = self->_memCapa;
    } else {
        deliver->_memCapa = 0x04E00000;
    }
    deliver->_fileCapa = self->_fileCapa;
    if (!(platform->_memNeed > (unsigned int)self->_memCapa)) {
        deliver->_isMemCapaOK = 1;
    } else {
        deliver->_isMemCapaOK = 0;
    }
    deliver->_isfileCapaOK = 1;
}

void beSvStartApi_Start(beSvApiWork *self, beSvDeliver *deliver) {
    self->_isEnd = 0;
    if (g_svMcModulesLoaded == 0) {
        igPsx2_LoadIopModule("mcman.irx", 1, 0, 0);
        igPsx2_LoadIopModule("mcserv.irx", 1, 0, 0);
        sceMcInit();
        g_svMcModulesLoaded = 1;
    }
    sceMtapPortOpen(2);
    g_svConnectMax[0] = 5;
    g_svSaveVersion[0] = deliver->_saveVer;
    if (sceMtapGetConnection(2) == 1) {
        g_svMultitapState = 1;
        g_svMultitapChanged = 0;
    } else {
        g_svMultitapChanged = 0;
        g_svMultitapState = -1;
    }
    g_svCardBusy = 0;
    g_svConnectCheckPending = 0;
    self->_retryCount = 0;
    self->_result = 1;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

int beSvStartApi_Update(beSvStartApi *self) {
    if (self->_isEnd != 0) {
        return 1;
    }
    self->_isEnd = 1;
    return 1;
}

void beSvStartApi_Report(beSvStartApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void beSvEndApi_Start(beSvEndApi *self) {
    self->_isEnd = 0;
    self->_result = 1;
    sceMtapPortClose(2);
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

int beSvEndApi_Update(beSvEndApi *self) {
    if (self->_isEnd != 0) {
        return 1;
    }
    self->_isEnd = 1;
    self->_result = 2;
    return 1;
}

void beSvEndApi_Report(beSvEndApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

int beSvConnectCheck_ProbeSlot(int check, int slot) {
    int cardType;

    cardType = 0;
    sceMcGetInfo(g_svCardSlots[slot].port, g_svCardSlots[slot].slot, &cardType, 0, 0);
    sceMcSync(0, 0, 0);
    if (cardType == 2) {
        g_svSlotPresent[slot] = 1;
        return 1;
    }
    g_svSlotPresent[slot] = 0;
    return 0;
}

int beSvConnectCheck_ProbeSlots(int check, int onlyPresent) {
    int count;
    int i;
    count = 5;
    if (g_svMultitapState == -1)
        count = 2;
    else if (g_svMultitapState == 1)
        count = 5;
    for (i = 0; i < count; i++) {
        if (!onlyPresent || g_svSlotPresent[i] == 1)
            beSvConnectCheck_ProbeSlot(check, i);
    }
    for (i = count; i < 8; i++)
        g_svSlotPresent[i] = 0;
    return count;
}

void beSvConnectCheck_PollMultitap(int check, beSvDeliver *deliver) {
    if (g_svMultitapPollSuspended[0] != 0) {
        if (g_svMultitapPollCount[0] > 0) {
            goto poll;
        }
    } else {
poll:
        if (sceMtapGetConnection(2) == 1) {
            if (g_svMultitapState == 1) {
                g_svMultitapChanged = 0;
                g_svMultitapPollCount[0] = 0;
            } else {
                g_svMultitapPollCount[0] += 1;
                if (g_svMultitapPollCount[0] >= 3) {
                    g_svMultitapPollCount[0] = 0;
                    g_svMultitapChanged = 1;
                    g_svMultitapState = 1;
                }
            }
        } else if (g_svMultitapState == -1) {
            g_svMultitapChanged = 0;
            g_svMultitapPollCount[0] = 0;
        } else {
            g_svMultitapPollCount[0] += 1;
            if (g_svMultitapPollCount[0] >= 3) {
                g_svMultitapPollCount[0] = 0;
                g_svMultitapChanged = -1;
                g_svMultitapState = -1;
            }
        }
        deliver->_useMtap = g_svMultitapState;
        deliver->_chgUseMtap = g_svMultitapChanged;
    }
}

void beSvConnectCheck_Poll(beSvConnectCheckWork *check) {
    if (g_svConnectCheckPending == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            switch (result) {
            case 0:
            case -2:
            case -1:
                g_svSlotPresent[check->_slot] = 1;
                check->_freeSizes[check->_slot] = check->_free;
                check->_formats[check->_slot] = check->_format;
                break;
            default:
                g_svSlotPresent[check->_slot] = 0;
                break;
            }
            g_svConnectCheckPending = 0;
            if (!g_svCardBusy) {
                int count = beSvConnectCheck_ProbeSlots((int)check, 1);
                bool found = false;
                int tries;
                for (tries = 1; tries < count + 1; tries++) {
                    int s = (check->_slot + tries) % count;
                    if (g_svSlotPresent[s] == 0) {
                        check->_slot = s;
                        found = true;
                        break;
                    }
                }
                if (found == true) {
                    sceMcGetInfo(g_svCardSlots[check->_slot].port, g_svCardSlots[check->_slot].slot, 0, &check->_free, &check->_format);
                    g_svConnectCheckPending = 1;
                }
            }
        }
    } else if (g_svCardBusy == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            if (cmd > 0 && cmd < 22 && g_svMcRequestState[cmd] == SV_MC_REQUEST_ISSUED) {
                g_svMcRequestResult[cmd] = result;
                g_svMcRequestState[cmd] = SV_MC_REQUEST_DONE;
            }
        }
    } else {
        int count = beSvConnectCheck_ProbeSlots((int)check, 0);
        check->_slot = 0;
        bool found = false;
        int s;
        for (s = 0; s < count; s++) {
            if (g_svSlotPresent[s] == 0) {
                check->_slot = s;
                found = true;
                break;
            }
        }
        if (found == true) {
            sceMcGetInfo(g_svCardSlots[check->_slot].port, g_svCardSlots[check->_slot].slot, 0, &check->_free, &check->_format);
            g_svConnectCheckPending = 1;
        }
    }
}

/* slotWords walks beSvConnectCheckWork one word per slot, so slotWords[16] and slotWords[24] are
 * that slot's _freeSizes and _formats entries. */
int beSvConnectCheck_FillDeliver(int *slotWords, beSvDeliver *deliver) {
    igIntList *connected;
    igIntList *freeSizes;
    igIntList *formats;
    int i;
    int n;
    int *data;
    int *present;
    int found;
    int j;
    int count;
    int off;
    connected = (igIntList *)deliver->_actConnect;
    freeSizes = (igIntList *)deliver->_freeSizeList;
    formats = (igIntList *)deliver->_formatList;
    found = 0;
    if (g_svMultitapPollCount[0] == 0) {
        deliver->_useMtap = g_svMultitapState;
    }
    n = connected->_count;
    data = (int *)connected->_data;
    for (j = 0; j < n; j++) {
        data[j] = g_svSlotAbsent[0];
    }
    i = 0;
    if (0 < connected->_count) {
        off = 0;
        present = &g_svSlotPresent[0];
        do {
            count = *(int *)&connected->_count;
            if (count != 0 && i >= 0 && i < count) {
                *(int *)((char *)connected->_data + off) = *present;
            }
            if (*present == 1) {
                count = freeSizes->_count;
                if (count != 0 && i >= 0 && i < count) {
                    *(int *)((char *)freeSizes->_data + off) = slotWords[16];
                }
                count = formats->_count;
                if (count != 0 && i >= 0 && i < count) {
                    *(int *)((char *)formats->_data + off) = slotWords[24];
                }
                found++;
            }
            i++;
            present++;
            off += 4;
            slotWords++;
        } while (i < connected->_count);
    }
    return found;
}

void beSvConnectCheck_Start(void)
{
}

int beSvConnectCheck_Update(void) {
    return 0;
}

void beSvConnectCheck_Report(void)
{
}

igMetaObject *beSvConnectCheck_GetMeta(void)
{
    return g_beSvConnectCheck_metaObject;
}

void beSvConnectCheck_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

igMetaObject *beSaveApi_GetMeta(void)
{
    return g_beSaveApi_metaObject;
}

void beSvConnectCheck_userDestruct(beSvConnectCheck *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvEndApi_GetMeta(void)
{
    return g_beSvEndApi_metaObject;
}

void beSvEndApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

void beSvEndApi_userDestruct(beSvEndApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvStartApi_GetMeta(void)
{
    return g_beSvStartApi_metaObject;
}

void beSvStartApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

void beSvStartApi_userDestruct(beSvStartApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvGetFreeSizeApi_GetMeta(void)
{
    return g_beSvGetFreeSizeApi_metaObject;
}

void beSvGetFreeSizeApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

void beSvGetFreeSizeApi_userDestruct(beSvGetFreeSizeApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvWriteMediaApi_GetMeta(void)
{
    return g_beSvWriteMediaApi_metaObject;
}

void beSvWriteMediaApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

void beSvWriteMediaApi_userDestruct(beSvWriteMediaApi *self) {
    igObject *saveWork;

    saveWork = (igObject *)self->_saveWork;
    if (saveWork != 0) {
        IG_OBJECT_RELEASE(saveWork);
        self->_saveWork = 0;
    }
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvReadMediaApi_GetMeta(void)
{
    return g_beSvReadMediaApi_metaObject;
}

void beSvReadMediaApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

static inline int countOf(const igObjectList *l) { return l->_count; }

void beSvReadMediaApi_userDestruct(beSvReadMediaApi *self) {
    igObjectList *l = (igObjectList *)self->_loadWorkList;
    if (countOf(l) != 0) {
        int n = l->_count;
        int i;
        igObject *t;
        for (i = 0; i < n; i++) {
            t = ((igObject **)l->_data)[i];
            IG_OBJECT_RELEASE(t);
        }
        {
            int m = l->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l->_data)[j] = 0;
            }
        }
        l->_count = 0;
    }
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvUseCheckApi_GetMeta(void)
{
    return g_beSvUseCheckApi_metaObject;
}

void beSvUseCheckApi_userDestruct(beSvUseCheckApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

void beSaveApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

igMetaObject *beSvFormatApi_GetMeta(void)
{
    return g_beSvFormatApi_metaObject;
}

void beSvFormatApi_userDestruct(beSvFormatApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvFileFindApi_GetMeta(void)
{
    return g_beSvFileFindApi_metaObject;
}

void beSvFileFindApi_userDestruct(beSvFileFindApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

igMetaObject *beSvFileMakeApi_GetMeta(void)
{
    return g_beSvFileMakeApi_metaObject;
}

void beSvFileMakeApi_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

void beSvFileMakeApi_userDestruct(beSvFileMakeApi *self) {
    igObject *saveWork;

    saveWork = (igObject *)self->_saveWork;
    if (saveWork != 0) {
        IG_OBJECT_RELEASE(saveWork);
        self->_saveWork = 0;
    }
    Gap__Core__igObject__userDestruct(self);
}

void beSaveApi_userDestruct(beSaveApi *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

void beSaveMemoryObj_userConstruct(igObjectDispatchView *self) {
    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(self->GetMeta(), 1);
}

#pragma pop

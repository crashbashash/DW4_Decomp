#include "dw4/reflected.h"
#include "dw4/igobject_release.h"

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
    SCE_MC_FUNC_WRITE = 6,
    SCE_MC_FUNC_FLUSH = 10,
    SCE_MC_FUNC_FORMAT = 16
};

/* Request state per libmc request number: 1 while issued, 2 once beSvConnectCheck_Poll stores its
 * result. */
enum { SV_MC_REQUEST_ISSUED = 1, SV_MC_REQUEST_DONE = 2 };

class igObjectVirtuals {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual int getMetaObject();
};

struct CardSlot { int port; int slot; };

extern "C" int Memory_AllocateBufferDirect(int, int);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int igObject_GetAllocator(...);
extern "C" void beSaveDataDeliver_AllocateData(beSaveDataDeliver *deliver, int size);
extern "C" int Memory_FreeBufferWithAllocator(int, int);
extern "C" int memset(void *, int, int);
extern "C" int Memory_AllocateAlignedWithAllocator(int, int, int);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void Gap__Bec__beSaveMemoryObj__vfunc_08(beSaveMemoryObj *self);
extern "C" int Gap__Bec__beSaveMemoryObj__vfunc_20(void);
extern "C" int sceMcFormat(int, int);
extern "C" int sceMcGetInfo(...);
extern "C" int sprintf(char *, const char *, ...);
extern "C" int sceMcOpen(int, int, char *, int);
extern "C" int sceMcClose(int);
extern "C" int sceMcSeek(int, int, int);
extern "C" int sceMcWrite(int, int, int);
extern "C" int sceMcFlush(int);
extern "C" int sceMcInit(...);
extern "C" int FUN_0032cf50(int *, const char *, int, int, int);
extern "C" int sceMtapGetConnection(int);
extern "C" int sceMtapPortOpen(int);
extern "C" int sceMtapPortClose(int);
extern "C" int sceMcSync(...);
extern "C" int beSvConnectCheck_ProbeSlot(int check, int slot);
extern "C" int beSvConnectCheck_ProbeSlots(int check, int onlyPresent);
extern "C" void beSvConnectCheck_PollMultitap(int check, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_21(void);
extern "C" int Gap__Bec__beSvConnectCheck__vfunc_22(void);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_23(void);
extern "C" int Gap__Bec__beSvConnectCheck__vfunc_20(void);
extern "C" int Gap__Core__igObject__vfunc_07(...);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_07(igObjectVirtuals *self);
extern "C" int Gap__Bec__beSaveApi__vfunc_20(void);
extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(...);
extern "C" void Gap__Bec__beSvConnectCheck__vfunc_08(void);
extern "C" int Gap__Bec__beSvEndApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvEndApi__vfunc_07(igObjectVirtuals *self);
extern "C" void Gap__Bec__beSvEndApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvStartApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvStartApi__vfunc_07(igObjectVirtuals *self);
extern "C" void Gap__Bec__beSvStartApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvGetFreeSizeApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_07(igObjectVirtuals *self);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvWriteMediaApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_07(igObjectVirtuals *self);
extern "C" int igObject_Destroy(...);
extern "C" int Gap__Bec__beSvReadMediaApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_07(igObjectVirtuals *self);
extern "C" int Gap__Bec__beSvUseCheckApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_08(void);
extern "C" void Gap__Bec__beSaveApi__vfunc_07(igObjectVirtuals *self);
extern "C" int Gap__Bec__beSvFormatApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvFileFindApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_08(void);
extern "C" int Gap__Bec__beSvFileMakeApi__vfunc_20(void);
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_07(igObjectVirtuals *self);
extern "C" void Gap__Bec__beSaveApi__vfunc_08(void);
extern "C" void Gap__Bec__beSaveMemoryObj__vfunc_07(igObjectVirtuals *self);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void beSaveDataDeliver_FreeData(beSaveDataDeliver *deliver);
extern "C" void beSaveMemoryObj_Allocate(beSaveMemoryObj *self, int size, int alignment);
extern "C" void beSaveMemoryObj_Free(beSaveMemoryObj *self);
extern "C" int g_beSaveMemoryObj_metaObject[4];
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_23(beSvFileMakeApi *self, beSvDeliver *deliver);
extern "C" unsigned char g_svCardBusy;
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvFileFindApi__vfunc_23(beSvFileFindApi *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver);
extern "C" int g_svMcRequestState[24];
extern "C" int g_svMcRequestResult[24];
extern "C" unsigned char g_svConnectCheckPending;
extern "C" unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvApiWork *self);
extern "C" void Gap__Bec__beSvFormatApi__vfunc_23(beSvFormatApi *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver);
extern "C" unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApiWork *self);
extern "C" void Gap__Bec__beSvUseCheckApi__vfunc_23(beSvUseCheckApi *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_23(beSvReadMediaApi *self, beSvDeliver *deliver);
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
extern "C" char slash_percent_s_slash_percent_s[];
extern "C" int g_svSaveFd[1];
extern "C" int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiWork *self);
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_23(beSvWriteMediaApi *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver);
extern "C" unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApiWork *self);
extern "C" void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApiWork *self, beSvDeliver *deliver);
extern "C" int g_svConnectMax[1];
extern "C" char mcman_irx[];
extern "C" char mcserv_irx[];
extern "C" int g_svSaveVersion[1];
extern "C" char g_svMultitapState;
extern "C" unsigned char g_svMcModulesLoaded;
extern "C" char g_svMultitapChanged;
extern "C" void Gap__Bec__beSvStartApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver);
extern "C" int Gap__Bec__beSvStartApi__vfunc_22(beSvStartApi *self);
extern "C" void Gap__Bec__beSvStartApi__vfunc_23(beSvStartApi *self, beSvDeliver *deliver);
extern "C" void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *self);
extern "C" int Gap__Bec__beSvEndApi__vfunc_22(beSvEndApi *self);
extern "C" void Gap__Bec__beSvEndApi__vfunc_23(beSvEndApi *self, beSvDeliver *deliver);
extern "C" int g_svSlotPresent[8];
extern "C" int g_svMultitapPollCount[1];
extern "C" int g_svMultitapPollSuspended[1];
extern "C" void beSvConnectCheck_Poll(beSvConnectCheckWork *check);
extern "C" int g_svSlotAbsent[1];
extern "C" int beSvConnectCheck_FillDeliver(int *slotWords, beSvDeliver *deliver);
extern "C" int g_beSvConnectCheck_metaObject[4];
extern "C" int g_beSaveApi_metaObject[4];
extern "C" int g_beSvEndApi_metaObject[4];
extern "C" int g_beSvStartApi_metaObject[4];
extern "C" int g_beSvGetFreeSizeApi_metaObject[4];
extern "C" int g_beSvWriteMediaApi_metaObject[4];
extern "C" void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *self);
extern "C" int g_beSvReadMediaApi_metaObject[4];
extern "C" void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *self);
extern "C" int g_beSvUseCheckApi_metaObject[4];
extern "C" int g_beSvFormatApi_metaObject[4];
extern "C" int g_beSvFileFindApi_metaObject[4];
extern "C" int g_beSvFileMakeApi_metaObject[4];
extern "C" void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *self);

void beSaveDataDeliver_AllocateData(beSaveDataDeliver *deliver, int size) {
    int own;
    int allocator;
    deliver->_size = size;
    own = igObject_GetAllocator(deliver);
    if (g_useOwnerAllocator != 0) {
        allocator = own;
    } else {
        allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    deliver->_data = Memory_AllocateBufferDirect(size, allocator);
}

void beSaveDataDeliver_FreeData(beSaveDataDeliver *deliver) {
    int allocator;

    if (deliver->_data != 0) {
        allocator = igObject_GetAllocator(deliver);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(deliver->_data, allocator);
    }
    deliver->_data = 0;
    deliver->_size = 0;
}

void beSaveMemoryObj_Allocate(beSaveMemoryObj *self, int size, int alignment) {
    int own, allocator;

    if (alignment == 0) {
        own = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator != 0 ? own : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        self->_mem = Memory_AllocateBufferDirect(size, allocator);
    } else {
        own = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator != 0 ? own : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        self->_mem = Memory_AllocateAlignedWithAllocator(size, alignment & 0xFFFF, allocator);
    }
    memset((void *)self->_mem, 0, size);
}

void beSaveMemoryObj_Free(beSaveMemoryObj *self) {
    int allocator;

    if (self->_mem != 0) {
        allocator = igObject_GetAllocator();
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(self->_mem, allocator);
    }
    self->_mem = 0;
}

void Gap__Bec__beSaveMemoryObj__vfunc_08(beSaveMemoryObj *self) {
    beSaveMemoryObj_Free(self);
    igMetaObject_CountInstances(((igObjectVirtuals *)self)->getMetaObject(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int Gap__Bec__beSaveMemoryObj__vfunc_20(void)
{
    return g_beSaveMemoryObj_metaObject[0];
}

void Gap__Bec__beSvFileMakeApi__vfunc_23(beSvFileMakeApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvFileFindApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver) {
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

void Gap__Bec__beSvFileFindApi__vfunc_23(beSvFileFindApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvFormatApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver) {
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

unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvApiWork *self) {
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

void Gap__Bec__beSvFormatApi__vfunc_23(beSvFormatApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvUseCheckApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver) {
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

unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApiWork *self) {
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

void Gap__Bec__beSvUseCheckApi__vfunc_23(beSvUseCheckApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvReadMediaApi__vfunc_23(beSvReadMediaApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

#define SV_NEXT_STEP(self)  ((self)->_step = (self)->getStep() + 1, (self)->_st3 = 0, (self)->_st2 = 0)
#define SV_FIRST_STEP(self) ((self)->_st3 = 0, (self)->_st2 = 0, (self)->_step = 0)
#define SV_RETRY_STEP(self) ((self)->_step = 1, (self)->_st3 = 0, (self)->_st2 = 0)
/* Memory-card write state machine, polled once per frame by the save-data pipeline. _phase (_st0)
 * selects the phase and _step (_st1) the step inside it. Every phase runs three steps: 0 clears
 * the retry counter, 1 issues one asynchronous memory-card request and raises its in-flight flag,
 * 2 polls the flag (returning 0 while it is set) and reads the result code. A failed request is
 * retried up to three times, then the machine ends with _isEnd = 1 and _result = 3 for the card-
 * unusable codes (-2, -4, -5, ...) or 12 for anything else. Phases: 0 opens /<dir>/<dir>, 1
 * resets the image pass, 2 seeks to the pass's data offset, 3 writes the save buffer and flushes
 * it (then repeats phases 2-3 for the second pass), 4 closes the file (_result = 2, saved).
 * Returns 1 when already finished, 0 while a request is pending, else _isEnd. */
int Gap__Bec__beSvWriteMediaApi__vfunc_22(beSvWriteMediaApiWork *self)
{
    char path[256];
    int ok;
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
            sprintf(path, slash_percent_s_slash_percent_s, platform->_dirName, platform->_dirName);
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
                ok = self->_retryCount < 3; if (ok == 1) {
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
                ok = self->_retryCount < 3; if (ok == 1) {
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
            if (sceMcWrite(g_svSaveFd[0], self->_saveWork->_mem, platform->_dataSize) >= 0) {
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
                ok = self->_retryCount < 3; if (ok == 1) {
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
                ok = self->_retryCount < 3; if (ok == 1) {
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
                ok = self->_retryCount < 3; if (ok == 1) {
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

void Gap__Bec__beSvWriteMediaApi__vfunc_23(beSvWriteMediaApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver) {
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

unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApiWork *self) {
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

void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApiWork *self, beSvDeliver *deliver) {
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

void Gap__Bec__beSvStartApi__vfunc_21(beSvApiWork *self, beSvDeliver *deliver) {
    int mcmanId;
    int mcservId;

    self->_isEnd = 0;
    if (g_svMcModulesLoaded == 0) {
        FUN_0032cf50(&mcmanId, mcman_irx, 1, 0, 0);
        FUN_0032cf50(&mcservId, mcserv_irx, 1, 0, 0);
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

int Gap__Bec__beSvStartApi__vfunc_22(beSvStartApi *self) {
    if (self->_isEnd != 0) {
        return 1;
    }
    self->_isEnd = 1;
    return 1;
}

void Gap__Bec__beSvStartApi__vfunc_23(beSvStartApi *self, beSvDeliver *deliver) {
    deliver->_result = self->_result;
    deliver->_isEndOperat = 1;
}

void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *self) {
    self->_isEnd = 0;
    self->_result = 1;
    sceMtapPortClose(2);
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

int Gap__Bec__beSvEndApi__vfunc_22(beSvEndApi *self) {
    if (self->_isEnd != 0) {
        return 1;
    }
    self->_isEnd = 1;
    self->_result = 2;
    return 1;
}

void Gap__Bec__beSvEndApi__vfunc_23(beSvEndApi *self, beSvDeliver *deliver) {
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

void Gap__Bec__beSvConnectCheck__vfunc_21(void)
{
}

int Gap__Bec__beSvConnectCheck__vfunc_22(void) {
    return 0;
}

void Gap__Bec__beSvConnectCheck__vfunc_23(void)
{
}

int Gap__Bec__beSvConnectCheck__vfunc_20(void)
{
    return g_beSvConnectCheck_metaObject[0];
}

void Gap__Bec__beSvConnectCheck__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

int Gap__Bec__beSaveApi__vfunc_20(void)
{
    return g_beSaveApi_metaObject[0];
}

void Gap__Bec__beSvConnectCheck__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvEndApi__vfunc_20(void)
{
    return g_beSvEndApi_metaObject[0];
}

void Gap__Bec__beSvEndApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

void Gap__Bec__beSvEndApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvStartApi__vfunc_20(void)
{
    return g_beSvStartApi_metaObject[0];
}

void Gap__Bec__beSvStartApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

void Gap__Bec__beSvStartApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvGetFreeSizeApi__vfunc_20(void)
{
    return g_beSvGetFreeSizeApi_metaObject[0];
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

void Gap__Bec__beSvGetFreeSizeApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvWriteMediaApi__vfunc_20(void)
{
    return g_beSvWriteMediaApi_metaObject[0];
}

void Gap__Bec__beSvWriteMediaApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *self) {
    igObject *saveWork;

    saveWork = (igObject *)self->_saveWork;
    if (saveWork != 0) {
        IG_OBJECT_RELEASE(saveWork);
        self->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int Gap__Bec__beSvReadMediaApi__vfunc_20(void)
{
    return g_beSvReadMediaApi_metaObject[0];
}

void Gap__Bec__beSvReadMediaApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

static inline int countOf(const igObjectList *l) { return l->_count; }

void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *self) {
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
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int Gap__Bec__beSvUseCheckApi__vfunc_20(void)
{
    return g_beSvUseCheckApi_metaObject[0];
}

void Gap__Bec__beSvUseCheckApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

void Gap__Bec__beSaveApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

int Gap__Bec__beSvFormatApi__vfunc_20(void)
{
    return g_beSvFormatApi_metaObject[0];
}

void Gap__Bec__beSvFormatApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvFileFindApi__vfunc_20(void)
{
    return g_beSvFileFindApi_metaObject[0];
}

void Gap__Bec__beSvFileFindApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

int Gap__Bec__beSvFileMakeApi__vfunc_20(void)
{
    return g_beSvFileMakeApi_metaObject[0];
}

void Gap__Bec__beSvFileMakeApi__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *self) {
    igObject *saveWork;

    saveWork = (igObject *)self->_saveWork;
    if (saveWork != 0) {
        IG_OBJECT_RELEASE(saveWork);
        self->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

void Gap__Bec__beSaveApi__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

void Gap__Bec__beSaveMemoryObj__vfunc_07(igObjectVirtuals *self) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(self->getMetaObject(), 1);
}

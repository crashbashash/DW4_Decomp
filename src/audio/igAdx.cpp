#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"
#include "dw4/cri/adxfs.h"
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_AllocateAlignedWithAllocator(...);
extern "C" int ADXT_Create(int, int, int);
extern "C" int ADXT_StartMemIdx(int, int, int);
extern "C" int ADXT_StartAfs(int, short, short);
extern "C" int ADXT_StartFname(int, const char *);
extern "C" int ADXT_Stop(int);
extern "C" void igAdxAudio_Stop(igAdxAudio *audio);
extern "C" int ADXT_Pause(int, int);
extern "C" void igAdxAudio_Pause(igAdxAudio *audio, int pause);
extern "C" int ADXT_GetStatPause(int);
extern "C" int igAdxAudio_GetPauseState(igAdxAudio *audio);
extern "C" int ADXT_Destroy(...);
extern "C" int Memory_FreeBufferWithAllocator(...);
extern "C" int ADXT_SetOutVol(int, int);
extern "C" void igAdxAudio_SetOutVolume(igAdxAudio *audio, int volume);
extern "C" int ADXT_GetOutVol(int);
extern "C" int igAdxAudio_GetOutVolume(igAdxAudio *audio);
extern "C" int ADXT_GetStat(int);
extern "C" int igAdxAudio_GetStatus(igAdxAudio *audio);
extern "C" igStringObj *igStringObj_Create(int);
extern "C" int Memory_GetAllocatorByName(...);
extern "C" void igAdx_CreateScratchString(void);
extern "C" int DisableIntc(int);
extern "C" int ADXM_ShutdownThrd(...);
extern "C" int SNDF_Finish(...);
extern "C" int mwPlyFinishSfdFx(...);
extern "C" int RemoveIntcHandler(int, int);
extern "C" void igAdx_Shutdown(void);
extern "C" void Gap__Core__igObject__constructFields(void);
extern "C" void Gap__igAdx__constructFields(void);
extern "C" int memset(...);
extern "C" int Gap__Core__igObject__resetFields(...);
extern "C" void Gap__igAdx__resetFields(void);
extern "C" int Gap__Core__igObject__userConstruct(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void Gap__igAdx__userConstruct(igObject *self);
extern "C" int Gap__igAdx__getMeta(void);
extern "C" void Gap__igAdx__destructFields(void);
extern "C" int Gap__Core__igObject__userDestruct(...);
extern "C" void Gap__igAdx__userDestruct(igObject *self);
extern "C" void igAdx_ErrorCallback(void);
extern "C" int strcpy(...);
extern "C" void igAdx_SetModulePath(int path);
extern "C" void igAdx_SetHostRootPath(int path);
extern "C" int AddIntcHandler(int, int (*)(), int);
extern "C" int ADXM_ExecVint(void);
extern "C" int EnableIntc(int);
extern "C" int sceSifInitRpc(int);
extern "C" int sceSifInitIopHeap(...);
extern "C" int sceCdInit(int);
extern "C" int sceCdMmode(int);
extern "C" int sceSdRemoteInit(...);
extern "C" int sceSdRemote(...);
extern "C" int sprintf(...);
extern "C" int ADXPS2_SetupDvdFs(int);
extern "C" int ADXPS2_LoadFcacheDvd(AdxFcachePrm *);
extern "C" int ADXPS2_SetupHostFs(AdxHstFsPrm *);
extern "C" int ADXPS2_LoadFcacheHst(AdxFcachePrm *);
extern "C" int ADXPS2_SetupMfs(int);
extern "C" int igPsx2_LoadIopModule(...);
extern "C" int strcmp(...);
extern "C" int igAdx_SetupIop(void);
extern "C" int igAdx_SetupOptional(void);
extern "C" int ADXT_Init(...);
extern "C" int ADXM_SetCbErr(void (*)(void), int);
extern "C" int ADXM_SetupThrd(int);
extern "C" int SNDF_Start(...);
extern "C" int igAdx_Initialize(int setupOptional);
extern "C" void ADXM_ExecVsyncFrame(void);
extern "C" void igAdx_ExecVsync(void);
extern "C" int ADXM_ExecMain(...);
extern "C" int SNDF_ExecServer(...);
extern "C" void igAdx_ExecServer(int);
extern "C" void *igStringRefList_Create(int);
extern "C" void igAdx_SetPartitionCount(int count);
extern "C" int StringPool_Allocate(int);
extern "C" int List_Reserve(void *, int, int);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" char *StringPool_Intern(int, char *);
extern "C" void igAdx_AddPartitionName(int partition, char *name);
extern "C" void ADXF_LoadPartitionNw(int stream, const char *name, int mode, void *buffer);
extern "C" int ADXF_GetPtStatEx(int stream);
extern "C" int igAdx_LoadPartition(int stream, const char *path, int mode, int length);
extern "C" unsigned int strlen(const char *);
extern "C" char *strncpy(char *, const char *, unsigned int);
extern "C" int igAdx_FindAfsFile(const char *name);
extern "C" int strcat(char *, const char *);
extern "C" void __dl__FPv(void *);
extern "C" void igAdxFile_StaticInitialize(void);
extern "C" void igAdxFile_StaticFinalize(void);
extern "C" int igAdxAudio_Initialize(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency);
extern "C" int igAdxAudio_CreateHandle(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency,
                                       int initialize);
extern "C" int igAdxAudio_StartMemory(igAdxAudio *audio, int data, int size);
extern "C" int igAdxAudio_CreateHandleAndStartFile(igAdxAudio *audio, const char *name, int maxChannels, int type,
                                                   int maxStreams, int maxFrequency);
extern "C" int igAdxAudio_StartFile(igAdxAudio *audio, const char *name);
extern "C" void igAdxAudio_Shutdown(igAdxAudio *audio);
extern "C" int text_User0[4];
/* The CRI file-system parameters igAdx_SetupIop hands ADXPS2: the host root and the two file-info caches. */
extern "C" AdxHstFsPrm g_adxHostFsParams;
extern "C" AdxFcachePrm g_adxHostFileCache;
extern "C" AdxFcachePrm g_adxDvdFileCache;
extern "C" int g_adxVblankHandlerId;
extern "C" int g_adxMediaMode[4];
extern "C" char g_adxHostRootPath[256];
extern "C" int g_adxPartitionCount[4];
extern "C" char g_adxUseFileInfoCache;
extern "C" unsigned char g_adxIopReady;
extern "C" char g_adxUnusedFlag;
/* An object seen through its vtable: slot 20 is igObject::getMeta. */
class igObjectVirtuals {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual int getMeta();
};
extern "C" int g_igAdx_metaObject[4];
extern "C" char g_adxModulePath[256];
extern "C" int SNDF_Init(int *config);
extern "C" int text_sdrdrv_irx[4];
extern "C" int text_s_cri_adxi_irx[4];
extern "C" int text_9_31s281_2[4];
extern "C" int text_9_18_2[4];
extern "C" int text_cri_ps2_iop_modules_cri_adxi_irx[4];
extern "C" int text_usr_local_cri_ps2_mwlib_iop_drv[4];
extern "C" int text_sdinit_0[4];
extern "C" int text_s_sndfi_irx[4];
extern "C" int text_cri_ps2_iop_modules_sndfi_irx[4];
extern "C" char text_cdvd_fic[16];
extern "C" char g_iopResetPending;
extern "C" void **g_adxPartitionBuffers;
extern "C" int g_stringPool[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    operator char *() const { return p; }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
extern "C" void igAdx_SetInsideFiles(igAdxAfsFileList *files);
extern "C" StringRef StringList_CopyRetained(int list, int index);
struct WaitResult { int code; };
class AdxThread {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual WaitResult sleep(int microseconds);
};
struct ThreadList { char pad[16]; AdxThread **data; };
struct ThreadManager { char pad[8]; ThreadList *threads; };
extern "C" ThreadManager *g_threadManager[4];
extern "C" void igStringObj_Set(igStringObj *string, const char *text);
extern "C" void igStringObj_ToLower(igStringObj *string);
extern "C" void igStringObj_ToInt(igStringObj *string, int *value);
extern "C" void igNamedObject_SetName(igAdxAfsFile *object, const char *name);
extern "C" char *g_stringObjEmptyText[4];
extern "C" int emptyString[4];
extern "C" const char g_pathSeparator[2];
extern "C" void igAdxAfsFile_GetPath(igAdxAfsFile *file, char *path);
/* The scratch string, the per-partition file names and the AFS files, each released when the program exits. */
extern "C" {
igSmartPointer<igStringObj> g_adxScratchString(0, kRetainReference);
igSmartPointer<igStringRefList> g_adxPartitionNames;
igSmartPointer<igAdxAfsFileList> g_adxAfsFileList;
}

static inline igAdxAfsFile *afsFileAt(igAdxAfsFileList *list, int index) {
    return ((igAdxAfsFile **)list->_data)[index];
}

int igAdxAudio_Initialize(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency) {
    if (audio->_bIsInitialized == 0) {
        int samples, sectors, streamSize;
        audio->_iMaxChannels = maxChannels;
        audio->_iType = type;
        audio->_iMaxStreams = maxStreams;
        audio->_iMaxFrequency = maxFrequency;
        samples = audio->_iMaxFrequency / 1000 * (audio->_iMaxChannels * 25000) / 44;
        sectors = ((audio->_iMaxStreams + 1) * samples + 0x800) / 0x800;
        streamSize = (sectors << 11) + 0x24;
        { int decodeSize = audio->_iMaxChannels * 0x40C0; audio->_iWorkSize = decodeSize + streamSize + 0x40; }
        audio->_pWorkArea = Memory_AllocateAlignedWithAllocator(audio->_iWorkSize, 16, igObject_GetAllocator(audio));
        if (audio->_pWorkArea == 0) return 0;
        audio->_bIsInitialized = 1;
    }
    return 1;
}

int igAdxAudio_CreateHandle(igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency,
                            int initialize) {
    if (audio->_bIsInitialized == 0) {
        if (initialize != 0) {
            igAdxAudio_Initialize(audio, maxChannels, type, maxStreams, maxFrequency);
            audio->_bIsInitialized = 1;
        } else {
            return 0;
        }
    }
    if (audio->_adxt == 0) {
        audio->_adxt = ADXT_Create(audio->_iMaxChannels, audio->_pWorkArea, audio->_iWorkSize);
        if (audio->_adxt == 0) {
            return 0;
        }
    }
    return audio->_adxt;
}

int igAdxAudio_StartMemory(igAdxAudio *audio, int data, int size) {
    if (audio->_adxt == 0) {
        audio->_adxt = igAdxAudio_CreateHandle(audio, audio->_iMaxChannels, audio->_iType, audio->_iMaxStreams,
                                               audio->_iMaxFrequency, 0);
        if (audio->_adxt == 0) {
            return 0;
        }
    }
    ADXT_StartMemIdx(audio->_adxt, data, size);
    return 1;
}

int igAdxAudio_CreateHandleAndStartFile(igAdxAudio *audio, const char *name, int maxChannels, int type,
                                        int maxStreams, int maxFrequency) {
    int index;
    igAdxAfsFile *file;

    audio->_adxt = igAdxAudio_CreateHandle(audio, maxChannels, type, maxStreams, maxFrequency, 1);
    index = igAdx_FindAfsFile(name);
    if (index != -1) {
        file = afsFileAt(g_adxAfsFileList.p, index);
        ADXT_StartAfs(audio->_adxt, file->_ptNumber, file->_fileNumber);
    } else {
        ADXT_StartFname(audio->_adxt, name);
    }
    return 1;
}

int igAdxAudio_StartFile(igAdxAudio *audio, const char *name) {
    int index;
    igAdxAfsFile *file;

    if (audio->_adxt != 0) {
        index = igAdx_FindAfsFile(name);
        if (index != -1) {
            file = afsFileAt(g_adxAfsFileList.p, index);
            ADXT_StartAfs(audio->_adxt, file->_ptNumber, file->_fileNumber);
        } else {
            ADXT_StartFname(audio->_adxt, name);
        }
        return 1;
    }
    return igAdxAudio_CreateHandleAndStartFile(audio, name, audio->_iMaxChannels, audio->_iType,
                                               audio->_iMaxStreams, audio->_iMaxFrequency);
}

void igAdxAudio_Stop(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt != 0) {
        ADXT_Stop(adxt);
    }
}

void igAdxAudio_Pause(igAdxAudio *audio, int pause) {
    int adxt = audio->_adxt;
    if (adxt != 0) {
        ADXT_Pause(adxt, pause);
    }
}

int igAdxAudio_GetPauseState(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return -1;
    }
    return ADXT_GetStatPause(adxt);
}

void igAdxAudio_Shutdown(igAdxAudio *audio) {
    if (audio->_adxt != 0) {
        ADXT_Destroy(audio->_adxt);
    }
    if (audio->_pWorkArea != 0) {
        Memory_FreeBufferWithAllocator(audio->_pWorkArea, igObject_GetAllocator(audio));
    }
}

void igAdxAudio_SetOutVolume(igAdxAudio *audio, int volume) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt != 0) {
        ADXT_SetOutVol(adxt, volume);
    }
}

int igAdxAudio_GetOutVolume(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return 0;
    }
    return ADXT_GetOutVol(adxt);
}

int igAdxAudio_GetStatus(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return -1;
    }
    return ADXT_GetStat(adxt);
}

void igAdx_CreateScratchString(void) {
    int allocator;
    igObject *old;

    allocator = Memory_GetAllocatorByName(&text_User0[0]);
    old = g_adxScratchString.p;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    g_adxScratchString.p = igStringObj_Create(allocator);
}

void igAdx_Shutdown(void) {
    int allocator;
    igObject *object;

    igAdx_SetPartitionCount(0);
    object = g_adxAfsFileList.p;
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
    g_adxAfsFileList.p = 0;
    object = g_adxScratchString.p;
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
    g_adxScratchString.p = 0;
    mwPlyFinishSfdFx();
    SNDF_Finish();
    DisableIntc(2);
    RemoveIntcHandler(2, g_adxVblankHandlerId);
    allocator = Memory_GetAllocatorByName(&text_User0[0]);
    if (g_adxHostFileCache.buf != 0) {
        Memory_FreeBufferWithAllocator(g_adxHostFileCache.buf, allocator);
        g_adxHostFileCache.buf = 0;
    }
    if (g_adxDvdFileCache.buf != 0) {
        Memory_FreeBufferWithAllocator(g_adxDvdFileCache.buf, allocator);
        g_adxDvdFileCache.buf = 0;
    }
    ADXM_ShutdownThrd();
}

void Gap__igAdx__constructFields(void)
{
    Gap__Core__igObject__constructFields();
}

void Gap__igAdx__resetFields(void) {
    igAdxAfsFileList *files;
    Gap__Core__igObject__resetFields();
    g_adxVblankHandlerId = 0;
    g_adxIopReady = 0;
    g_adxUnusedFlag = 0;
    g_adxMediaMode[0] = 0;
    g_adxUseFileInfoCache = 0;
    memset(&g_adxHostRootPath[0], 0, 0x100);
    files = g_adxAfsFileList.p;
    IG_OBJECT_RELEASE(files);
    g_adxAfsFileList.p = 0;
    g_adxPartitionCount[0] = 0;
}

void Gap__igAdx__userConstruct(igObject *self) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectVirtuals *)self)->getMeta(), 1);
}

int Gap__igAdx__getMeta(void)
{
    return g_igAdx_metaObject[0];
}

void Gap__igAdx__destructFields(void)
{
}

void Gap__igAdx__userDestruct(igObject *self) {
    igMetaObject_CountInstances(((igObjectVirtuals *)self)->getMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

void igAdx_ErrorCallback(void) {

}

void igAdx_SetModulePath(int path) {
    if (path != 0) {
        strcpy(&g_adxModulePath[0], path);
        return;
    }
    memset(&g_adxModulePath[0], 0, 0x100);
}

void igAdx_SetHostRootPath(int path) {
    if (path != 0) {
        strcpy(&g_adxHostRootPath[0], path);
        return;
    }
    memset(&g_adxHostRootPath[0], 0, 0x100);
}

int igAdx_SetupIop(void) {
    int sdrdrvResult;
    int adxiResult;
    int sndfiResult;
    char path[512];
    int sndfConfig[4];
    int allocator;

    if (g_adxIopReady != 0) {
        return 1;
    }
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    sceCdInit(0);
    switch (g_adxMediaMode[0]) {
    case 1:
        sceCdMmode(1);
        break;
    case 2:
        sceCdMmode(2);
        break;
    }
    g_iopResetPending = 0;
    igPsx2_LoadIopModule(&sdrdrvResult, &text_sdrdrv_irx[0], 1, 0, 0);
    sceSdRemoteInit();
    sceSdRemote(1, 0x8000, 0);
    sceSdRemote(1, 0x8010, 0x980, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA80, 0x3FFF);
    sceSdRemote(1, 0x8010, 0x981, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA81, 0x3FFF);
    if (g_adxModulePath[0] != 0) {
        sprintf(path, &text_s_cri_adxi_irx[0], &g_adxModulePath[0]);
    } else if (strcmp(&text_9_31s281_2[0], &text_9_18_2[0]) == 0) {
        sprintf(path, &text_cri_ps2_iop_modules_cri_adxi_irx[0]);
    } else {
        sprintf(path, &text_usr_local_cri_ps2_mwlib_iop_drv[0]);
    }
    igPsx2_LoadIopModule(&adxiResult, path, 0, 0x13, &text_sdinit_0[0]);
    if (g_adxModulePath[0] != 0) {
        sprintf(path, &text_s_sndfi_irx[0], &g_adxModulePath[0]);
    } else {
        sprintf(path, &text_cri_ps2_iop_modules_sndfi_irx[0]);
    }
    igPsx2_LoadIopModule(&sndfiResult, path, 0, 0, 0);
    memset(sndfConfig, 0, 0x10);
    sndfConfig[0] = 0x30000;
    sndfConfig[1] = 0;
    sndfConfig[2] = 0;
    sndfConfig[3] = 0;
    SNDF_Init(sndfConfig);
    ADXPS2_SetupMfs(0);
    if (g_adxHostRootPath[0] != 0) {
        memset(&g_adxHostFsParams, 0, 0x10);
        g_adxHostFsParams.rootdir = &g_adxHostRootPath[0];
        ADXPS2_SetupHostFs(&g_adxHostFsParams);
    } else {
        ADXPS2_SetupHostFs(0);
    }
    allocator = Memory_GetAllocatorByName(&text_User0[0]);
    if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
        memset(&g_adxHostFileCache, 0, 0x10);
        g_adxHostFileCache.flist = &text_cdvd_fic[0];
        g_adxHostFileCache.fnamelen = 0x20;
        g_adxHostFileCache.bufsize = ((g_adxHostFileCache.fnamelen + 1) * 0xD) + 0x68;
        g_adxHostFileCache.buf = (void *)Memory_AllocateAlignedWithAllocator(g_adxHostFileCache.bufsize, 0x10, allocator);
        ADXPS2_LoadFcacheHst(&g_adxHostFileCache);
    }
    if (g_adxMediaMode[0] != 0) {
        ADXPS2_SetupDvdFs(0);
        if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
            memset(&g_adxDvdFileCache, 0, 0x10);
            g_adxDvdFileCache.flist = &text_cdvd_fic[0];
            g_adxDvdFileCache.fnamelen = 0x20;
            g_adxDvdFileCache.bufsize = ((g_adxDvdFileCache.fnamelen + 1) * 0xD) + 0x68;
            g_adxDvdFileCache.buf = (void *)Memory_AllocateAlignedWithAllocator(g_adxDvdFileCache.bufsize, 0x10, allocator);
            ADXPS2_LoadFcacheDvd(&g_adxDvdFileCache);
        }
    }
    DisableIntc(2);
    g_adxVblankHandlerId = AddIntcHandler(2, &ADXM_ExecVint, 0);
    EnableIntc(2);
    g_adxIopReady = 1;
    return 1;
}

int igAdx_SetupOptional(void)
{
    return 1;
}

int igAdx_Initialize(int setupOptional) {
    int ok;

    ok = igAdx_SetupIop() & 0xFF;
    if ((ok != 0) && (setupOptional != 0)) {
        ok = igAdx_SetupOptional() & 0xFF;
    }
    ADXM_SetupThrd(0);
    ADXM_SetCbErr(igAdx_ErrorCallback, 0);
    ADXT_Init();
    SNDF_Start();
    return ok;
}

void igAdx_ExecVsync(void)
{
    ADXM_ExecVsyncFrame();
}

void igAdx_ExecServer(int) {
    ADXM_ExecMain();
    SNDF_ExecServer();
}

/* `0 < n` on the inner guards, `n > 0` on the outer, and the reference is released through a local
 * object pointer. */
void igAdx_SetPartitionCount(int count) {
    int buffer;
    int allocator;
    int clearOffset;
    int freed;
    int freeOffset;
    int cleared;
    igObject *object;

    allocator = Memory_GetAllocatorByName(&text_User0[0]);
    if (g_adxPartitionBuffers != 0) {
        if (g_adxPartitionCount[0] > 0) {
            freed = 0;
            if (0 < g_adxPartitionCount[0]) {
                freeOffset = 0;
                do {
                    buffer = *(int *)((int)g_adxPartitionBuffers + freeOffset);
                    if (buffer != 0) {
                        Memory_FreeBufferWithAllocator(buffer, allocator);
                    }
                    freed += 1;
                    freeOffset += 4;
                } while (freed < g_adxPartitionCount[0]);
            }
        }
        Memory_FreeBufferWithAllocator(g_adxPartitionBuffers, allocator);
    }
    g_adxPartitionCount[0] = count;
    if (count > 0) {
        g_adxPartitionBuffers = (void **)Memory_AllocateAlignedWithAllocator(count * 4, 0x10, allocator);
        cleared = 0;
        if (0 < g_adxPartitionCount[0]) {
            clearOffset = 0;
            do {
                cleared += 1;
                *(int *)((int)g_adxPartitionBuffers + clearOffset) = 0;
                clearOffset += 4;
            } while (cleared < g_adxPartitionCount[0]);
        }
        object = g_adxPartitionNames.p;
        if (object != 0) {
            object->_refCount = (int)object->_refCount - 1;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
        g_adxPartitionNames.p = (igStringRefList *)igStringRefList_Create(allocator);
    }
}

void igAdx_AddPartitionName(int partition, char *name) {
    int pool;
    int empty;
    if (name != 0) {
        char *interned;
        if (name == 0) {
            interned = 0;
        } else {
            if (g_stringPool[0] == 0) {
                pool = StringPool_Allocate(16);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            interned = StringPool_Intern(g_stringPool[0], name);
        }
        {
            StringRef token(interned);
            StringList_AppendRetained(g_adxPartitionNames.p, &token);
        }
    } else {
        igStringRefList *names;
        int n;
        int i;
        int *old;
        int **slot;
        int *blank;
        names = g_adxPartitionNames.p;
        n = names->_count;
        i = 0;
        if (0 < n) {
            do {
                slot = &((int **)names->_data)[i];
                if (g_stringPool[0] == 0) {
                    pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                blank = (int *)StringPool_Intern(g_stringPool[0], 0);
                old = *slot;
                if (old != 0) {
                    int *header = old - 2;
                    pool = old[-1] - 1;
                    old[-1] = pool;
                    if (pool == 0) StringChunk_ReleaseHeader(*header, header);
                }
                i++;
                *slot = blank;
            } while (i < n);
        }
        names->_count = 0;
        empty = g_adxPartitionNames.p->_count > 0;
        if (empty == 0) List_Reserve(g_adxPartitionNames.p, 0, 4);
        g_adxPartitionNames.clear();
        {
            igAdxAfsFileList *files = g_adxAfsFileList.p;
            if (files != 0) {
                int fileCount = files->_count;
                int f;
                int m, j;
                for (f = 0; f < fileCount; f++) {
                    igAdxAfsFile *file = afsFileAt(files, f);
                    IG_OBJECT_RELEASE(file);
                }
                m = files->_count;
                for (j = 0; j < m; j++) ((igAdxAfsFile **)files->_data)[j] = 0;
                files->_count = 0;
                empty = g_adxAfsFileList.p->_count > 0;
                if (empty == 0) List_Reserve(g_adxAfsFileList.p, 0, 4);
                g_adxAfsFileList.clear();
            }
        }
    }
}

void igAdx_SetInsideFiles(igAdxAfsFileList *files) {
    igAdxAfsFileList *old;
    if (files != 0) {
        if (files != 0) {
            files->_refCount = files->_refCount + 1;
        }
        old = g_adxAfsFileList.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        g_adxAfsFileList.p = files;
    }
}

int igAdx_LoadPartition(int stream, const char *path, int mode, int length)
{
    int size;
    char *name;
    bool waiting;

    if (!g_adxIopReady) return 0;
    size = ((length + 1) * 2 + 282) & ~3;
    if (size > 0) {
        g_adxPartitionBuffers[stream] = ((void *)Memory_AllocateAlignedWithAllocator(size, 16, ((void *)Memory_GetAllocatorByName(((char *)text_User0)))));
    }
    igAdx_AddPartitionName(stream, (char *)path);
    name = StringList_CopyRetained((int)g_adxPartitionNames.p, stream).p;
    ADXF_LoadPartitionNw(stream, name, mode, g_adxPartitionBuffers[stream]);
    waiting = true;
    do {
        switch (ADXF_GetPtStatEx(stream)) {
        case 3:
            waiting = false;
            break;
        case 4:
            return 0;
        default:
            igAdx_ExecServer(0);
            break;
        }
        g_threadManager[0]->threads->data[0]->sleep(3333333);
    } while (waiting);
    return 1;
}

/* The index of `name` in the AFS file list, or -1. Entry 0 is the direct entry: a name
 * `[p,f]...` sets it to partition p, file f. */
int igAdx_FindAfsFile(const char *name) {
    int partition;
    int fileNumber;
    char digits[16];
    char path[256];
    int close;
    unsigned int i;
    int k;
    int n;
    if (g_adxAfsFileList.p) {
        close = -1;
        if (name[0] == '[') {
            for (i = 1; i < strlen(name); i++) {
                if (name[i] == ']') {
                    close = i + 1;
                    break;
                }
            }
            if (close != -1 && close >= 3) {
                igAdxAfsFile *entry;
                memset(digits, 0, 16);
                strncpy(digits, name + 1, 1);
                igStringObj_Set(g_adxScratchString.p, digits);
                igStringObj_ToInt(g_adxScratchString.p, &partition);
                strncpy(digits, name + 3, close - 4);
                igStringObj_Set(g_adxScratchString.p, digits);
                igStringObj_ToInt(g_adxScratchString.p, &fileNumber);
                entry = afsFileAt(g_adxAfsFileList.p, 0);
                igNamedObject_SetName(entry, name);
                entry->_ptNumber = partition;
                entry->_fileNumber = fileNumber;
                return 0;
            }
        }
        n = g_adxAfsFileList.p->_count;
        igStringObj_Set(g_adxScratchString.p, name);
        igStringObj_ToLower(g_adxScratchString.p);
        for (k = 1; k < n; k++) {
            igAdxAfsFile_GetPath(afsFileAt(g_adxAfsFileList.p, k), path);
            const char *text = (const char *)g_adxScratchString.p->_buffer;
            text = (text == 0) ? g_stringObjEmptyText[0] : text;
            if (strcmp(text, path) == 0) {
                return k;
            }
        }
    }
    return -1;
}

/* The file's path: its folders' names and its own, joined by '/'. */
void igAdxAfsFile_GetPath(igAdxAfsFile *file, char *path) {
    int i;
    int offset;
    if (path != 0) {
        if (file->_pathList == 0) {
            strcpy(path, file->_name ? (char *)file->_name : (char *)&emptyString[0]);
            return;
        }
        *path = 0;
        i = 0;
        if (0 < ((igNamedObjectList *)file->_pathList)->_count) {
            offset = 0;
            do {
                igNamedObject *folder = *(igNamedObject **)((char *)((igNamedObjectList *)file->_pathList)->_data + offset);
                strcat(path, folder->_name ? (char *)folder->_name : (char *)&emptyString[0]);
                strcat(path, g_pathSeparator);
                i += 1;
                offset += 4;
            } while (i < ((igNamedObjectList *)file->_pathList)->_count);
        }
        strcat(path, file->_name ? (char *)file->_name : (char *)&emptyString[0]);
    }
}

void igAdxFile_StaticInitialize(void)
{
}

void igAdxFile_StaticFinalize(void)
{
}

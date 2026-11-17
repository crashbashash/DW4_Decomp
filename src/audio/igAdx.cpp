#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"
#include "dw4/cri/adx_ps2.h"
#include "dw4/igAdx.h"
#include "dw4/igAdxAudio.h"
#include "dw4/igAdxFile.h"
#pragma push
#pragma readonly_strings on
#include "dw4/igObject.h"
#include "dw4/igMemory.h"
extern "C" {
#include "dw4/cri/cri_adxt.h"
}
#include "dw4/igStringObj.h"
#include "dw4/libkernl.h"
extern "C" int SNDF_Finish(...);
extern "C" int mwPlyFinishSfdFx(...);
#include "dw4/eekernel.h"
extern "C" void Gap__igAdx__constructFields(igObject *self, int flags);
extern "C" void Gap__igAdx__resetFields(igObject *self, int flags);
#include "dw4/igMetaObject.h"
extern "C" void Gap__igAdx__userConstruct(igObject *self);
extern "C" int Gap__igAdx__getMeta(void);
extern "C" void Gap__igAdx__destructFields(void);
extern "C" void Gap__igAdx__userDestruct(igObject *self);
extern "C" void igAdx_ErrorCallback(void *obj, char *msg);
#include <string.h>
extern "C" {
#include "dw4/sony/sif.h"
}
extern "C" int sceSifInitIopHeap(...);
extern "C" int sceCdInit(int);
extern "C" int sceCdMmode(int);
extern "C" int sceSdRemoteInit(...);
/* Kept here: its only declaration is in cri/sndf.h, whose own libc and SIF prototypes conflict with the Sony homes. */
extern "C" int sceSdRemote(int arg, int command, ...);
#include <stdio.h>
extern "C" int igPsx2_LoadIopModule(...);
extern "C" int igAdx_SetupIop(void);
extern "C" int igAdx_SetupOptional(void);
extern "C" int SNDF_Start(...);
extern "C" int SNDF_ExecServer(...);
#include "dw4/igDataLists.h"
#include "dw4/StringPool.h"
extern "C" unsigned char igAdxAudio_CreateHandleAndStartFile(igAdxAudio *audio, const char *name, int maxChannels, int type,
                                                   int maxStreams, int maxFrequency);
/* The CRI file-system parameters igAdx_SetupIop hands ADXPS2: the host root and the two file-info caches. */
extern "C" {
AdxHstFsPrm g_adxHostFsParams;
AdxFcachePrm g_adxHostFileCache;
AdxFcachePrm g_adxDvdFileCache;
int g_adxVblankHandlerId;
int g_adxMediaMode;
char g_adxModulePath[256];
char g_adxHostRootPath[256];
char g_adxUseFileInfoCache;
unsigned char g_adxIopReady;
char g_adxUnusedFlag;
}
extern "C" int SNDF_Init(int *config);
#include "dw4/igPsx2File.h"
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
    operator char *() const { return p; }
};
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
#include "dw4/igThread.h"
#include "dw4/emptyString.h"
#include "dw4/igNamedObject.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/list-services.h"
extern "C" void igAdxAfsFile_GetPath(igAdxAfsFile *file, char *path);
/* The scratch string, the per-partition file names and the AFS files, each released when the program exits. */
extern "C" {
igSmartPointer<igStringObj> g_adxScratchString(0, kRetainReference);
int g_adxPartitionCount;
void **g_adxPartitionBuffers;
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
        audio->_pWorkArea = (int)Memory_AllocateAlignedWithAllocator(audio->_iWorkSize, 16, igObject_GetAllocator(audio));
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
        audio->_adxt = (int)ADXT_Create(audio->_iMaxChannels, (char *)audio->_pWorkArea, audio->_iWorkSize);
        if (audio->_adxt == 0) {
            return 0;
        }
    }
    return audio->_adxt;
}

int igAdxAudio_StartMemory(igAdxAudio *audio, void *data, int size) {
    if (audio->_adxt == 0) {
        audio->_adxt = igAdxAudio_CreateHandle(audio, audio->_iMaxChannels, audio->_iType, audio->_iMaxStreams,
                                               audio->_iMaxFrequency, 0);
        if (audio->_adxt == 0) {
            return 0;
        }
    }
    ADXT_StartMemIdx((AdxtObj *)audio->_adxt, (AcxHeader *)data, size);
    return 1;
}

unsigned char igAdxAudio_CreateHandleAndStartFile(igAdxAudio *audio, const char *name, int maxChannels, int type,
                                        int maxStreams, int maxFrequency) {
    int index;
    igAdxAfsFile *file;

    audio->_adxt = igAdxAudio_CreateHandle(audio, maxChannels, type, maxStreams, maxFrequency, 1);
    index = igAdx_FindAfsFile(name);
    if (index != -1) {
        file = afsFileAt(g_adxAfsFileList.p, index);
        ADXT_StartAfs((AdxtObj *)audio->_adxt, file->_ptNumber, file->_fileNumber);
    } else {
        ADXT_StartFname((AdxtObj *)audio->_adxt, (char *)name);
    }
    return 1;
}

unsigned char igAdxAudio_StartFile(igAdxAudio *audio, const char *name) {
    int index;
    igAdxAfsFile *file;

    if (audio->_adxt != 0) {
        index = igAdx_FindAfsFile(name);
        if (index != -1) {
            file = afsFileAt(g_adxAfsFileList.p, index);
            ADXT_StartAfs((AdxtObj *)audio->_adxt, file->_ptNumber, file->_fileNumber);
        } else {
            ADXT_StartFname((AdxtObj *)audio->_adxt, (char *)name);
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
        ADXT_Stop((AdxtObj *)adxt);
    }
}

void igAdxAudio_Pause(igAdxAudio *audio, int pause) {
    int adxt = audio->_adxt;
    if (adxt != 0) {
        ADXT_Pause((AdxtObj *)adxt, pause);
    }
}

int igAdxAudio_GetPauseState(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return -1;
    }
    return ADXT_GetStatPause((AdxtObj *)adxt);
}

void igAdxAudio_Shutdown(igAdxAudio *audio) {
    if (audio->_adxt != 0) {
        ADXT_Destroy((AdxtObj *)audio->_adxt);
    }
    if (audio->_pWorkArea != 0) {
        Memory_FreeBufferWithAllocator((void *)audio->_pWorkArea, igObject_GetAllocator(audio));
    }
}

void igAdxAudio_SetOutVolume(igAdxAudio *audio, int volume) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt != 0) {
        ADXT_SetOutVol((AdxtObj *)adxt, volume);
    }
}

int igAdxAudio_GetOutVolume(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return 0;
    }
    return ADXT_GetOutVol((AdxtObj *)adxt);
}

int igAdxAudio_GetStatus(igAdxAudio *audio) {
    int adxt;

    adxt = audio->_adxt;
    if (adxt == 0) {
        return -1;
    }
    return ADXT_GetStat((AdxtObj *)adxt);
}

void igAdx_CreateScratchString(void) {
    igMemoryPoolView *allocator;
    igObject *old;

    allocator = Memory_GetAllocatorByName("User0");
    old = g_adxScratchString.p;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    g_adxScratchString.p = (igStringObj *)(igStringObj_Create((int)allocator));
}

void igAdx_Shutdown(void) {
    igMemoryPoolView *allocator;
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
    allocator = Memory_GetAllocatorByName("User0");
    if (g_adxHostFileCache.buf != 0) {
        Memory_FreeBufferWithAllocator((void *)g_adxHostFileCache.buf, allocator);
        g_adxHostFileCache.buf = 0;
    }
    if (g_adxDvdFileCache.buf != 0) {
        Memory_FreeBufferWithAllocator((void *)g_adxDvdFileCache.buf, allocator);
        g_adxDvdFileCache.buf = 0;
    }
    ADXM_ShutdownThrd();
}

void Gap__igAdx__constructFields(igObject *self, int flags)
{
    Gap__Core__igObject__constructFields(self, flags);
}

void Gap__igAdx__resetFields(igObject *self, int flags) {
    igAdxAfsFileList *files;
    Gap__Core__igObject__resetFields(self, flags);
    g_adxVblankHandlerId = 0;
    g_adxIopReady = 0;
    g_adxUnusedFlag = 0;
    g_adxMediaMode = 0;
    g_adxUseFileInfoCache = 0;
    memset(&g_adxHostRootPath[0], 0, 0x100);
    files = g_adxAfsFileList.p;
    IG_OBJECT_RELEASE(files);
    g_adxAfsFileList.p = 0;
    g_adxPartitionCount = 0;
}

void Gap__igAdx__userConstruct(igObject *self) {
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
}

int Gap__igAdx__getMeta(void)
{
    return (int)g_igAdx_metaObject;
}

void Gap__igAdx__destructFields(void)
{
}

void Gap__igAdx__userDestruct(igObject *self) {
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

void igAdx_ErrorCallback(void *obj, char *msg) {

}

void igAdx_SetModulePath(const char *path) {
    if (path != 0) {
        strcpy(&g_adxModulePath[0], path);
        return;
    }
    memset(&g_adxModulePath[0], 0, 0x100);
}

void igAdx_SetHostRootPath(const char *path) {
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
    igMemoryPoolView *allocator;

    if (g_adxIopReady != 0) {
        return 1;
    }
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    sceCdInit(0);
    switch (g_adxMediaMode) {
    case 1:
        sceCdMmode(1);
        break;
    case 2:
        sceCdMmode(2);
        break;
    }
    g_igPsx2_resetIopServices = 0;
    igPsx2_LoadIopModule(&sdrdrvResult, "sdrdrv.irx", 1, 0, 0);
    sceSdRemoteInit();
    sceSdRemote(1, 0x8000, 0);
    sceSdRemote(1, 0x8010, 0x980, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA80, 0x3FFF);
    sceSdRemote(1, 0x8010, 0x981, 0x3FFF);
    sceSdRemote(1, 0x8010, 0xA81, 0x3FFF);
    if (g_adxModulePath[0] != 0) {
        sprintf(path, "%s/cri_adxi.irx", &g_adxModulePath[0]);
    } else if (strcmp("9.31s281", "9.18") == 0) {
        sprintf(path, "/cri/ps2/iop/modules/cri_adxi.irx");
    } else {
        sprintf(path, "/usr/local/cri/ps2/mwlib/iop/drv/cri_adxi.irx");
    }
    igPsx2_LoadIopModule(&adxiResult, path, 0, 0x13, "sdinit=0\0spucore=1");
    if (g_adxModulePath[0] != 0) {
        sprintf(path, "%s/sndfi.irx", &g_adxModulePath[0]);
    } else {
        sprintf(path, "/cri/ps2/iop/modules/sndfi.irx");
    }
    igPsx2_LoadIopModule(&sndfiResult, path, 0, 0, 0);
    memset(sndfConfig, 0, 0x10);
    sndfConfig[0] = 0x30000;
    sndfConfig[1] = 0;
    sndfConfig[2] = 0;
    sndfConfig[3] = 0;
    SNDF_Init(sndfConfig);
    ADXPS2_SetupMemFs(0);
    if (g_adxHostRootPath[0] != 0) {
        memset(&g_adxHostFsParams, 0, 0x10);
        g_adxHostFsParams.rootdir = &g_adxHostRootPath[0];
        ADXPS2_SetupHostFs(&g_adxHostFsParams);
    } else {
        ADXPS2_SetupHostFs(0);
    }
    allocator = Memory_GetAllocatorByName("User0");
    if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
        memset(&g_adxHostFileCache, 0, 0x10);
        g_adxHostFileCache.flist = "cdvd.fic";
        g_adxHostFileCache.fnamelen = 0x20;
        g_adxHostFileCache.bufsize = ((g_adxHostFileCache.fnamelen + 1) * 0xD) + 0x68;
        g_adxHostFileCache.buf = (void *)Memory_AllocateAlignedWithAllocator(g_adxHostFileCache.bufsize, 0x10, allocator);
        ADXPS2_LoadFcacheHost(&g_adxHostFileCache);
    }
    if (g_adxMediaMode != 0) {
        ADXPS2_SetupDvdFs(0);
        if ((*(unsigned char *)&g_adxUseFileInfoCache) != 0) {
            memset(&g_adxDvdFileCache, 0, 0x10);
            g_adxDvdFileCache.flist = "cdvd.fic";
            g_adxDvdFileCache.fnamelen = 0x20;
            g_adxDvdFileCache.bufsize = ((g_adxDvdFileCache.fnamelen + 1) * 0xD) + 0x68;
            g_adxDvdFileCache.buf = (void *)Memory_AllocateAlignedWithAllocator(g_adxDvdFileCache.bufsize, 0x10, allocator);
            ADXPS2_LoadFcacheDvd(&g_adxDvdFileCache);
        }
    }
    DisableIntc(2);
    g_adxVblankHandlerId = AddIntcHandler(2, (int (*)(int))&ADXM_ExecVint, 0);
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
    igMemoryPoolView *allocator;
    int clearOffset;
    int freed;
    int freeOffset;
    int cleared;
    igObject *object;

    allocator = Memory_GetAllocatorByName("User0");
    if (g_adxPartitionBuffers != 0) {
        if (g_adxPartitionCount > 0) {
            freed = 0;
            if (0 < g_adxPartitionCount) {
                freeOffset = 0;
                do {
                    buffer = *(int *)((int)g_adxPartitionBuffers + freeOffset);
                    if (buffer != 0) {
                        Memory_FreeBufferWithAllocator((void *)buffer, allocator);
                    }
                    freed += 1;
                    freeOffset += 4;
                } while (freed < g_adxPartitionCount);
            }
        }
        Memory_FreeBufferWithAllocator((void *)g_adxPartitionBuffers, allocator);
    }
    g_adxPartitionCount = count;
    if (count > 0) {
        g_adxPartitionBuffers = (void **)Memory_AllocateAlignedWithAllocator(count * 4, 0x10, allocator);
        cleared = 0;
        if (0 < g_adxPartitionCount) {
            clearOffset = 0;
            do {
                cleared += 1;
                *(int *)((int)g_adxPartitionBuffers + clearOffset) = 0;
                clearOffset += 4;
            } while (cleared < g_adxPartitionCount);
        }
        object = g_adxPartitionNames.p;
        if (object != 0) {
            object->_refCount = (int)object->_refCount - 1;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
        g_adxPartitionNames.p = (igStringRefList *)igStringRefList_Create((int)allocator);
    }
}

void igAdx_AddPartitionName(int partition, const char *name) {
    int pool;
    int empty;
    if (name != 0) {
        char *interned;
        if (name == 0) {
            interned = 0;
        } else {
            if (g_stringPool == 0) {
                pool = (int)StringPool_Allocate(16);
                if (pool != 0) pool = (int)StringPool_Construct((StringPool *)pool);
                g_stringPool = (StringPool *)pool;
            }
            interned = StringPool_Intern(g_stringPool, name);
        }
        {
            StringRef token(interned);
            StringList_AppendRetained(g_adxPartitionNames.p, &token.p);
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
                if (g_stringPool == 0) {
                    pool = (int)StringPool_Allocate(16);
                    if (pool != 0) pool = (int)StringPool_Construct((StringPool *)pool);
                    g_stringPool = (StringPool *)pool;
                }
                blank = (int *)StringPool_Intern(g_stringPool, 0);
                old = *slot;
                if (old != 0) {
                    int *header = old - 2;
                    pool = old[-1] - 1;
                    old[-1] = pool;
                    if (pool == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                i++;
                *slot = blank;
            } while (i < n);
        }
        names->_count = 0;
        empty = g_adxPartitionNames.p->_count > 0;
        if (empty == 0) List_Reserve((igDataList *)g_adxPartitionNames.p, 0, 4);
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
                if (empty == 0) List_Reserve((igDataList *)g_adxAfsFileList.p, 0, 4);
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
        g_adxPartitionBuffers[stream] = ((void *)Memory_AllocateAlignedWithAllocator(size, 16, Memory_GetAllocatorByName("User0")));
    }
    igAdx_AddPartitionName(stream, (char *)path);
    name = StringList_CopyRetained((int)g_adxPartitionNames.p, stream).p;
    ADXF_LoadPartitionNw(stream, name, (void *)mode, (AdxfPtInfo *)g_adxPartitionBuffers[stream]);
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
        ((AdxThread *)g_threadManager->_threadList->_data[0])->sleep(3333333);
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
                igNamedObject_SetName((igNamedObject *)entry, name);
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
            text = (text == 0) ? g_stringObjEmptyText : text;
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
                strcat(path, "/");
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

#pragma pop

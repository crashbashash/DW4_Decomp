#include "dw4/support/reflected.h"
#include "dw4/core/igFileDispatchView.h"
#include "dw4/game/beFileChkObj.h"
#include "dw4/game/beFileListInfoManager.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beFileListInfo.h"
#include "dw4/game/beFont.h"
#include "dw4/game/beLuaInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/core/igNamedObjectInfo.h"
#include "dw4/core/igResource.h"
#include "dw4/support/emptyString.h"
#define CLEAR(T, src) { \
    T *l = (T *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        if (o != 0) { \
            o->_refCount = (int)o->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }

extern "C" void beFileListInfoManager_Stop(void);
extern "C" igMetaObject *beFileListInfoManager_GetMeta(void);
extern "C" void beFileListInfoManager_Activate(beFileListInfoManager *self, int unusedArg);
extern "C" void beFileListInfoManager_Deactivate(beFileListInfoManager *self, int unusedArg);
extern "C" void beFileListInfoManager_Start(beFileListInfoManager *self);
extern "C" int beFileListInfoManager_AddInfo(beFileListInfoManager *self, igObject *info);
extern "C" void beFileListInfoManager_RemoveAllInfo(beFileListInfoManager *self);

extern "C" char ROOTATTR_2[];

/* The one-word list entry List_InsertWords copies from. */
struct InfoWord {
    int *p;
    InfoWord(int *info) : p(info) {}
};

static inline void insertReadInfo(beFileListInfoManager *self, int at, const InfoWord &entry) {
    const InfoWord *word = (const InfoWord *)(int)&entry; /* matching construct: manual - the int round trip keeps the entry addressed through memory */
    int *info = word->p;
    int list = self->_readInfoList;
    if (info != 0) info[1] = info[1] + 1;
    List_InsertWords((igDataList *)list, at, 1, (void *)word);
}

int beFileChkObj_FileExists(beFileChkObj *checker, const char *fileName) {
    if (((igFileDispatchView *)checker->_fd)->OpenFile(fileName, "rb") != 0) {
        ((igFileDispatchView *)checker->_fd)->CloseFile();
        return 1;
    }
    return 0;
}

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void beFileListInfoManager_Activate(beFileListInfoManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void beFileListInfoManager_Deactivate(beFileListInfoManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

void beFileListInfoManager_Start(beFileListInfoManager *self) {
    self->_system = ((int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject));
    self->_messenger = ((int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beMessenger_metaObject));
    self->_sceneInfoManager = ((int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject));
}

void beFileListInfoManager_Stop(void)
{
}

static inline void insertWords(igObjectList *l, int at, int n, igObject **src) {
    int i;
    for (i = 0; i < n; i++) {
        igObject *v = src[i];
        if (v) ++v->_refCount;
    }
    List_InsertWords((igDataList *)l, at, n, (void *)src);
}

int beFileListInfoManager_AddInfo(beFileListInfoManager *self, igObject *info) {
    if (g_beFileListInfo_metaObject == ((igObjectDispatchView *)info)->GetMeta()) {
        igObjectList *list = (igObjectList *)self->_infoList;
        if (list->_count > 0) {
            igObject *first = info;
            insertWords(list, 0, 1, &first);
        } else {
            ObjectList_AppendRetained(list, info);
        }
        self->_proc = 0;
        ((beSystem *)self->_system)->_isSResetEnable = 0;
        return 1;
    }
    if (g_igNamedObjectInfo_metaObject == ((igObjectDispatchView *)info)->GetMeta()) {
        void *found = igInsightCore_FindManager((igInsightCore *)self->_insight, g_beFont_metaObject);
        if (found == 0) return 0;
        beFont_AddFontImages((beFont *)found, (igNamedObjectInfo *)info);
        return 1;
    }
    return 0;
}

void beFileListInfoManager_RemoveAllInfo(beFileListInfoManager *self) {
    igStringRefList *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    CLEAR(igInfoList, self->_infoList)
    CLEAR(igDirectoryList, self->_dirList)
    s5 = (igStringRefList *)self->_fnames;
    s4 = s5->_count;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->_data + off);
            if (g_stringPool == 0) {
                v = (int)StringPool_Allocate(0x10);
                if (v != 0) {
                    v = (int)StringPool_Construct((StringPool *)v);
                }
                g_stringPool = (StringPool *)v;
            }
            s1 = (int *)StringPool_Intern(g_stringPool, 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*hdr, (StringTokenHeader *)hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->_count = 0;
    CLEAR(igInfoList, self->_importantInfoList)
    CLEAR(igInfoList, self->_readInfoList)
    {
        igInfoList *l2 = (igInfoList *)self->_infoList;
        if (!(0 < l2->_count)) {
            List_Reserve((igDataList *)l2, 0, 4);
        }
    }
    {
        igDirectoryList *l2 = (igDirectoryList *)self->_dirList;
        if (!(0 < l2->_count)) {
            List_Reserve((igDataList *)l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)self->_importantInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve((igDataList *)l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)self->_readInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve((igDataList *)l2, 0, 4);
        }
    }
    self->_loaded = 0;
}

/* Points one pool of the global context at the allocator `selector` names (the owner's allocator
 * when g_useOwnerAllocator is set), holding a reference to it. */
#define SET_POOL(pool, selector) { \
    igResource *context; \
    int allocator; \
    int ownerAllocator = (int)((Gap::Core::igObject *)self)->getMemoryPool(); \
    igObject *old; \
    if (g_useOwnerAllocator != 0) { allocator = ownerAllocator; } else { allocator = (int)Memory_GetAllocatorBySelector(selector); } \
    context = (igResource *)g_globalContext; \
    if (allocator != 0) ((igObject *)allocator)->_refCount = ((igObject *)allocator)->_refCount + 1; \
    old = (igObject *)context->pool; \
    if (old != 0) { \
        old->_refCount = old->_refCount - 1; \
        if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); \
    } \
    context->pool = allocator; }

/* One step of loading the file list, called each frame until it returns 1 (every file loaded).
 * With no directory pending it starts loading the next file, the first times switching the global
 * context's pools to the ndmw allocator and then to the default one. Once that directory is loaded
 * it sorts its infos: a Lua info goes straight to the insight core, a scene with cameras or whose
 * scene graph is named ROOTATTR is important, any other scene is a plain info, and every other
 * info is a read info. */
unsigned char beFileListInfoManager_LoadNextFile(beFileListInfoManager *self, igStringRefList *fileNames) {
    igDirectory *dir;
    igInfoList *infos;
    int offset;
    int i;
    int readIndex;
    int j;
    igObjectDispatchView *info;
    igMetaObject *meta;
    igDirectoryList *dirs;
    int fileCount = fileNames->_count;
    if (self->_loaded >= fileCount) return 1;
    dirs = (igDirectoryList *)self->_dirList;
    if (dirs->_count != 0) {
        dir = ((igDirectory **)dirs->_data)[0];
        if (igResource_IsDirectoryLoaded((igResource *)g_globalContext, dir)) {
            igStringRef rootAttr(ROOTATTR_2);
            infos = (igInfoList *)dir->_infoList;
            i = 0;
            if (i < infos->_count) {
                offset = 0;
                do {
                    meta = g_beLuaInfo_metaObject;
                    info = *(igObjectDispatchView **)(infos->_data + offset);
                    if (meta == info->GetMeta()) {
                        igInsightCore_AddInfo((igInsightCore *)self->_insight, (igObject *)info);
                    } else {
                        meta = g_igSceneInfo_metaObject;
                        if (meta == info->GetMeta()) {
                            igSceneInfo *scene;
                            if (info != 0 && ((Gap::Core::igObject *)info)->isOfType(g_igSceneInfo_metaObject) != 0) {
                                scene = (igSceneInfo *)info;
                            } else {
                                scene = 0;
                            }
                            if (scene->_cameras != 0 && ((igObjectList *)scene->_cameras)->_count > 0) {
                                ObjectList_AppendRetained((igObjectList *)self->_importantInfoList, (igObject *)info);
                            } else {
                                char *name = (char *)((igInfo *)scene->_sceneGraph)->_name;
                                char *rootText = name ? name : emptyString;
                                if (rootText == rootAttr.p) {
                                    ObjectList_AppendRetained((igObjectList *)self->_importantInfoList, (igObject *)info);
                                } else {
                                    ObjectList_AppendRetained((igObjectList *)self->_infoList, (igObject *)info);
                                }
                            }
                        } else {
                            /* the test reads the new info's own type, so it never holds here */
                            readIndex = -1;
                            j = 0;
                            if (j < ((igInfoList *)self->_readInfoList)->_count) {
                                do {
                                    igMetaObject *sceneMeta = g_igSceneInfo_metaObject;
                                    if (sceneMeta == info->GetMeta()) {
                                        readIndex = j;
                                        break;
                                    }
                                    j += 1;
                                } while (j < ((igInfoList *)self->_readInfoList)->_count);
                            }
                            if (readIndex == -1) {
                                ObjectList_AppendRetained((igObjectList *)self->_readInfoList, (igObject *)info);
                            } else {
                                insertReadInfo(self, readIndex, InfoWord((int *)info));
                            }
                        }
                    }
                    i += 1;
                    offset += 4;
                } while (i < infos->_count);
            }
            igResource_UnloadDirectory((igResource *)g_globalContext, (const char *)dir->_name);
            CLEAR(igDirectoryList, self->_dirList)
            self->_loaded = self->_loaded + 1;
        }
    } else {
        int remaining = self->_onetimeCount;
        if (remaining > -1) {
            if (remaining == 2) {
                SET_POOL(_objectMemoryPool, kIGMemoryPoolHandleUser0)
                SET_POOL(_dataMemoryPool, kIGMemoryPoolHandleUser0)
            } else if (remaining == 0) {
                SET_POOL(_objectMemoryPool, kIGMemoryPoolHandleUser1)
                SET_POOL(_dataMemoryPool, kIGMemoryPoolHandleUser1)
            }
            self->_onetimeCount = self->_onetimeCount - 1;
        }
        igStringRef fileName = StringList_CopyRetained(fileNames, self->_loaded);
        ObjectList_AppendRetained((igObjectList *)self->_dirList, igResource_LoadDirectory((igResource *)g_globalContext, fileName.p));
    }
    return 0;
}

int beFileListInfoManager_AddReadInfos(beFileListInfoManager *self) {
    int i;
    igObjectList *l;
    int n;
    int k;
    int j;
    igObject *o;
    l = (igObjectList *)self->_readInfoList;
    for (i = 0; i < l->_count; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            igInsightCore_AddInfo((igInsightCore *)self->_insight, o);
        }
        l = (igObjectList *)self->_readInfoList;
    }
    n = ((igObjectList *)self->_readInfoList)->_count;
    for (k = 0; k < n; k++) {
        o = ((igObject **)l->_data)[k];
        if (o != 0) {
            /* matching construct: _refCount is unsigned in the metadata; the retail load is the signed lw */
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m2 = l->_count;
        int j2;
        for (j2 = 0; j2 < m2; j2++) {
            ((igObject **)l->_data)[j2] = 0;
        }
    }
    l->_count = 0;
    return 1;
}

igMetaObject *beFileListInfoManager_GetMeta(void)
{
    return g_beFileListInfoManager_metaObject;
}


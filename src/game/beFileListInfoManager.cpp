#include "dw4/reflected.h"
#include "dw4/igFileDispatchView.h"
#include "dw4/beFileChkObj.h"
#include "dw4/beFileListInfoManager.h"
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
extern "C" void * igInsightCore_FindManager(...);
extern "C" void List_InsertWords(void *, int, int, void *);
extern "C" int StringPool_Allocate(int);
extern "C" int List_Reserve(void *, int, int);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, int);
extern "C" void igInsightCore_AddToScheduler(int, beFileListInfoManager *);
extern "C" void igInsightCore_RemoveFromScheduler(int, beFileListInfoManager *);
extern "C" void beFileListInfoManager_Activate(beFileListInfoManager *self, int unusedArg);
extern "C" void beFileListInfoManager_Deactivate(beFileListInfoManager *self, int unusedArg);
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" void beFileListInfoManager_Start(beFileListInfoManager *self);
extern "C" void beFont_AddFontImages(void *, igObject *);
extern "C" void ObjectList_AppendRetained(igObjectList *, igObject *);
extern "C" igMetaObject *g_igNamedObjectInfo_metaObject;
extern "C" int g_beFont_metaObject[4];
extern "C" igMetaObject *g_beFileListInfo_metaObject;
extern "C" int beFileListInfoManager_AddInfo(beFileListInfoManager *self, igObject *info);
extern "C" int g_stringPool[4];
extern "C" int igObject_Destroy(igObject *);
extern "C" void beFileListInfoManager_RemoveAllInfo(beFileListInfoManager *self);
extern "C" int igInsightCore_AddInfo(int, igObject *);
extern "C" int igObject_IsKindOf(igObject *object, igMetaObject *meta);
extern "C" int igResource_IsDirectoryLoaded(int resource, igDirectory *directory);
extern "C" void igResource_UnloadDirectory(int resource, int name);
extern "C" igObject *igResource_LoadDirectory(int resource, int *name);
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(int key);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_globalContext[4];
extern "C" igMetaObject *g_igSceneInfo_metaObject;
extern "C" igMetaObject *g_beLuaInfo_metaObject;
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" char emptyString[];
extern "C" char ROOTATTR_2[];

/* A pooled string held by reference: the count sits at p[-1], the chunk header at p[-2]. */
struct StringRef {
    int *p;
    StringRef() {}
    StringRef(const StringRef &other) : p(other.p) {}
    ~StringRef() {
        int *s = p;
        if (s != 0) {
            int *header = s - 2;
            int count = s[-1] - 1;
            s[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
extern "C" StringRef StringList_CopyRetained(igStringRefList *list, int index);

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
    List_InsertWords((void *)list, at, 1, (void *)word);
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
    igInsightCore_AddToScheduler(self->_insight, self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void beFileListInfoManager_Deactivate(beFileListInfoManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

void beFileListInfoManager_Start(beFileListInfoManager *self) {
    self->_system = ((int)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]));
    self->_messenger = ((int)igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]));
    self->_sceneInfoManager = ((int)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]));
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
    List_InsertWords(l, at, n, (void *)src);
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
        void *found = igInsightCore_FindManager(self->_insight, g_beFont_metaObject[0]);
        if (found == 0) return 0;
        beFont_AddFontImages(found, info);
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
            if (g_stringPool[0] == 0) {
                v = StringPool_Allocate(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                g_stringPool[0] = v;
            }
            s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
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
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igDirectoryList *l2 = (igDirectoryList *)self->_dirList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)self->_importantInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)self->_readInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    self->_loaded = 0;
}

/* Points one pool of the global context at the allocator `selector` names (the owner's allocator
 * when g_useOwnerAllocator is set), holding a reference to it. */
#define SET_POOL(pool, selector) { \
    igResource *context; \
    int allocator; \
    int ownerAllocator = igObject_GetAllocator(self); \
    igObject *old; \
    if (g_useOwnerAllocator != 0) { allocator = ownerAllocator; } else { allocator = Memory_GetAllocatorBySelector(selector); } \
    context = (igResource *)g_globalContext[0]; \
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
int beFileListInfoManager_LoadNextFile(beFileListInfoManager *self, igStringRefList *fileNames) {
    igDirectory *dir;
    igInfoList *infos;
    int offset;
    int i;
    int readIndex;
    int j;
    igObjectDispatchView *info;
    igMetaObject *meta;
    int *rootName;
    igDirectoryList *dirs;
    int fileCount = fileNames->_count;
    if (self->_loaded >= fileCount) return 1;
    dirs = (igDirectoryList *)self->_dirList;
    if (dirs->_count != 0) {
        dir = ((igDirectory **)dirs->_data)[0];
        if (igResource_IsDirectoryLoaded(g_globalContext[0], dir) != 0) {
            if (ROOTATTR_2 == 0) {
                rootName = 0;
            } else {
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(0x10);
                    if (pool != 0) { pool = StringPool_Construct(pool); }
                    g_stringPool[0] = pool;
                }
                rootName = (int *)StringPool_Intern(g_stringPool[0], (int)ROOTATTR_2);
            }
            StringRef rootAttr;
            rootAttr.p = rootName;
            infos = (igInfoList *)dir->_infoList;
            i = 0;
            if (i < infos->_count) {
                offset = 0;
                do {
                    meta = g_beLuaInfo_metaObject;
                    info = *(igObjectDispatchView **)(infos->_data + offset);
                    if (meta == info->GetMeta()) {
                        igInsightCore_AddInfo(self->_insight, (igObject *)info);
                    } else {
                        meta = g_igSceneInfo_metaObject;
                        if (meta == info->GetMeta()) {
                            igSceneInfo *scene;
                            if (info != 0 && igObject_IsKindOf((igObject *)info, g_igSceneInfo_metaObject) != 0) {
                                scene = (igSceneInfo *)info;
                            } else {
                                scene = 0;
                            }
                            if (scene->_cameras != 0 && ((igObjectList *)scene->_cameras)->_count > 0) {
                                ObjectList_AppendRetained((igObjectList *)self->_importantInfoList, (igObject *)info);
                            } else {
                                int *name = (int *)((igInfo *)scene->_sceneGraph)->_name;
                                int *rootText = name ? name : (int *)emptyString;
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
            igResource_UnloadDirectory(g_globalContext[0], dir->_name);
            CLEAR(igDirectoryList, self->_dirList)
            self->_loaded = self->_loaded + 1;
        }
    } else {
        int remaining = self->_onetimeCount;
        if (remaining > -1) {
            if (remaining == 2) {
                SET_POOL(_objectMemoryPool, kIGMemoryPoolHandleUser0[0])
                SET_POOL(_dataMemoryPool, kIGMemoryPoolHandleUser0[0])
            } else if (remaining == 0) {
                SET_POOL(_objectMemoryPool, kIGMemoryPoolHandleUser1[0])
                SET_POOL(_dataMemoryPool, kIGMemoryPoolHandleUser1[0])
            }
            self->_onetimeCount = self->_onetimeCount - 1;
        }
        StringRef fileName(StringList_CopyRetained(fileNames, self->_loaded));
        ObjectList_AppendRetained((igObjectList *)self->_dirList, igResource_LoadDirectory(g_globalContext[0], fileName.p));
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
            igInsightCore_AddInfo(self->_insight, o);
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


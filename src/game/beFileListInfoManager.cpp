#include "dw4/reflected.h"
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

extern "C" void Gap__Bec__beFileListInfoManager__vfunc_24(void);
extern "C" int Gap__Bec__beFileListInfoManager__vfunc_20(void);
extern "C" void * igInsightCore_FindManager(...);
extern "C" void List_InsertWords(void *, int, int, void *);
extern "C" int StringPool_Allocate(int);
extern "C" int List_Reserve(void *, int, int);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, int);
extern "C" int DAT_0050e558[4];
struct S;
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vY(); };
struct S { int pad[2]; void *o; };
extern "C" int FUN_0037f1b0(S *arg0, int arg1);
extern "C" void igInsightCore_AddToScheduler(int, beFileListInfoManager *);
extern "C" void igInsightCore_RemoveFromScheduler(int, beFileListInfoManager *);
extern "C" void Gap__Bec__beFileListInfoManager__vfunc_21(beFileListInfoManager *self, int unusedArg);
extern "C" void Gap__Bec__beFileListInfoManager__vfunc_22(beFileListInfoManager *self, int unusedArg);
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0);
extern "C" int g_beFileListInfoManager_metaObject[4];
extern "C" void beFont_AddFontImages(void *, igObject *);
extern "C" void ObjectList_AppendRetained(igObjectList *, igObject *);
extern "C" int g_igNamedObjectInfo_metaObject[4];
extern "C" int g_beFont_metaObject[4];
extern "C" int g_beFileListInfo_metaObject[4];
class MetaVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int getMeta(); };
extern "C" int Gap__Bec__beFileListInfoManager__vfunc_25(beFileListInfoManager *self, igObject *info);
extern "C" int g_stringPool[4];
extern "C" int igObject_Destroy(igObject *);
extern "C" void Gap__Bec__beFileListInfoManager__vfunc_26(beFileListInfoManager *arg0);
extern "C" int igInsightCore_AddInfo(int, igObject *);
extern "C" int FUN_003817d0(beFileListInfoManager *arg0);
extern "C" int igObject_IsKindOf(igObject *object, int meta);
extern "C" int igResource_IsDirectoryLoaded(int resource, igDirectory *directory);
extern "C" void igResource_UnloadDirectory(int resource, int name);
extern "C" igObject *igResource_LoadDirectory(int resource, int *name);
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(int key);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_globalContext[4];
extern "C" int g_igSceneInfo_metaObject[4];
extern "C" int g_beLuaInfo_metaObject[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" char emptyString[];
extern "C" char DAT_0050e6c8[];
extern "C" int beFileListInfoManager_LoadNextFile(beFileListInfoManager *self, igStringRefList *fileNames);

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

int FUN_0037f1b0(S *arg0, int arg1) {
    if (((VA *)arg0->o)->vX(arg1, (int)&DAT_0050e558[0]) != 0) {
        ((VB *)arg0->o)->vY();
        return 1;
    }
    return 0;
}

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__beFileListInfoManager__vfunc_21(beFileListInfoManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__beFileListInfoManager__vfunc_22(beFileListInfoManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0) {
    arg0->_system = ((int)igInsightCore_FindManager(arg0->_insight, g_beSystem_metaObject[0]));
    arg0->_messenger = ((int)igInsightCore_FindManager(arg0->_insight, g_beMessenger_metaObject[0]));
    arg0->_sceneInfoManager = ((int)igInsightCore_FindManager(arg0->_insight, g_igViewerSceneInfoManager_metaObject[0]));
}

void Gap__Bec__beFileListInfoManager__vfunc_24(void)
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

int Gap__Bec__beFileListInfoManager__vfunc_25(beFileListInfoManager *self, igObject *info) {
    if (g_beFileListInfo_metaObject[0] == ((MetaVt *)info)->getMeta()) {
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
    if (g_igNamedObjectInfo_metaObject[0] == ((MetaVt *)info)->getMeta()) {
        void *found = igInsightCore_FindManager(self->_insight, g_beFont_metaObject[0]);
        if (found == 0) return 0;
        beFont_AddFontImages(found, info);
        return 1;
    }
    return 0;
}

void Gap__Bec__beFileListInfoManager__vfunc_26(beFileListInfoManager *arg0) {
    igStringRefList *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    CLEAR(igInfoList, arg0->_infoList)
    CLEAR(igDirectoryList, arg0->_dirList)
    s5 = (igStringRefList *)arg0->_fnames;
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
    CLEAR(igInfoList, arg0->_importantInfoList)
    CLEAR(igInfoList, arg0->_readInfoList)
    {
        igInfoList *l2 = (igInfoList *)arg0->_infoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igDirectoryList *l2 = (igDirectoryList *)arg0->_dirList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)arg0->_importantInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)arg0->_readInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    arg0->_loaded = 0;
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
    MetaVt *info;
    int meta;
    int *rootName;
    igDirectoryList *dirs;
    int fileCount = fileNames->_count;
    if (self->_loaded >= fileCount) return 1;
    dirs = (igDirectoryList *)self->_dirList;
    if (dirs->_count != 0) {
        dir = ((igDirectory **)dirs->_data)[0];
        if (igResource_IsDirectoryLoaded(g_globalContext[0], dir) != 0) {
            if (DAT_0050e6c8 == 0) {
                rootName = 0;
            } else {
                if (g_stringPool[0] == 0) {
                    int pool = StringPool_Allocate(0x10);
                    if (pool != 0) { pool = StringPool_Construct(pool); }
                    g_stringPool[0] = pool;
                }
                rootName = (int *)StringPool_Intern(g_stringPool[0], (int)DAT_0050e6c8);
            }
            StringRef rootAttr;
            rootAttr.p = rootName;
            infos = (igInfoList *)dir->_infoList;
            i = 0;
            if (i < infos->_count) {
                offset = 0;
                do {
                    meta = g_beLuaInfo_metaObject[0];
                    info = *(MetaVt **)(infos->_data + offset);
                    if (meta == info->getMeta()) {
                        igInsightCore_AddInfo(self->_insight, (igObject *)info);
                    } else {
                        meta = g_igSceneInfo_metaObject[0];
                        if (meta == info->getMeta()) {
                            igSceneInfo *scene;
                            if (info != 0 && igObject_IsKindOf((igObject *)info, g_igSceneInfo_metaObject[0]) != 0) {
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
                                    int sceneMeta = g_igSceneInfo_metaObject[0];
                                    if (sceneMeta == info->getMeta()) {
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
                SET_POOL(_objectMemoryPool, g_ndmwAllocatorSelector[0])
                SET_POOL(_dataMemoryPool, g_ndmwAllocatorSelector[0])
            } else if (remaining == 0) {
                SET_POOL(_objectMemoryPool, g_defaultAllocatorSelector[0])
                SET_POOL(_dataMemoryPool, g_defaultAllocatorSelector[0])
            }
            self->_onetimeCount = self->_onetimeCount - 1;
        }
        StringRef fileName(StringList_CopyRetained(fileNames, self->_loaded));
        ObjectList_AppendRetained((igObjectList *)self->_dirList, igResource_LoadDirectory(g_globalContext[0], fileName.p));
    }
    return 0;
}

int FUN_003817d0(beFileListInfoManager *arg0) {
    int i;
    igObjectList *l;
    int n;
    int k;
    int j;
    igObject *o;
    l = (igObjectList *)arg0->_readInfoList;
    for (i = 0; i < l->_count; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            igInsightCore_AddInfo(arg0->_insight, o);
        }
        l = (igObjectList *)arg0->_readInfoList;
    }
    n = ((igObjectList *)arg0->_readInfoList)->_count;
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

int Gap__Bec__beFileListInfoManager__vfunc_20(void)
{
    return g_beFileListInfoManager_metaObject[0];
}


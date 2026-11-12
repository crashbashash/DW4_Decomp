#ifndef DW4_LUA_LIBRARY_H
#define DW4_LUA_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

/* The library front: the registration latch. */
extern "C" unsigned char g_LuaLibrary_registered;
extern "C" void LuaLibrary_MarkRegistered(void);

extern "C" void igObject_InitHeader(void *object);
extern "C" void igObject_Destroy(void *object);
extern "C" void StringChunk_ReleaseHeader(void *owner, void *header);
extern "C" void igMetaObject_RunStaticInit(void *(*registerClass)(void));
extern "C" void *igMetaObject_RegisterClass(...);
extern "C" int igMetaObject_Create(int allocator);
extern "C" int igMetaObject_GetFieldCount(igMetaObject *meta);
extern "C" void igMetaObject_CreateFields(igMetaObject *meta, void *constructors, int count);
extern "C" void *igMetaObject_GetFieldAt(igMetaObject *meta, int index);
extern "C" void igMetaObject_NameFields(igMetaObject *meta, void *names, void *descriptors, void *offsets, int first);
extern "C" int Memory_GetAllocatorBySelector(int key);

/* The object system's byte offset of the vtable word inside an object. */
struct ObjectSystem { char pad[916]; int vtableOffset; };
extern "C" ObjectSystem *g_objectSystem[4];
extern "C" int g_metadataAllocatorKey[4];

extern "C" void *igObject_Register(void);
extern "C" void *igObject_GetMetaObject_ParentAccessor(void);
extern "C" void *igNamedObject_Register(void);
extern "C" void *igNamedObject_GetPublishedMetaObject(void);
extern "C" int FUN_002c04a0(void);

extern "C" int g_igNamedObject_vtable[4];

extern "C" igMetaObject *g_igLuaState_metaObject[4];
extern "C" const char igLuaState_className[];
extern "C" char g_igLuaState_callbackList[];
extern "C" int g_igLuaState_vtable[4];
extern "C" int g_igLuaState_fieldConstructors[2];
extern "C" int g_igLuaState_fieldNames[2];
extern "C" int g_igLuaState_fieldDescriptors[2];
extern "C" int g_igLuaState_fieldOffsets[2];
extern "C" igMetaObject *igLuaState_GetMetaObject(void);
extern "C" int igLuaState_GetVTable(void);
extern "C" void igLuaState_EnsureRegistered(void);
extern "C" void *igLuaState_Register(void);
extern "C" void thunk_igLuaState_GetMetaObject(void);
extern "C" void igLuaState_InitFields(void);

extern "C" igMetaObject *g_igLuaGlue_metaObject[4];
extern "C" const char igLuaGlue_className[];
extern "C" int g_igLuaGlue_vtable[4];
extern "C" igMetaObject *igLuaGlue_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igLuaGlue_GetMetaObject(void);
extern "C" int igLuaGlue_GetVTable(void);
extern "C" void igLuaGlue_EnsureRegistered(void);
extern "C" void *igLuaGlue_Register(void);
extern "C" void thunk_igLuaGlue_GetMetaObject(void);
extern "C" void LuaGlue_Initialize(void);
extern "C" void LuaGlue_Shutdown(void);
extern "C" igMetaObject *Gap__Lua__igLuaGlue__vfunc_22(void);
extern "C" void Gap__Lua__igLuaGlue__vfunc_09(void);
extern "C" void Gap__Lua__igLuaGlue__vfunc_10(void);

static inline bool isRegistered(igMetaObject *meta)
{
    return (meta->_validity & 4) != 0;
}

/* A reference-counted string: the text follows its chunk owner and its count. */
static inline void releaseString(char *text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int count = header[1] - 1;
        header[1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((void *)header[0], header);
        }
    }
}

/* `<Class>_GetVTable` runs a class's inline constructor and destructor on a stack instance and
 * reads the vtable word in between; igObject_InitHeader is igObject's constructor. */
struct ObjectImage {
    int *vtable;
    unsigned int _refCount;
};

/* igLuaState: igNamedObject's _name, then its own two fields. */
struct LuaStateImage : ObjectImage {
    char *_name;
    int _luaState;
    igObject *_memPool;
};

/* Thread-local values: one entry per (thread, slot), hashed by the two words xored. */
struct ThreadLocalEntry {
    unsigned int key;           /* thread ^ slot */
    ThreadLocalEntry *next;     /* bucket chain */
    ThreadLocalEntry *prev;
    int slot;
    void *value;
    void *thread;
};

extern "C" unsigned int g_threadLocalBucketShift;
extern "C" unsigned int g_threadLocalBucketCount;
extern "C" unsigned int g_threadLocalCount;
extern "C" ThreadLocalEntry **g_threadLocalBuckets;
extern "C" int g_threadLocalTableBusy;

extern "C" void ThreadLocalTable_Insert(ThreadLocalEntry *entry);
extern "C" void ThreadLocalTable_Link(ThreadLocalEntry *entry, ThreadLocalEntry **buckets,
                                      unsigned int bucketCount, unsigned int shift);
extern "C" void ThreadLocalTable_Resize(void);
extern "C" void ThreadLocalTable_Remove(ThreadLocalEntry *entry);

extern "C" void *Memory_AllocateDefaultBuffer(unsigned int size);
extern "C" void Memory_FreeBufferAliasA(void *buffer);
extern "C" void *memset(void *buffer, int value, unsigned int size);

/* The game reads script files through Alchemy's igFile instead of stdio. */
class igFileView : public igVirtualObject {
public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22();
    virtual int open(const char *name, const char *mode);      /* slot 23 */
    virtual int close();                                       /* slot 24 */
    virtual int read(void *buffer, int size, int count);       /* slot 25 */
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual int seek(int offset, int origin);                  /* slot 36 */
    virtual int size();                                        /* slot 37 */
};
extern "C" igFileView *FUN_002c4ca0(int pool);

struct lua_State;
enum { LUA_ERRFILE = 2, LUA_ERRMEM = 4 };
enum { SEEK_SET = 0, SEEK_END = 2 };
int lua_dobuffer(lua_State *L, const char *buffer, unsigned int size, const char *name);
void *luaM_realloc(lua_State *L, void *block, unsigned int size);
int lua_dofile(lua_State *L, const char *filename);

#endif

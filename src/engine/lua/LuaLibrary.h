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
struct lua_State;
struct LuaStateImage : ObjectImage {
    char *_name;
    lua_State *_luaState;
    igObject *_memPool;
};

/* Thread-local values: one entry per (thread, slot), hashed by the two words xored. An entry
 * leaves the table when it is destroyed. */
struct ThreadLocalEntry;
extern "C" void ThreadLocalTable_Insert(ThreadLocalEntry *entry);
extern "C" void ThreadLocalTable_Link(ThreadLocalEntry *entry, ThreadLocalEntry **buckets,
                                      unsigned int bucketCount, unsigned int shift);
extern "C" void ThreadLocalTable_Resize(void);
extern "C" void ThreadLocalTable_Remove(ThreadLocalEntry *entry);

struct ThreadLocalLink {
    unsigned int key;           /* thread ^ slot */
    ThreadLocalEntry *next;     /* bucket chain */
    ThreadLocalEntry *prev;

    ~ThreadLocalLink() {
        ThreadLocalTable_Remove((ThreadLocalEntry *)this);
    }
};

struct ThreadLocalEntry : ThreadLocalLink {
    int slot;
    void *value;
    void *thread;

    ThreadLocalEntry(void *thread, int slot, void *value);
    ~ThreadLocalEntry();
};

extern "C" unsigned int g_threadLocalBucketShift;
extern "C" unsigned int g_threadLocalBucketCount;
extern "C" unsigned int g_threadLocalCount;
extern "C" ThreadLocalEntry **g_threadLocalBuckets;
extern "C" int g_threadLocalTableBusy;

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

/* Stock Lua 4.0.1's API (lua.h, lualib.h), compiled as C++ like the rest of Lua. */
class igMemoryPoolView;
typedef int (*lua_CFunction)(lua_State *L);
enum { LUA_TUSERDATA, LUA_TNIL, LUA_TNUMBER, LUA_TSTRING, LUA_TTABLE, LUA_TFUNCTION };
enum { LUA_ERRRUN = 1, LUA_ERRFILE, LUA_ERRSYNTAX, LUA_ERRMEM, LUA_ERRERR };
enum { SEEK_SET = 0, SEEK_END = 2 };
lua_State *lua_open(int stacksize, igMemoryPoolView *pool);
void lua_close(lua_State *L);
int lua_gettop(lua_State *L);
void lua_settop(lua_State *L, int index);
void lua_pushvalue(lua_State *L, int index);
void lua_remove(lua_State *L, int index);
void lua_insert(lua_State *L, int index);
int lua_type(lua_State *L, int index);
int lua_tag(lua_State *L, int index);
double lua_tonumber(lua_State *L, int index);
const char *lua_tostring(lua_State *L, int index);
lua_CFunction lua_tocfunction(lua_State *L, int index);
void *lua_touserdata(lua_State *L, int index);
void lua_pushnil(lua_State *L);
void lua_pushnumber(lua_State *L, double n);
void lua_pushstring(lua_State *L, const char *s);
void lua_pushcclosure(lua_State *L, lua_CFunction fn, int n);
void lua_pushusertag(lua_State *L, void *u, int tag);
void lua_gettable(lua_State *L, int index);
void lua_rawget(lua_State *L, int index);
void lua_rawgeti(lua_State *L, int index, int n);
void lua_getglobals(lua_State *L);
int lua_getref(lua_State *L, int ref);
void lua_newtable(lua_State *L);
void lua_settable(lua_State *L, int index);
void lua_rawset(lua_State *L, int index);
void lua_rawseti(lua_State *L, int index, int n);
void lua_settagmethod(lua_State *L, int tag, const char *event);
int lua_ref(lua_State *L, int lock);
int lua_dofile(lua_State *L, const char *filename);
int lua_dostring(lua_State *L, const char *str);
int lua_dobuffer(lua_State *L, const char *buffer, unsigned int size, const char *name);
int lua_newtag(lua_State *L);
void lua_settag(lua_State *L, int tag);
int lua_next(lua_State *L, int index);
int lua_getn(lua_State *L, int index);
void lua_baselibopen(lua_State *L);
void lua_strlibopen(lua_State *L);
void lua_mathlibopen(lua_State *L);
void *luaM_realloc(lua_State *L, void *block, unsigned int size);

/* The C runtime and the Alchemy services the binding uses. */
#include "src/third_party/libc/stdarg.h"
extern "C" unsigned int strlen(const char *s);
extern "C" int strcmp(const char *a, const char *b);
extern "C" char *strstr(const char *haystack, const char *needle);
extern "C" int sprintf(char *buffer, const char *format, ...);
extern "C" int vsprintf(char *buffer, const char *format, va_list args);
extern "C" void *Memory_AllocateBufferDirect(unsigned int size, igObject *pool);
extern "C" void Memory_FreeBufferWithAllocator(void *buffer, igObject *pool);
extern "C" igObject *igMetaObject_CreateInstanceDefault(igMetaObject *meta);
extern "C" igMetaField *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name);
extern "C" igMetaObject *igObjectSystem_FindMetaByNameDefault(const char *name);
extern "C" igMetaObject *g_igCharMetaField_metaObject;
extern "C" igMetaObject *g_igUnsignedCharMetaField_metaObject;
extern "C" igMetaObject *g_igIntMetaField_metaObject;
extern "C" igMetaObject *g_igUnsignedIntMetaField_metaObject;
extern "C" igMetaObject *g_igShortMetaField_metaObject;
extern "C" igMetaObject *g_igUnsignedShortMetaField_metaObject;
extern "C" igMetaObject *g_igLongMetaField_metaObject;
extern "C" igMetaObject *g_igUnsignedLongMetaField_metaObject;
extern "C" igMetaObject *g_igEnumMetaField_metaObject;
extern "C" igMetaObject *g_igFloatMetaField_metaObject;
extern "C" igMetaObject *g_igDoubleMetaField_metaObject;
extern "C" igMetaObject *g_igStringMetaField_metaObject;
extern "C" igMetaObject *g_igBoolMetaField_metaObject;
extern "C" igMetaObject *g_igMemoryRefMetaField_metaObject;
extern "C" igMetaObject *g_igObjectRefMetaField_metaObject;

/* An Alchemy object as the binding sees it: slot 20 of every igObject returns its meta-object.
 * Bit 23 of the reference count marks an object a script holds a reference to. */
class LuaBoundObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual igMetaObject *getMeta();                            /* slot 20 */
    union {
        unsigned int _refCount;
        struct {
            unsigned int count : 23;
            unsigned int scriptHeld : 1;
            unsigned int flags : 8;
        } refBits;
    };
};

/* A field's meta-object descriptor: slot 20 returns the igMetaField subclass it is. */
class LuaMetaFieldView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual igMetaObject *getMeta();                            /* slot 20 */
};

/* The binding's own hash tables chain their entries through this header: the key, then the
 * bucket chain's next and previous entries. */
struct LuaHashLink {
    unsigned int key;
    LuaHashLink *next;
    LuaHashLink *prev;
};

/* What a bound value is in C++, `LuaType::kind`. */
enum LuaKind {
    LUA_KIND_NONE,
    LUA_KIND_CHAR,
    LUA_KIND_UCHAR,
    LUA_KIND_SHORT,
    LUA_KIND_USHORT,
    LUA_KIND_INT,
    LUA_KIND_UINT,
    LUA_KIND_LONG,
    LUA_KIND_ULONG,
    LUA_KIND_BOOL,
    LUA_KIND_ENUM,
    LUA_KIND_FLOAT,
    LUA_KIND_DOUBLE,
    LUA_KIND_STRING,
    LUA_KIND_OBJECT,
    LUA_KIND_VOID,
    LUA_KIND_STATIC,
    LUA_KIND_CHARS
};

struct LuaClass;

/* A bound value's type: the C++ kind, how many pointers lead to it, and the Lua types a script
 * may pass for it (`1 << LUA_T*`). An object names its meta-object and its Lua class; an enum
 * keeps its name in the meta-object word. */
struct LuaType {
    int kind : 8;
    int indirection : 2;
    unsigned int byValue : 1;
    unsigned int flag3 : 1;
    unsigned int flag4 : 1;
    unsigned int acceptsTable : 1;
    unsigned int isObjectPointer : 1;
    unsigned int writeBack : 1;
    int acceptedTypes : 16;
    igMetaObject *metaObject;
    LuaClass *luaClass;

    LuaType() {}
    LuaType(int kind, int indirection, int flags, const char *className);
    LuaType(const char **names, unsigned int code);
};

/* One argument or result while a bound function runs. */
struct LuaValue {
    LuaType type;
    union {
        signed char c;
        unsigned char uc;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long long ll;
        unsigned long long ull;
        bool b;
        float f;
        double d;
        char *string;
        void *object;
    } data;

    LuaValue() {}
    LuaValue(LuaType *type, lua_State *L, int index);
};

/* A bound C++ function or method, followed by its argument types. Functions of one name and
 * owner chain as overloads. */
struct LuaFunction {
    LuaHashLink link;               /* key: the owner xored with the name's hash */
    const char *name;
    LuaType result;
    LuaClass *owner;
    lua_CFunction function;
    LuaFunction *nextOverload;
    short id;
    unsigned short argCount : 12;
    unsigned short hasSelf : 1;
    unsigned short isUnique : 1;
    unsigned short hasOutArgs : 1;
    unsigned short isMethod : 1;

    LuaFunction(lua_CFunction function, int id, const char *name, const LuaType &result, LuaClass *owner,
                int isMethod, int argCount);
};

/* A class exposed to Lua: its tags, its class table and the handlers of its tag methods.
 * Instances a script creates carry `instanceTag`, objects it is handed `referenceTag`. */
struct LuaClassData {
    LuaHashLink link;               /* key: the name's hash */
    const char *name;
    igMetaObject *metaObject;
    LuaClass *base;
    LuaClass *firstDerived;
    LuaClass *prevSibling;
    LuaClass *nextSibling;
    const char *metaName;
    int instanceTag;
    int referenceTag;
    int classTag;
    int classTableRef;
    LuaFunction *indexGetter;
    LuaFunction *indexSetter;
    lua_CFunction gcHandler;
    lua_CFunction setHandler;
    lua_CFunction getHandler;
    lua_CFunction constructor;
    lua_CFunction peerConstructor;
    LuaClass *alternate;
};

/* The class is polymorphic: its vtable pointer follows the data. The vtables are retail data, as
 * this build's profile would give a compiled one a type-info pointer, so a class's vtable is
 * stored by hand and its virtual functions are called through LuaBoundClass. */
struct LuaClass : LuaClassData {
    const void *vtable;

    LuaClass(const char *name, const char *metaName, lua_CFunction gc, lua_CFunction peerConstructor,
             lua_CFunction get, lua_CFunction set, lua_CFunction construct);
};

/* The two virtual functions, which a derived class overrides to bind its functions and constants;
 * LuaClass_RegisterFunctions and LuaClass_RegisterConstants are LuaClass's own. */
class LuaBoundClass : public LuaClassData {
public:
    virtual void registerFunctions();
    virtual void registerConstants();
};

extern "C" const int g_LuaClass_vtable[4];
extern "C" const int g_LuaCharArrayClass_vtable[4];
extern "C" const int g_LuaUnsignedCharArrayClass_vtable[4];
extern "C" const int g_LuaShortArrayClass_vtable[4];
extern "C" const int g_LuaUnsignedShortArrayClass_vtable[4];
extern "C" const int g_LuaIntArrayClass_vtable[4];
extern "C" const int g_LuaUnsignedIntArrayClass_vtable[4];
extern "C" const int g_LuaLongArrayClass_vtable[4];
extern "C" const int g_LuaUnsignedLongArrayClass_vtable[4];
extern "C" const int g_LuaBoolArrayClass_vtable[4];
extern "C" const int g_LuaFloatArrayClass_vtable[4];
extern "C" const int g_LuaDoubleArrayClass_vtable[4];
extern "C" void LuaClass_RegisterConstants(LuaClass *luaClass);
extern "C" void LuaClass_RegisterFunctions(LuaClass *luaClass);

/* The binding's hash tables, one per kind of entry: bucket count 1 << shift, entry count,
 * buckets, and a busy count that defers resizing while a walk is under way. */
struct LuaProperty;
extern "C" unsigned int g_luaFieldBucketShift;
extern "C" unsigned int g_luaFieldBucketCount;
extern "C" unsigned int g_luaFieldCount;
extern "C" LuaHashLink **g_luaFieldBuckets;
extern "C" int g_luaFieldTableBusy;
extern "C" unsigned int g_luaFunctionBucketShift;
extern "C" unsigned int g_luaFunctionBucketCount;
extern "C" unsigned int g_luaFunctionCount;
extern "C" LuaHashLink **g_luaFunctionBuckets;
extern "C" int g_luaFunctionTableBusy;
extern "C" unsigned int g_luaClassBucketShift;
extern "C" unsigned int g_luaClassBucketCount;
extern "C" unsigned int g_luaClassCount;
extern "C" LuaHashLink **g_luaClassBuckets;
extern "C" int g_luaClassTableBusy;
extern "C" unsigned int g_luaPropertyBucketShift;
extern "C" unsigned int g_luaPropertyBucketCount;
extern "C" unsigned int g_luaPropertyCount;
extern "C" LuaProperty **g_luaPropertyBuckets;
extern "C" int g_luaPropertyTableBusy;
extern "C" unsigned int g_luaConstantBucketShift;
extern "C" unsigned int g_luaConstantBucketCount;
extern "C" unsigned int g_luaConstantCount;
extern "C" LuaHashLink **g_luaConstantBuckets;
extern "C" int g_luaConstantTableBusy;
extern "C" unsigned int g_luaEnumBucketShift;
extern "C" unsigned int g_luaEnumBucketCount;
extern "C" unsigned int g_luaEnumCount;
extern "C" LuaHashLink **g_luaEnumBuckets;
extern "C" int g_luaEnumTableBusy;

/* A property (a bound variable) of a class; its owner's handlers read and write it. Its second
 * base is its link in the property table. */
struct LuaPropertyLink {
    unsigned int key;               /* the owner xored with the name's hash */
    LuaProperty *next;
    LuaProperty *prev;
};
struct LuaProperty : LuaHashLink, LuaPropertyLink {
    const char *name;
    LuaClass *owner;
};

/* An enum constant of a class. */
struct LuaConstant {
    LuaHashLink link;
    const char *name;
    LuaClass *owner;
    int value;
};

extern "C" igObject *g_luaGluePool;

/* A reflected field the binding exposes by name: the entry leaves the table when destroyed, and
 * its memory comes from the glue's pool. */
extern "C" void LuaFieldTable_Remove(LuaHashLink *link);
struct LuaFieldLink : LuaHashLink {
    ~LuaFieldLink() {
        LuaFieldTable_Remove(this);
    }
};
struct LuaFieldEntry {
    LuaFieldLink link;              /* key: the meta-object xored with the name's hash */
    igMetaObject *meta;
    igMetaField *field;

    ~LuaFieldEntry();
    void operator delete(void *memory) {
        Memory_FreeBufferWithAllocator(memory, g_luaGluePool);
    }
};

extern "C" void LuaFieldTable_Resize(void);

/* Holds the field table still while it lives: no resize until it ends, and a resize then if
 * entries came or went meanwhile. */
struct LuaFieldTableLock {
    unsigned int count;

    LuaFieldTableLock() {
        count = g_luaFieldCount;
        g_luaFieldTableBusy += 1;
    }
    ~LuaFieldTableLock() {
        g_luaFieldTableBusy--;
        if (count != g_luaFieldCount) {
            LuaFieldTable_Resize();
        }
    }
};

/* Walks the field-table bucket of one key. */
struct LuaFieldIterator {
    LuaFieldTableLock lock;
    LuaFieldEntry *node;

    LuaFieldIterator(unsigned int key);
    ~LuaFieldIterator();
    int isValid();
    LuaFieldIterator &operator++(int);
    LuaFieldEntry *get();
};

/* A class a start-up hook creates when the glue starts: static instances link themselves in. */
struct LuaStartupHook {
    int phase;
    LuaBoundClass *(*create)(void);
    LuaBoundClass *luaClass;
    LuaStartupHook *next;
    LuaStartupHook *prev;

    LuaStartupHook(LuaBoundClass *(*create)(void), int phase);
};

/* The sorted tags of userdata that are Alchemy objects (an igIntList). */
struct LuaTagList {
    int *vtable;
    unsigned int _refCount;
    int count;
    int capacity;
    int *data;

    int indexOf(const int &tag) const {
        int lo = 0;
        int hi = count - 1;
        int mid;
        int entry;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            entry = data[mid];
            if (entry < tag) {
                lo = mid + 1;
            } else if (tag < entry) {
                hi = mid - 1;
            } else {
                return mid;
            }
        }
        if (count == 0) {
            return -1;
        }
        entry = data[lo];
        if (tag < entry || entry < tag) {
            return -1;
        }
        return lo;
    }
    void insertSorted(int *tag);
};
extern "C" int FUN_001e3ab0(LuaTagList *list, int *value);
extern "C" void List_InsertWords(LuaTagList *list, int index, int count, int *values);
inline void LuaTagList::insertSorted(int *tag) {
    List_InsertWords(this, FUN_001e3ab0(this, tag), 1, tag);
}
extern "C" LuaTagList *FUN_002caa70(igObject *pool);

/* The current memory context; slot 21 hands out a pool. */
class LuaMemoryContext {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual igObject *getPool(int size);                        /* slot 21 */
};
extern "C" LuaMemoryContext *Memory_GetCurrentContextAlias(void);

inline void *operator new(unsigned int, void *memory) {
    return memory;
}

inline void *operator new(unsigned int size, igObject *pool) {
    return Memory_AllocateBufferDirect(size, pool);
}

/* The hash of a name in the binding's tables. */
static inline unsigned int LuaBinding_HashName(const char *name) {
    unsigned int hash = 0;
    int length = strlen(name);
    const char *c = name;
    while (length-- != 0) {
        hash += (hash << 5) + (hash << 2) + *c;
        c++;
    }
    return hash;
}

enum { LUA_ANYTAG = -1 };
enum { LUA_PUSH_INSTANCE, LUA_PUSH_REFERENCE, LUA_PUSH_KEEP_TAG };

/* Receives each message LuaError formats, with the data registered alongside. */
typedef void (*LuaErrorHandler)(const char *message, void *data);

extern "C" LuaTagList *g_luaObjectTags;
extern "C" LuaClass *g_luaArrayClasses[13];
extern "C" LuaClass *g_luaGlobalClass;
extern "C" LuaStartupHook *g_luaStartupHooks;
extern "C" int g_luaObjectTag;
extern "C" int g_luaMetaObjectTag;
extern "C" const char *g_luaOperatorEvents[];

/* LuaBinding.cpp */
extern "C" {
void LuaBinding_SetGlobalUserdata(lua_State *L, const char *name, void *object, int tag);
void LuaType_UpdateAccepted(LuaType *type);
int LuaType_IsNumber(LuaType *type);
int LuaType_MatchesUserdata(LuaType *type, int tag, LuaBoundObject *object, int *distance);
void LuaType_PushObject(LuaType *type, lua_State *L, LuaBoundObject *object, int mode);
void LuaType_PushString(LuaType *type, lua_State *L, const char *string);
void LuaType_PushPointer(LuaType *type, lua_State *L, int mode, LuaBoundObject *object);
int LuaType_Accepts(LuaType *type, lua_State *L, int index, int *distance);
void LuaValue_StoreInTable(LuaValue *value, lua_State *L, int table);
bool LuaObject_PushField(lua_State *L, igMetaField *field, LuaBoundObject *object);
int LuaObject_StoreField(lua_State *L, igMetaField *field, LuaBoundObject *object, int index);
LuaFunction *LuaFunctionTable_Find(LuaClass *owner, const char *name);
LuaFunction *LuaFunction_Resolve(LuaFunction *function, lua_State *L, int first, int upvalue);
void LuaFunctionTable_LinkOverloads(void);
int LuaFunction_Call(LuaFunction *function, lua_State *L);
void LuaClass_SetOperator(lua_State *L, LuaClass *luaClass, LuaFunction *function, int event);
void LuaFunction_SetField(lua_State *L, LuaFunction *function);
void LuaClass_BindClass(lua_State *L, LuaClass *luaClass);
void LuaClass_BindFunctions(LuaClass *owner, lua_CFunction method, lua_CFunction function,
                            const char **names, int count, const unsigned int *codes, LuaFunction **byId);
void LuaFunctionTable_Clear(void);
LuaProperty *LuaPropertyTable_Find(LuaClass *owner, const char *name);
void LuaPropertyTable_Clear(void);
LuaConstant *LuaConstantTable_Find(const char *name, LuaClass *owner);
void LuaClassTable_Clear(void);
void LuaConstantTable_Clear(void);
void LuaEnumTable_Clear(void);
int LuaBinding_GetGlobal(lua_State *L);
int LuaBinding_SetGlobal(lua_State *L);
int LuaObject_New(lua_State *L);
const char *LuaMetaField_GetName(igMetaField *field);
unsigned int LuaFieldTable_Key(igMetaObject *meta, const char *name);
int LuaObject_Collect(lua_State *L);
int LuaFunction_CallMember(lua_State *L);
int LuaFunction_CallUpvalue(lua_State *L);
int LuaFunction_CallOverload(lua_State *L);
int LuaClass_GetMember(lua_State *L, LuaClass *luaClass, const char *name);
int LuaClass_GetIndexed(lua_State *L, LuaClass *luaClass);
int LuaClass_GetTable(lua_State *L);
int LuaClass_SetTable(lua_State *L);
int LuaObject_GetTable(lua_State *L);
int LuaObject_SetTable(lua_State *L);
int LuaPeer_GetTable(lua_State *L);
void LuaPeer_NoteSetError(const char *message, void *data);
int LuaPeer_SetTable(lua_State *L);
void LuaObject_SetField(lua_State *L, igMetaField *field, LuaBoundObject *object, const char *key, int index);
int LuaFunction_CallOperator(lua_State *L);
int LuaFunction_CallUnaryOperator(lua_State *L);
LuaClass *LuaClass_FindByName(const char *name);
LuaClass *LuaClass_FindByTag(int tag);
LuaClass *LuaClass_FindForMeta(igMetaObject *meta);
int LuaClass_DistanceToBase(LuaClass *base, LuaClass *luaClass);
void LuaClassTable_ReleaseAll(void);
void LuaClass_SetTagMethod(lua_State *L, LuaClass *luaClass, int tag, lua_CFunction handler, const char *event);
void LuaClass_SetTableHandlers(lua_State *L, LuaClass *luaClass, int tag, lua_CFunction set, lua_CFunction get);
void LuaClass_Register(LuaClass *luaClass, lua_State *L);
void LuaClass_SetBase(LuaClass *luaClass, LuaClass *base);
int LuaClass_HasTag(LuaClass *luaClass, int tag, int *distance);
int LuaBinding_GetClassTags(lua_State *L);
int LuaCharArray_Delete(lua_State *L);
int LuaCharArray_Get(lua_State *L);
int LuaCharArray_Set(lua_State *L);
int LuaCharArray_New(lua_State *L);
int LuaUnsignedCharArray_Delete(lua_State *L);
int LuaUnsignedCharArray_Get(lua_State *L);
int LuaUnsignedCharArray_Set(lua_State *L);
int LuaUnsignedCharArray_New(lua_State *L);
int LuaShortArray_Delete(lua_State *L);
int LuaShortArray_Get(lua_State *L);
int LuaShortArray_Set(lua_State *L);
int LuaShortArray_New(lua_State *L);
int LuaUnsignedShortArray_Delete(lua_State *L);
int LuaUnsignedShortArray_Get(lua_State *L);
int LuaUnsignedShortArray_Set(lua_State *L);
int LuaUnsignedShortArray_New(lua_State *L);
int LuaIntArray_Delete(lua_State *L);
int LuaIntArray_Get(lua_State *L);
int LuaIntArray_Set(lua_State *L);
int LuaIntArray_New(lua_State *L);
int LuaUnsignedIntArray_Delete(lua_State *L);
int LuaUnsignedIntArray_Get(lua_State *L);
int LuaUnsignedIntArray_Set(lua_State *L);
int LuaUnsignedIntArray_New(lua_State *L);
int LuaLongArray_Delete(lua_State *L);
int LuaLongArray_Get(lua_State *L);
int LuaLongArray_Set(lua_State *L);
int LuaLongArray_New(lua_State *L);
int LuaUnsignedLongArray_Delete(lua_State *L);
int LuaUnsignedLongArray_Get(lua_State *L);
int LuaUnsignedLongArray_Set(lua_State *L);
int LuaUnsignedLongArray_New(lua_State *L);
int LuaBoolArray_Delete(lua_State *L);
int LuaBoolArray_Get(lua_State *L);
int LuaBoolArray_New(lua_State *L);
int LuaFloatArray_Delete(lua_State *L);
int LuaFloatArray_Get(lua_State *L);
int LuaFloatArray_Set(lua_State *L);
int LuaFloatArray_New(lua_State *L);
int LuaDoubleArray_Delete(lua_State *L);
int LuaDoubleArray_Get(lua_State *L);
int LuaDoubleArray_Set(lua_State *L);
int LuaDoubleArray_New(lua_State *L);
}

/* Walks every entry of the field table. */
struct LuaFieldWalker {
    LuaFieldTableLock lock;
    LuaFieldEntry *node;
    unsigned int bucket;

    LuaFieldWalker();
    ~LuaFieldWalker();
    int isValid();
    LuaFieldWalker &operator++(int);
    LuaFieldEntry *get();
};

/* An Alchemy result code, returned by value. */
struct igResult {
    int code;
};

/* The semaphore that guards the thread-local slots. */
class LuaSemaphoreView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual igResult initialize();                              /* slot 21 */
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual igResult release();                                 /* slot 29 */
    virtual void s30();
    virtual igResult wait(int block);                           /* slot 31 */
    unsigned int _refCount;
};
extern "C" LuaSemaphoreView *FUN_002ba650(igObject *pool);

/* Holds the semaphore for its lifetime. */
struct LuaSemaphoreLock {
    LuaSemaphoreView *semaphore;

    LuaSemaphoreLock(LuaSemaphoreView *held) {
        semaphore = held;
        semaphore->wait(1);
    }
    ~LuaSemaphoreLock() {
        semaphore->release();
    }
};

/* The thread manager; slot 21 is the calling thread. */
class LuaThreadManagerView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void *getCurrentThread();                           /* slot 21 */
};
extern "C" LuaThreadManagerView *g_threadManager;

extern "C" LuaErrorHandler g_luaErrorHandler;
extern "C" void *g_luaErrorHandlerData;
extern "C" LuaStateImage *g_currentLuaState;
extern "C" unsigned char g_luaStatePerThread;
extern "C" int g_luaStateSlot;
extern "C" int g_threadLocalNextSlot;
extern "C" LuaSemaphoreView *g_threadLocalSemaphore;
extern "C" const char *g_luaErrorNames[];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_defaultAllocatorKey;
extern "C" igObject *igObject_GetAllocator(void *object);

/* LuaState.cpp */
extern "C" {
int LuaBoolArray_Set(lua_State *L);
void LuaGlue_Shutdown(void);
void LuaGlue_OpenLibrary(lua_State *L);
void *LuaBinding_GetPeer(lua_State *L, int index);
int LuaBinding_New(lua_State *L);
int LuaBinding_Cast(lua_State *L);
void LuaFieldTable_Insert(LuaHashLink *link);
void LuaFieldTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaFieldTable_Resize(void);
void LuaFieldTable_Remove(LuaHashLink *link);
void LuaFunctionTable_Insert(LuaHashLink *link);
void LuaFunctionTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaFunctionTable_Resize(void);
void LuaFunctionTable_Remove(LuaHashLink *link);
void LuaClassTable_Insert(LuaHashLink *link);
void LuaClassTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaClassTable_Resize(void);
void LuaClassTable_Remove(LuaHashLink *link);
void LuaPropertyTable_Link(LuaPropertyLink *link, LuaProperty **buckets, unsigned int bucketCount, unsigned int shift);
void LuaPropertyTable_Resize(void);
void LuaPropertyTable_Remove(LuaPropertyLink *link);
void LuaConstantTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaConstantTable_Resize(void);
void LuaConstantTable_Remove(LuaHashLink *link);
void LuaEnumTable_Link(LuaHashLink *link, LuaHashLink **buckets, unsigned int bucketCount, unsigned int shift);
void LuaEnumTable_Resize(void);
void LuaEnumTable_Remove(LuaHashLink *link);
void ThreadLocal_Set(int slot, void *value);
void ThreadLocal_SetForThread(void *thread, int slot, void *value);
int ThreadLocal_NewSlot(void *value);
void ThreadLocal_FreeSlot(int slot);
void igLuaState_MakeCurrent(LuaStateImage *state);
void igLuaState_Open(LuaStateImage *state);
void igLuaState_Close(LuaStateImage *state);
int igLuaState_RunString(LuaStateImage *state, const char *source);
int igLuaState_RunFile(LuaStateImage *state, const char *path);
int igLuaState_RunBuffer(LuaStateImage *state, const char *buffer, unsigned int size, const char *name);
void LuaBinding_SetErrorHandler(LuaErrorHandler handler, void *data);
LuaErrorHandler LuaBinding_GetErrorHandler(void **data);
void LuaError(const char *format, ...);
igMetaObject *Gap__Lua__igLuaState__vfunc_22(void);
}

#endif

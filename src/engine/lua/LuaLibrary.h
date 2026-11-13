#ifndef DW4_LUA_LIBRARY_H
#define DW4_LUA_LIBRARY_H

#include "dw4/lua.h"
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
extern "C" int igMemoryPool_GetOrCreateMetaObject(void);

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
extern "C" igMetaObject *igLuaGlue_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igLuaGlue_GetMetaObject(void);
extern "C" int igLuaGlue_GetVTable(void);
extern "C" void igLuaGlue_EnsureRegistered(void);
extern "C" void *igLuaGlue_Register(void);
extern "C" void thunk_igLuaGlue_GetMetaObject(void);
extern "C" void LuaGlue_Initialize(void);
extern "C" void LuaGlue_Shutdown(void);

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

/* The shared pool of reference-counted strings, created on first use. */
struct StringPool;
extern "C" StringPool *g_stringPool;
extern "C" void *StringPool_Allocate(unsigned int size);
extern "C" StringPool *StringPool_Construct(void *memory);
extern "C" char *StringPool_Intern(StringPool *pool, const char *text);
static inline StringPool *stringPool() {
    if (g_stringPool == 0) {
        void *memory = StringPool_Allocate(16);
        if (memory != 0) {
            memory = StringPool_Construct(memory);
        }
        g_stringPool = (StringPool *)memory;
    }
    return g_stringPool;
}

/* A pooled copy of `text`, holding a reference; none for none. */
static inline char *internString(const char *text) {
    if (text == 0) {
        return 0;
    }
    return StringPool_Intern(stringPool(), text);
}

/* A reflected field's setters: a string field takes a reference to a pooled string, an object
 * reference field a reference to the object. */
extern "C" void igStringMetaField_AssignRetainedToken(igMetaField *field, void *object, char **text);
extern "C" void igObjectRefMetaField_Assign(igMetaField *field, void *object, void *value);

/* `<Class>_GetVTable` runs a class's inline constructor and destructor on a stack instance and
 * reads the vtable word in between; igObject_InitHeader is igObject's constructor. igLuaState's
 * is written out by hand on this image of the object, its destructors included. */
struct ObjectImage {
    int *vtable;
    unsigned int _refCount;
};

/* igLuaState: igNamedObject's _name, then its own two fields. */
struct LuaStateImage : ObjectImage {
    char *_name;
    lua_State *_luaState;
    igObject *_memPool;
};

namespace Gap {
namespace Core {
/* igNamedObject's virtual functions: an igObject with a name. */
class igNamedObject : public igObject {
public:
    char *_name;

    igMetaObject *getMeta();
};
}
namespace Lua {
/* A Lua state as an Alchemy object. Built, it opens the state in its memory pool with the standard
 * libraries and the glue's; going, it closes it. Its own virtual functions run a chunk from a
 * string, a file or a buffer. */
class igLuaState : public Core::igNamedObject {
public:
    lua_State *_luaState;
    ::igObject *_memPool;

    void userConstruct();
    void userDestruct();
    igMetaObject *getMeta();
    virtual int runString(const char *source);
    virtual int runFile(const char *path);
    virtual int runBuffer(const char *buffer, unsigned int size, const char *name);
};
}
}

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

/* Holds the thread-local table still while it lives, as LuaFieldTableLock does the field table. */
struct ThreadLocalTableLock {
    unsigned int count;

    ThreadLocalTableLock() {
        count = g_threadLocalCount;
        g_threadLocalTableBusy += 1;
    }
    ~ThreadLocalTableLock() {
        g_threadLocalTableBusy--;
        if (count != g_threadLocalCount) {
            ThreadLocalTable_Resize();
        }
    }
};

/* A thread's key for a slot. */
inline unsigned int ThreadLocalTable_Key(void *thread, int slot) {
    return (unsigned int)thread ^ slot;
}

/* Walks the thread-local bucket of one key. */
struct ThreadLocalIterator {
    ThreadLocalTableLock lock;
    ThreadLocalEntry *node;

    ThreadLocalIterator(unsigned int key)
        : node(g_threadLocalBuckets != 0
                   ? g_threadLocalBuckets[(g_threadLocalBucketCount - 1) & (key ^ (key >> g_threadLocalBucketShift))]
                   : 0) {
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = node->next;
    }
    ThreadLocalEntry *get() {
        return node;
    }
};

/* Walks every entry of the thread-local table. */
struct ThreadLocalWalker {
    ThreadLocalTableLock lock;
    ThreadLocalEntry *node;
    unsigned int bucket;

    ThreadLocalWalker() {
        node = 0;
        bucket = 0;
        while (node == 0 && bucket < g_threadLocalBucketCount && g_threadLocalBuckets != 0) {
            node = g_threadLocalBuckets[bucket++];
        }
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = node->next;
        if (node != 0) {
            return;
        }
        while (node == 0 && bucket < g_threadLocalBucketCount) {
            node = g_threadLocalBuckets[bucket++];
        }
    }
    ThreadLocalEntry *get() {
        return node;
    }
};

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
extern "C" igFileView *igFile_Create(int pool);

/* Stock Lua's internals and the C runtime's seek origins, which only the library uses. */
enum { SEEK_SET = 0, SEEK_END = 2 };
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

/* The binding's hash tables, one per kind of entry: bucket count 1 << shift, entry count,
 * buckets, and a busy count that defers resizing while a walk is under way. */
struct LuaProperty;
struct LuaPropertyLink;
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
 * base is its link in the property table, which it leaves when destroyed. */
extern "C" void LuaPropertyTable_Remove(LuaPropertyLink *link);
struct LuaPropertyLink {
    unsigned int key;               /* the owner xored with the name's hash */
    LuaProperty *next;
    LuaProperty *prev;

    ~LuaPropertyLink() {
        LuaPropertyTable_Remove(this);
    }
};
struct LuaProperty : LuaHashLink, LuaPropertyLink {
    const char *name;
    igLuaGlue::Class *owner;
};

/* An enum of a class. Its link's key and the two words after it are not established. */
struct LuaEnum : Hashed<LuaEnum, 4> {
    int unknown[2];
    igLuaGlue::Class *owner;

    void operator delete(void *memory) {
        Memory_FreeBufferWithAllocator(memory, g_luaGluePool);
    }
};

/* A constant of an enum, keyed by its name's hash. */
struct LuaConstant : Hashed<LuaConstant, 8> {
    LuaEnum *enumeration;
    const char *name;
    int value;
};

extern "C" void LuaConstantTable_Remove(LuaHashLink *link);
extern "C" void LuaEnumTable_Remove(LuaHashLink *link);

template <>
inline Hashed<LuaConstant, 8>::~Hashed() {
    LuaConstantTable_Remove(&link);
}

template <>
inline Hashed<LuaEnum, 4>::~Hashed() {
    LuaEnumTable_Remove(&link);
}

/* A reflected field the binding exposes by name: the entry joins the table when built and leaves
 * it when destroyed, and its memory comes from the glue's pool. */
extern "C" void LuaFieldTable_Insert(LuaHashLink *link);
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

    LuaFieldEntry(igMetaObject *meta, igMetaField *field);
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

extern "C" void LuaClassTable_Insert(LuaHashLink *link);
extern "C" void LuaClassTable_Resize(void);
extern "C" void LuaFunctionTable_Insert(LuaHashLink *link);
extern "C" void LuaFunctionTable_Remove(LuaHashLink *link);

/* A class enters the class table as it is built, keyed by its name's hash. */
template <>
inline Hashed<igLuaGlue::Class, 7>::Hashed(unsigned int key) {
    link.key = key;
    link.next = 0;
    link.prev = 0;
    LuaClassTable_Insert(&link);
}

/* A function enters the function table as it is built, keyed by its owner and name, and leaves
 * it when destroyed; it comes from the glue's pool. */
template <>
inline Hashed<LuaFunction, 8>::Hashed(unsigned int key) {
    link.key = key;
    link.next = 0;
    link.prev = 0;
    LuaFunctionTable_Insert(&link);
}

template <>
inline Hashed<LuaFunction, 8>::~Hashed() {
    LuaFunctionTable_Remove(&link);
}

inline void LuaFunction::operator delete(void *memory) {
    Memory_FreeBufferWithAllocator(memory, g_luaGluePool);
}

/* Holds the class table still while it lives, as LuaFieldTableLock does the field table. */
struct LuaClassTableLock {
    unsigned int count;

    LuaClassTableLock() {
        count = g_luaClassCount;
        g_luaClassTableBusy += 1;
    }
    ~LuaClassTableLock() {
        g_luaClassTableBusy--;
        if (count != g_luaClassCount) {
            LuaClassTable_Resize();
        }
    }
};

/* Walks the class-table bucket of one key. */
struct LuaClassIterator {
    LuaClassTableLock lock;
    igLuaGlue::Class *node;

    LuaClassIterator(unsigned int key)
        : node(g_luaClassBuckets != 0
                   ? (igLuaGlue::Class *)g_luaClassBuckets[(g_luaClassBucketCount - 1) & (key ^ (key >> g_luaClassBucketShift))]
                   : 0) {
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = (igLuaGlue::Class *)node->link.next;
    }
    igLuaGlue::Class *get() {
        return node;
    }
};

/* Walks every class in the class table. */
struct LuaClassWalker {
    LuaClassTableLock lock;
    igLuaGlue::Class *node;
    unsigned int bucket;

    LuaClassWalker() {
        node = 0;
        bucket = 0;
        while (node == 0 && bucket < g_luaClassBucketCount && g_luaClassBuckets != 0) {
            node = (igLuaGlue::Class *)g_luaClassBuckets[bucket++];
        }
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = (igLuaGlue::Class *)node->link.next;
        if (node != 0) {
            return;
        }
        while (node == 0 && bucket < g_luaClassBucketCount) {
            node = (igLuaGlue::Class *)g_luaClassBuckets[bucket++];
        }
    }
    igLuaGlue::Class *get() {
        return node;
    }
};

/* The globals of the table whose entries are T, as the walks below read them. */
template <class T>
struct LuaTable;

extern "C" void LuaFunctionTable_Resize(void);
extern "C" void LuaPropertyTable_Resize(void);
extern "C" void LuaConstantTable_Resize(void);
extern "C" void LuaEnumTable_Resize(void);

template <>
struct LuaTable<LuaFunction> {
    static unsigned int &count() { return g_luaFunctionCount; }
    static int &busy() { return g_luaFunctionTableBusy; }
    static unsigned int bucketCount() { return g_luaFunctionBucketCount; }
    static unsigned int bucketShift() { return g_luaFunctionBucketShift; }
    static LuaHashLink **buckets() { return g_luaFunctionBuckets; }
    static LuaFunction *next(LuaFunction *entry) { return (LuaFunction *)entry->link.next; }
    static void resize() { LuaFunctionTable_Resize(); }
};

template <>
struct LuaTable<LuaProperty> {
    static unsigned int &count() { return g_luaPropertyCount; }
    static int &busy() { return g_luaPropertyTableBusy; }
    static unsigned int bucketCount() { return g_luaPropertyBucketCount; }
    static unsigned int bucketShift() { return g_luaPropertyBucketShift; }
    static LuaProperty **buckets() { return g_luaPropertyBuckets; }
    static LuaProperty *next(LuaProperty *entry) { return entry->LuaPropertyLink::next; }
    static void resize() { LuaPropertyTable_Resize(); }
};

template <>
struct LuaTable<LuaConstant> {
    static unsigned int &count() { return g_luaConstantCount; }
    static int &busy() { return g_luaConstantTableBusy; }
    static unsigned int bucketCount() { return g_luaConstantBucketCount; }
    static unsigned int bucketShift() { return g_luaConstantBucketShift; }
    static LuaHashLink **buckets() { return g_luaConstantBuckets; }
    static LuaConstant *next(LuaConstant *entry) { return (LuaConstant *)entry->link.next; }
    static void resize() { LuaConstantTable_Resize(); }
};

template <>
struct LuaTable<LuaEnum> {
    static unsigned int &count() { return g_luaEnumCount; }
    static int &busy() { return g_luaEnumTableBusy; }
    static unsigned int bucketCount() { return g_luaEnumBucketCount; }
    static unsigned int bucketShift() { return g_luaEnumBucketShift; }
    static LuaHashLink **buckets() { return g_luaEnumBuckets; }
    static LuaEnum *next(LuaEnum *entry) { return (LuaEnum *)entry->link.next; }
    static void resize() { LuaEnumTable_Resize(); }
};

/* Holds the table of T still while it lives, as LuaClassTableLock does the class table. */
template <class T>
struct LuaTableLock {
    unsigned int count;

    LuaTableLock() {
        count = LuaTable<T>::count();
        LuaTable<T>::busy() += 1;
    }
    ~LuaTableLock() {
        LuaTable<T>::busy()--;
        if (count != LuaTable<T>::count()) {
            LuaTable<T>::resize();
        }
    }
};

/* Walks the bucket of one key in the table of T. */
template <class T>
struct LuaTableIterator {
    LuaTableLock<T> lock;
    T *node;

    LuaTableIterator(unsigned int key)
        : node(LuaTable<T>::buckets() != 0
                   ? (T *)LuaTable<T>::buckets()[(LuaTable<T>::bucketCount() - 1) & (key ^ (key >> LuaTable<T>::bucketShift()))]
                   : 0) {
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = LuaTable<T>::next(node);
    }
    T *get() {
        return node;
    }
};

/* Walks every entry of the table of T. */
template <class T>
struct LuaTableWalker {
    LuaTableLock<T> lock;
    T *node;
    unsigned int bucket;

    LuaTableWalker() {
        node = 0;
        bucket = 0;
        while (node == 0 && bucket < LuaTable<T>::bucketCount() && LuaTable<T>::buckets() != 0) {
            node = (T *)LuaTable<T>::buckets()[bucket++];
        }
    }
    bool isValid() {
        return node != 0;
    }
    void operator++(int) {
        node = LuaTable<T>::next(node);
        if (node != 0) {
            return;
        }
        while (node == 0 && bucket < LuaTable<T>::bucketCount()) {
            node = (T *)LuaTable<T>::buckets()[bucket++];
        }
    }
    T *get() {
        return node;
    }
};

/* A class a start-up hook creates when the glue starts: static instances link themselves in. */
struct LuaStartupHook {
    int phase;
    igLuaGlue::Class *(*create)(void);
    igLuaGlue::Class *luaClass;
    LuaStartupHook *next;
    LuaStartupHook *prev;

    LuaStartupHook(igLuaGlue::Class *(*create)(void), int phase);
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
extern "C" LuaTagList *igIntList_Create(igObject *pool);

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

inline LuaFieldEntry::LuaFieldEntry(igMetaObject *meta, igMetaField *field) {
    link.key = (unsigned int)meta ^ LuaBinding_HashName((const char *)field->_fieldName);
    link.next = 0;
    link.prev = 0;
    LuaFieldTable_Insert(&link);
    this->meta = meta;
    this->field = field;
}

enum { LUA_ANYTAG = -1 };
/* The binding's tags until the first state opens the library and makes them. */
enum { LUA_UNMADETAG = -9999 };
enum { LUA_PUSH_INSTANCE, LUA_PUSH_REFERENCE, LUA_PUSH_KEEP_TAG };

/* Receives each message LuaError formats, with the data registered alongside. */
typedef void (*LuaErrorHandler)(const char *message, void *data);

extern "C" LuaTagList *g_luaObjectTags;
extern "C" igLuaGlue::Class *g_luaArrayClasses[13];
extern "C" igLuaGlue::Class *g_luaGlobalClass;
extern "C" LuaStartupHook *g_luaStartupHooks;
/* The empty name of the class that holds the global functions. */
extern "C" const char emptyString_3[];
/* How many classes wait for a base class of the name they gave to be built. */
extern "C" int g_luaClassesAwaitingBase;
extern "C" int g_luaObjectTag;
extern "C" int g_luaMetaObjectTag;
/* Made with the other two; nothing reads it. */
extern "C" int g_luaReservedTag;
void lua_setglobal(lua_State *L, const char *name);
extern "C" const char *g_luaOperatorEvents[];

/* LuaBinding.cpp */
extern "C" {
void LuaBinding_SetGlobalUserdata(lua_State *L, const char *name, void *object, int tag);
void LuaType_UpdateAccepted(LuaType *type);
int LuaType_IsNumber(LuaType *type);
int LuaType_MatchesUserdata(LuaType *type, int tag, LuaBoundObject *object, int *distance);
void LuaType_PushObject(LuaType *type, lua_State *L, LuaBoundObject *object, int mode);
void LuaType_PushPointer(LuaType *type, lua_State *L, int mode, LuaBoundObject *object);
int LuaType_Accepts(LuaType *type, lua_State *L, int index, int *distance);
void LuaValue_StoreInTable(LuaValue *value, lua_State *L, int table);
bool LuaObject_PushField(lua_State *L, igMetaField *field, LuaBoundObject *object);
int LuaObject_StoreField(lua_State *L, igMetaField *field, LuaBoundObject *object, int index);
LuaFunction *LuaFunctionTable_Find(igLuaGlue::Class *owner, const char *name, bool callback);
void LuaFunctionTable_BindAll(lua_State *L);
LuaFunction *LuaFunction_Resolve(LuaFunction *function, lua_State *L, int first, int last);
void LuaFunctionTable_LinkOverloads(void);
int LuaFunction_Call(LuaFunction *function, lua_State *L);
void LuaClass_SetOperator(lua_State *L, igLuaGlue::Class *luaClass, LuaFunction *function, int event);
void LuaFunction_SetField(lua_State *L, LuaFunction *function);
void LuaClass_BindClass(lua_State *L, igLuaGlue::Class *luaClass);
void LuaFunctionTable_Clear(void);
LuaProperty *LuaPropertyTable_Find(igLuaGlue::Class *owner, const char *name);
void LuaPropertyTable_Clear(void);
LuaConstant *LuaConstantTable_Find(const char *name, igLuaGlue::Class *owner);
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
int LuaClass_GetMember(lua_State *L, igLuaGlue::Class *luaClass, const char *name);
int LuaClass_GetIndexed(lua_State *L, igLuaGlue::Class *luaClass);
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
igLuaGlue::Class *LuaClass_FindByName(const char *name);
igLuaGlue::Class *LuaClass_FindByTag(int tag);
igLuaGlue::Class *LuaClass_FindForMeta(igMetaObject *meta);
int LuaClass_DistanceToBase(igLuaGlue::Class *base, igLuaGlue::Class *luaClass);
void LuaClassTable_ReleaseAll(void);
void LuaClass_SetTagMethod(lua_State *L, igLuaGlue::Class *luaClass, int tag, lua_CFunction handler, const char *event);
void LuaClass_SetTableHandlers(lua_State *L, igLuaGlue::Class *luaClass, int tag, lua_CFunction set, lua_CFunction get);
void LuaClass_Register(igLuaGlue::Class *luaClass, lua_State *L);
void LuaClass_SetBase(igLuaGlue::Class *luaClass, igLuaGlue::Class *base);
int LuaClass_HasTag(igLuaGlue::Class *luaClass, int tag, int *distance);
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
    void advance();
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
    virtual igResult destroy();                                 /* slot 22 */
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
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

/* Drops one reference to the semaphore, destroying it with the last. */
static inline void LuaSemaphore_ReleaseReference(LuaSemaphoreView *semaphore) {
    semaphore->_refCount = semaphore->_refCount - 1;
    if ((semaphore->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(semaphore);
    }
}

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
extern "C" Gap::Lua::igLuaState *g_currentLuaState;
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
void igLuaState_MakeCurrent(Gap::Lua::igLuaState *state);
void LuaBinding_SetErrorHandler(LuaErrorHandler handler, void *data);
LuaErrorHandler LuaBinding_GetErrorHandler(void **data);
}

#endif

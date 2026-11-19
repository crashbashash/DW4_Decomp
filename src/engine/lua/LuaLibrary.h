#ifndef DW4_LUA_LIBRARY_H
#define DW4_LUA_LIBRARY_H

#include "dw4/lua/lua.h"
#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/lua/igLuaGlue.h"
#include "dw4/lua/igLuaState.h"
#include "dw4/lua/LuaArray.h"
#include "dw4/lua/LuaBinding.h"
#include "dw4/lua/LuaClass.h"
#include "dw4/lua/LuaFunction.h"
#include "dw4/lua/LuaGlue.h"
#include "dw4/lua/LuaHashTables.h"
#include "dw4/lua/LuaObject.h"
#include "dw4/lua/LuaType.h"
#include "dw4/core/ThreadLocalTable.h"
#include "dw4/core/igNamedObject.h"

/* The library front: the registration latch. */
extern "C" void LuaLibrary_MarkRegistered(void);

/* A class's registration: a field factory builds each reflected field, a callback list runs when the
 * class registers. */
typedef igMetaField *(*FieldFactory)(struct igMemoryPoolView *pool);
typedef void (*igMetaObjectCallback)(void);
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igFile.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/support/list-services.h"
#include "dw4/core/igMemoryPool.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igSemaphore.h"
#include "dw4/core/igThread.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/StringPool.h"


extern "C" int g_igLuaState_vtable[4];


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
            StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
        }
    }
}

/* The shared pool of reference-counted strings, created on first use. */
static inline StringPool *stringPool() {
    if (g_stringPool == 0) {
        void *memory = StringPool_Allocate(16);
        if (memory != 0) {
            memory = StringPool_Construct((StringPool *)memory);
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

    igMetaObject *getMeta() const;
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

    void userConstruct(int flag);
    void userDestruct();
    igMetaObject *getMeta() const;
    virtual int runString(const char *source);
    virtual int runFile(const char *path);
    virtual int runBuffer(const char *buffer, unsigned int size, const char *name);
};
}
}

/* Thread-local values: one entry per (thread, slot), hashed by the two words xored. An entry
 * leaves the table when it is destroyed. */
struct ThreadLocalEntry;

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

/* A property (a bound variable) of a class; its owner's handlers read and write it. Its second
 * base is its link in the property table, which it leaves when destroyed. */
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
        Memory_FreeBufferWithAllocator(memory, (igMemoryPoolView *)g_luaGluePool);
    }
};

/* A constant of an enum, keyed by its name's hash. */
struct LuaConstant : Hashed<LuaConstant, 8> {
    LuaEnum *enumeration;
    const char *name;
    int value;
};


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
        Memory_FreeBufferWithAllocator(memory, (igMemoryPoolView *)g_luaGluePool);
    }
};


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
    Memory_FreeBufferWithAllocator(memory, (igMemoryPoolView *)g_luaGluePool);
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
extern "C" int FUN_001e3ab0(igIntList *list, int *value);
/* LuaTagList is this library's view of the igIntList, so both list services take it converted. */
inline void LuaTagList::insertSorted(int *tag) {
    List_InsertWords((igDataList *)this, FUN_001e3ab0((igIntList *)this, tag), 1, tag);
}

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

inline void *operator new(unsigned int, void *memory) {
    return memory;
}

inline void *operator new(unsigned int size, igObject *pool) {
    return Memory_AllocateBufferDirect(size, (igMemoryPoolView *)pool);
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


/* How many classes wait for a base class of the name they gave to be built. */
/* Made with the other two; nothing reads it. */
void lua_setglobal(lua_State *L, const char *name);

/* LuaBinding.cpp */
extern "C" {
void LuaClassTable_ReleaseAll(void);
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
        igObject_Destroy((igObject *)semaphore);
    }
}

#endif

#include "dw4/reflected.h"

class igResult {
public:
    int v;
    igResult() {}
    igResult(int x) : v(x) {}
    igResult(const igResult &o) : v(o.v) {}
    igResult &operator=(const igResult &o) { v = o.v; return *this; }
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const;
};
extern igResult g_statusSucceeded;
extern igResult g_allocatorFailureStatus;
inline bool igResult::isFailed(int &f) const { f = g_allocatorFailureStatus.v; return *this == g_allocatorFailureStatus; }

struct PoolDescRecord { int vt; int rc; char *name; char q12[8]; char *alias; char *s24; int a28; int a32; int a36; char *s40; char *s44; char *s48; char *s52; char *s56; char *s60; char *s64; char *s68; char *s72; char *s76; int a80; };
struct PoolDescSlot { int pool; char name[128]; PoolDescRecord *record; char q136[8]; };
struct ContextStackEntry;

extern "C" {
void *memset(void *, int, unsigned int);
void igObject_Destroy(void *);
int strcmp(...);
char *strncpy(...);
char *strstr(...);
int sprintf(...);
void igNamedObject_SetName(...);
int igObject_GetAllocator(...);
void *FUN_002c01f0(int);
void *FUN_002bfed0(int);
void FUN_002f8a80(...);
void FUN_002f8b20(...);
void *StringPool_Allocate(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, void *);
igMemoryPool *Memory_GetAllocatorBySelector(int);
void FUN_003065f0(...);
void FUN_00306e50(...);
void *FUN_002c5780(...);
int FUN_002dcc40(...);
int FUN_00304430(...);
int FUN_00304680(...);
int FUN_002dcc60(...);
int FUN_002dcd70(...);
igResult FUN_002f86e0(void *);
ContextStackEntry *FUN_002f8760(void);
void igMemoryPoolContextInfo_DeleteAllocation(void *);
extern void *DAT_00587000[4];
extern char DAT_004f7910[];
extern char *g_memoryContextNames[46];
extern unsigned char *g_objectSystem[4];
extern void *DAT_00586fd0;
extern void *g_stringPool;
extern void *DAT_00587218[4];
extern char DAT_004fa530[];
extern char DAT_004fa550[];
}

extern "C" int igObject_InitHeader(...);
struct Ref { int pad0; int f4; };
struct BF { unsigned lo : 23; unsigned hi : 9; };
/* dispatch-only view of the object: 43 vtable slots then the init slot (no fields) */
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void vX(); };
/* Refcount field as a 23+9 bit-field (read-modify-write with a 64-bit constant) and a 43-slot
 * virtual call. */
/* matching construct: the word at +16 is stored/loaded as a reference pointer (the reflected _resolveState is a 1-byte bool there; code wins); the vtable is the reflected int _vtable, called through slot 45 */
extern "C" igMemoryPoolContextInfo *igMemoryPoolContextInfo_Construct(igMemoryPoolContextInfo *arg0);


struct ContextRecord {
    void *allocator;       /* retained by the slot setter */
    char name[128];        /* 127 characters copied in plus an explicit terminator */
    void *descriptor;
    unsigned storageFlags, flags;
};
/* Dispatch-only view of the context's virtual table: the dummies pad the table so that
 * InitializeRecordNames lands on vtable offset 180 and Clear on offset 212 (the other slots are
 * never called here). */
class ContextVirtuals {
public:
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42();
    virtual void InitializeRecordNames();  /* vtable offset 180 */
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50();
    virtual void Clear(int index);         /* vtable offset 212: release the allocator of one record */
};
struct ContextView : igObject {
    int usedRecords;       /* +8: highest populated slot + 1 (30 right after construction) */
    unsigned flags;        /* +12 */
    igObject *parent;      /* +16 */
    ContextRecord records[46];
};
/* vtable of igMemoryPoolContextInfo (published by the constructor) */
extern "C" char g_igMemoryPoolContextInfo_vtable[];
/* IgMemoryPoolContextInfo: the destructor and the retained-allocator slot setter. A context holds
 * 46 records of 144 bytes starting at +0x14 (clearing them is the 6,624-byte memset in the
 * destructor). Each record is the allocator bound to that slot, a 128-byte inline name, a
 * descriptor and flag words. The object header is the igObject vtable word and reference word,
 * followed by a count at +8 (30 after construction, then the highest populated slot + 1), a flag
 * word at +12 and a parent object at +16 that the destructor releases with the igObject reference-
 * count idiom. The views below describe the observed 32-bit layout, not the original C++ spelling. */
/* Destructor: republish the vtable, clear the reference word and all records, rebuild the 46
 * record names, release the parent, and free the allocation when the low 16 bits of `deleteFlags`
 * are positive (deleting destructor). The parent word is left in place. */
extern "C" void *igMemoryPoolContextInfo_Destruct(ContextView *self, long long deleteFlags);


struct R { int a; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v92(int); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual R v208(int); };
struct E { int pad[5]; int key; int val[30]; };
struct Ctx : VC { };
extern int DAT_00587010[4];
extern "C" int FUN_002f2730(Ctx *arg0, int arg1);
int FUN_002f2730(Ctx *arg0, int arg1);


class ContextVirtuals2 {
public:
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20();
    virtual void *Lookup(int index);  /* returns the allocator bound to record `index` */
};
struct NamedRecord {
    void *allocator;
    char name[128];
    void *descriptor;
    unsigned storageFlags, flags;
};
struct ContextRecords {
    char header[20];
    NamedRecord records[46];
};
/* Lookup of a context record by name. A context holds 46 records of 144 bytes starting at +0x14,
 * each with a 128-byte inline name at +4. The view below describes the observed 32-bit layout, not
 * the original C++ spelling. */
/* Dispatch-only view: the dummies pad the vtable so that Lookup lands on slot 21 (vtable offset
 * 92). */
/* 0 when the strings are equal */
/* Finds the first of the 46 records whose name equals `name` and returns what its slot-21 lookup
 * yields; null or empty names, and unknown names, give null. */
extern "C" void *FUN_002f2830(ContextVirtuals2 *self, const char *name);


/* (vtable offset 100) Bind `value` to record `index` (0..45). Re-binding the same object is a no-
 * op; a different old binding is released through Clear first. The new object is retained, and a
 * non-null binding raises the used-record count. */
extern "C" void FUN_002f28d0(ContextView *self, int index, igObject *value);


extern "C" int FUN_002f2990(int arg0, int arg1);


class VC2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int *v108(int); };
struct Ctx2 { E e[46]; };
extern "C" int *FUN_002f29d0(Ctx2 *arg0, int arg1);
/* The global count test is written `1 < n`. */
int *FUN_002f29d0(Ctx2 *arg0, int arg1);


#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_RECORD_SIZE 0x90
#define CONTEXT_RECORDS_OFFSET 0x14
#define CONTEXT_RECORD_NAME_MAX 0x7F
/* Renames record `recordIndex` of the context: copies at most 127 characters into the record's
 * inline 128-byte name field, terminates it, and renames the record's bound named object (if any)
 * to match. Out-of-range indices are ignored. The context holds 46 records of 144 bytes starting
 * at +0x14, each with a 128-byte inline name at +4. */
extern "C" void FUN_002f2ab0(int self, int recordIndex, int name);


extern "C" int FUN_002f2b30(int arg0, char *arg1);


extern "C" int strncmp(...);
extern int DAT_004fa3b0[4];
extern int DAT_004fa3c8[4];
extern "C" int FUN_002f2bc0(int arg0, char *arg1);


extern "C" int FUN_002f2cd0(int arg0, int arg1);


struct R2 { int v; R2() {} R2(int x) { v = x; } };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
class Child { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual R2 vA(int, int); };
class Self { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual R2 vB(int, int); };
struct OB { int vt; int a4; int a8; int a12; RO *f16; };
extern "C" R2 FUN_002f2d20(OB *arg1, int arg2, int arg3);


class Child2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual R2 vA(int, int); };
extern "C" R2 FUN_002f2e30(OB *arg1, int arg2, int arg3);


struct igRefHead { int vt; int rc; };
class SlotReadTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual igResult readOne(int, igRefHead *);
};
extern "C" igResult FUN_002f2f40(SlotReadTable *self, int file);


extern "C" int FUN_002f8a50(int);
extern "C" void *FUN_002f8a60(int, int);
struct DirSlotObject { int vt; int rc; };
struct DirSourceRecord { char p0[20]; int id; };
class DirSlotTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slotFor(int); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual igResult fillSlot(int, DirSourceRecord *, int);
  char q4[12]; DirSlotObject *slots; };
extern "C" igResult FUN_002f3060(DirSlotTable *self, int file, int arg);


extern "C" int igObject_IsKindOf(void *, int);
/* Header stored in front of every interned string token. */
struct StringTokenHeader { int owner; int refCount; };
typedef void StringToken;
/* a token points at the interned text; its header precedes it */
/* The descriptor's attached object: only the four virtuals this function calls are named; the others
 * are placeholders that keep the vtable byte offsets (8 + 4 * slot) right. */
class SizedObject {
public:
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26();
    virtual unsigned int hasLimitOrSize();/* byte 116 */
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33();
    virtual long long limit();/* byte 144 */
    virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41();
    virtual unsigned int count();/* byte 176 */
    virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50();
    virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58();
    virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66();
    virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74();
    virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82();
    virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90();
    virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void p95(); virtual void p96(); virtual void p97();
    virtual unsigned long long total();/* byte 400 */
};
/* Pool descriptor defaults (entry +0x84): interned-string sources and integer limits. */
struct PoolDefaults {
    char pad0[0x18];
    const char *text0;       /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    const char *text1;       /* +0x28 */
    const char *text2;
    const char *text3;
    const char *text4;
    const char *text5;
    const char *text6;
    const char *text7;
    const char *text8;
    const char *text9;
    const char *text10;      /* +0x4c */
    int field50;             /* +0x50 */
};
struct PoolEntry {
    SizedObject *object;     /* +0x00 */
    char name[0x80];         /* +0x04 */
    PoolDefaults *defaults;  /* +0x84 */
    char pad88[8];
};
struct PoolTable {
    char pad0[0x14];
    PoolEntry entries[46];   /* +0x14, 0x90 bytes each */
};
/* The pool handle object being filled; string members hold interned tokens. */
struct PoolHandle {
    char pad0[0x14];
    StringToken *handleName; /* +0x14 */
    StringToken *token0;     /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    StringToken *token1;     /* +0x28 */
    StringToken *token2;
    StringToken *token3;
    StringToken *token4;
    StringToken *token5;
    StringToken *token6;
    StringToken *token7;
    StringToken *token8;
    StringToken *token9;
    StringToken *token10;    /* +0x4c */
    int field50;             /* +0x50 */
};
extern int g_igArenaMemoryPool_metaObject[4];
extern char DAT_004fa3e0[];
#define ASSIGN_TOKEN(field, source)                                           \
    text = (source);                                                          \
    if (g_stringPool == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        g_stringPool = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(g_stringPool, text);          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader(header->owner, header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token
#define ASSIGN_TOKEN_DIRECT(field, source)                                           \
    if (g_stringPool == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        g_stringPool = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(g_stringPool, (source));          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader(header->owner, header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token
/* Fills one memory-pool handle object from the pool descriptor table: looks up descriptor `index`
 * (0x90 bytes each, from +0x14 of the table) and, when the index is in 0..45, copies it into the
 * handle object: the descriptor name via igNamedObject_SetName, the integer size/limit fields
 * (+0x1c..+0x24, +0x50), and ten interned strings (+0x18, +0x28..+0x4c, each assigned through the
 * shared StringPool with the usual retain/release of the old token). The descriptor's attached
 * object (+0 of the entry) supplies +0x1c when it reports a size; the handle name (+0x14) is built
 * from the table name 'kIGMemoryPoolHandle%s'. The status written through `result` is g_statusSucceeded
 * on success and g_allocatorFailureStatus for an out-of-range index. */
extern "C" void FUN_002f31b0(int *result, PoolTable *table, int index, PoolHandle *handle);


extern char emptyString[];
extern int g_allocatorSelector[4];
struct PoolDescString { int chunk; int refs; };
static inline void *descPool() {
    if (g_stringPool == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0) { p = StringPool_Construct(p); }
        g_stringPool = p;
    }
    return g_stringPool;
}
static inline void setDescString(char **dst, char *src) {
    char *v = StringPool_Intern(descPool(), src);
    char *old = *dst;
    if (old != 0) {
        PoolDescString *h = (PoolDescString *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader(h->chunk, h); }
    }
    *dst = v;
}
extern "C" PoolDescRecord *FUN_002f8be0(int, char *);
extern "C" PoolDescRecord *FUN_002f8ca0(int, char *);
class PoolDescManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual igResult build(int, int); };
class PoolDescManager : public PoolDescManagerBase { public: char q4[4]; int nextSlot; char q12[4]; int table; };
static inline char *descName(PoolDescRecord *r) { char *n = r->name; if (n != 0) { return n; } return emptyString; }
extern "C" igResult FUN_002f3910(PoolDescManager *self, int index, PoolDescRecord *desc, int build);


extern "C" void FUN_002f4060(void *arg0, int arg1);


extern "C" void FUN_002f4070(void *arg0);
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
class DW4VC_152_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int); };
void FUN_002f4070(void *arg0);


class Obj2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual int v85(int); int f4; };
class Par { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v36(int); int f4; int f8; int f12; };
extern "C" void FUN_002f4110(Par *arg0);


struct Obj3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void FUN_002f41e0(char *arg0);
void FUN_002f41e0(char *arg0);


extern "C" void FUN_002f4250(void **arg0);
class DW4VC_180_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual int vX(); };
class DW4VC_196_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual int vX(); };
class DW4VC_212_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int vX(int); };
class DW4VC_220_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(); };
void FUN_002f4250(void **arg0);


extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" void FUN_002f42e0(void **arg0, int arg1);
void FUN_002f42e0(void **arg0, int arg1);


extern "C" int Gap__Core__igObject__vfunc_02(...);
extern "C" void FUN_002f4340(void **arg0);
void FUN_002f4340(void **arg0);


extern char *DAT_00586de8;
extern int igArenaMemoryPool_className[4];
extern int igMallocMemoryPool_className[4];
extern int DAT_00586fd8[4];
extern int DAT_00586fe0[4];
extern int DAT_00586fe8[4];
extern int DAT_00586ff0[4];
extern unsigned char g_useOwnerAllocator;
class PoolObjectBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90(); virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void prepare(); };
class PoolObject : public PoolObjectBase { public: int rc; };
struct PoolContext { char p0[48]; PoolObject *main; PoolObject *second; };
extern "C" void *FUN_002f0040(int, int, int);
extern "C" int Memory_GetDefaultAllocator();
extern "C" PoolObject *FUN_0031eb90(void *);
extern "C" PoolObject *FUN_003235c0(void *);
extern "C" void Memory_InitializeAllocatorRegistries(PoolObject *);
extern "C" void FUN_002f0370(PoolObject *);
struct PoolSlot { char p0[144]; };
struct PoolSlotTable { char p0[20]; PoolObject *first; };
static inline PoolObject *newLargePool() {
    void *p = FUN_002f0040(0xd0, 0, Memory_GetDefaultAllocator());
    if (p != 0) { p = FUN_0031eb90(p); }
    return (PoolObject *)p;
}
static inline PoolObject *newSmallPool() {
    void *p = FUN_002f0040(0xa0, 0, Memory_GetDefaultAllocator());
    if (p != 0) { p = FUN_003235c0(p); }
    return (PoolObject *)p;
}
#define NEW_LARGE_POOL(p) { p = newLargePool(); }
#define NEW_SMALL(p) { p = newSmallPool(); }
#define NEW_POOL(p) { if (DAT_00586de8 != 0) { if (strcmp(DAT_00586de8, igArenaMemoryPool_className) == 0) { NEW_LARGE_POOL(p) } else if (strcmp(DAT_00586de8, igMallocMemoryPool_className) == 0) { NEW_SMALL(p) } else { NEW_LARGE_POOL(p) } } else { NEW_LARGE_POOL(p) } }
extern "C" void FUN_002f43a0(PoolSlotTable *self);


extern "C" void FUN_002f48c0(void);


class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void v96(); };
extern "C" int FUN_002f0460(void *);
extern "C" int Memory_ShutdownAllocatorRegistries(void *);
extern "C" int thunk_free_2(void *);
extern int D_00587010[4];
extern "C" void FUN_002f48d0(char *arg0);
void FUN_002f48d0(char *arg0);


#define CONTEXT_NAME_LIMIT 0x7F      /* 127-char copy, then an explicit terminator */
/* One record: 4-byte first word, 128-byte inline name, 12 further bytes. */
typedef struct ContextRecord2 {
    int firstWord;
    char name[128];
    char rest[12];
} ContextRecord2;
/* The 46 records follow the 20-byte object header.  Retail steps one pointer
 * by whole records from the context base, so that pointer sits 20 bytes before
 * the record it works on; this view reproduces it (name is 24 bytes in). */
typedef struct ContextPrefixedRecord {
    char header[20];
    ContextRecord2 record;
} ContextPrefixedRecord;
/* IgMemoryPoolContextInfo slot 180: write the 46 original context names (Bootstrap, Default,
 * Current, NonTracked, ...) into the name field of each 144-byte context record. Each name is
 * copied with a 127-character limit and the 128th byte is cleared explicitly. Called by the
 * constructor and the destructor. strncpy is a strncpy-like bounded string copy (dest, source,
 * limit). */
extern "C" void igMemoryPoolContextInfo_InitializeRecordNames(igMemoryPoolContextInfo *self);


extern "C" int FUN_002cd990();
extern "C" int FUN_002cd9f0();
extern "C" int FUN_002cda50();
extern "C" void FUN_00307470(int, int, const char *, int, int *, int, int);
extern "C" void FUN_00307550(int, int, const char *, int, int *, int, int);
extern int DAT_004c2228[4];
extern int DAT_004c2368[4];
extern int DAT_004c2370[4];
extern int DAT_004fa400[4];
extern int DAT_004fa420[4];
extern int DAT_004fa440[4];
extern char DAT_004fa460[];
extern char DAT_004fa490[];
extern char DAT_004fa4c0[];
extern int DAT_004fa4f0[4];
extern int DAT_004fa510[4];
extern int DAT_005871f8[4];
extern unsigned char GPR_00554994;
class PoolConfigObject { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual int inUse(); virtual igResult lock(int); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); int rc; char q8[184]; int options; };
struct PoolConfigContext { char p0[48]; PoolConfigObject *main; PoolConfigObject *second; int config; char p60[28]; PoolConfigObject *a88; char p92[4]; PoolConfigObject *a96; };
class PoolConfigManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual PoolConfigObject *poolFor(int); virtual void p22(); virtual void setPool(int, PoolConfigObject *); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual igResult setDefault(int, int); virtual void p34(); virtual void p35(); virtual void setFlags(int); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual igResult readConfig(int, int); virtual void p47(); virtual igResult apply(); virtual igResult build(int, int); virtual void p50(); virtual void p51(); virtual void finish(); };
class PoolConfigManager : public PoolConfigManagerBase { public: char q4[8]; int flags; int defaultSize; PoolConfigObject *first; char q24[140]; PoolConfigObject *third; char q168[284]; PoolConfigObject *fallback; };
extern "C" PoolConfigObject *FUN_002cdab0(PoolConfigObject *);
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(PoolConfigObject *, int);
extern "C" void FUN_002f4a60(int *out, PoolConfigManager *self) {
    unsigned char useFlag;
    unsigned char lockFlag;
    unsigned char optFlag;
    int options;
    int optB;
    int optC;
    int mainSize;
    int nextSize;
    PoolConfigObject *mainPool;
    int i;
    int config;
    PoolConfigObject *o;
    int result;
    PoolConfigObject *second;
    int fail;
    config = ((PoolConfigContext *)g_objectSystem[0])->config;
    mainPool = ((PoolConfigContext *)g_objectSystem[0])->main;
    second = ((PoolConfigContext *)g_objectSystem[0])->second;
    options = DAT_004c2370[0];
    mainSize = 0;
    nextSize = 0;
    optB = DAT_004c2368[0];
    optC = DAT_005871f8[0];
    {
    int f = self->flags;
    result = g_statusSucceeded.v;
    lockFlag = GPR_00554994;
    useFlag = (f & 4) != 0;
    }
    FUN_003065f0(config, 2, DAT_004fa400, &mainSize, 0, 0);
    if (mainSize > 0) { mainPool->setName(mainSize); }
    FUN_00306e50(config, 2, DAT_004fa420, &lockFlag, lockFlag, 0);
    GPR_00554994 = lockFlag;
    FUN_00306e50(config, 2, DAT_004fa440, &useFlag, useFlag, 0);
    self->setFlags(useFlag != 0 ? self->flags | 4 : self->flags & ~4);
    FUN_00307550(config, 2, DAT_004fa460, FUN_002cd990(), &options, DAT_004c2370[0], 0);
    FUN_00307470(config, 2, DAT_004fa490, FUN_002cd9f0(), &optB, DAT_004c2368[0], 0);
    FUN_00307470(config, 2, DAT_004fa4c0, FUN_002cda50(), &optC, DAT_005871f8[0], 0);
    {
        int v = (options & 0x200) != 0;
        optFlag = v;
        FUN_00306e50(config, 2, DAT_004fa4f0, &optFlag, v, 0);
    }
    if (optFlag != 0) { options |= 0x200; }
    DAT_004c2370[0] = options;
    DAT_004c2368[0] = optB;
    DAT_005871f8[0] = optC;
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && igObject_IsKindOf(o, g_igArenaMemoryPool_metaObject[0]) != 0) {
            igArenaMemoryPool_SetPoolOptionFlags(o, (options & ~1) | (o->options & 1));
        }
    }
    FUN_003065f0(config, 2, DAT_004fa510, &nextSize, 0, 0);
    PoolConfigManager *top = (PoolConfigManager *)DAT_00586fd0;
    PoolConfigObject *fb = self->fallback;
    if (self == top && fb == mainPool) {
        PoolConfigObject *n = FUN_002cdab0(mainPool);
        if (nextSize > 0) { n->setName(nextSize); }
        n->finish();
        self->setPool(3, n);
        n->rc = n->rc - 1;
        if (((unsigned long long)((long long)(int)n->rc << 0x29) >> 0x29) == 0) igObject_Destroy(n);
    }
    if (self->readConfig(config, DAT_004c2228[0]).isFailed(fail)) { result = fail; }
    if (self->setDefault(self->defaultSize, 0).isFailed(fail)) { result = fail; }
    if (self->apply().isFailed(fail)) { result = fail; }
    if (g_useOwnerAllocator == 0) {
        for (i = 0; i < 46; i++) {
            if (i != 0) {
                PoolConfigObject **slot = (PoolConfigObject **)((char *)self + i * 144 + 20);
                PoolConfigObject *p = *slot;
                if (p == mainPool) {
                    p->rc = p->rc - 1;
                    if (((unsigned long long)((long long)(int)p->rc << 0x29) >> 0x29) == 0) igObject_Destroy(p);
                    *slot = 0;
                }
            }
        }
        for (i = 0; i < 46; i++) {
            if (i == 2) {
                self->setPool(i, self->third);
            } else {
                if (self->build(i, 0).isFailed(fail)) { result = fail; }
            }
        }
    } else {
        self->setPool(2, self->third);
    }
    self->finish();
    o = self->poolFor(20);
    if (o != mainPool && o != second) { ((PoolConfigContext *)g_objectSystem[0])->a88 = o; }
    o = self->poolFor(7);
    if (o != mainPool && o != second) { ((PoolConfigContext *)g_objectSystem[0])->a96 = o; }
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && o->inUse() == 0) { o->finish(); }
    }
    if (DAT_004c2370[0] & 8) {
        mainPool->lock(1);
        if (second != mainPool) { second->lock(1); }
    }
    if (result == g_statusSucceeded.v) { self->setFlags(self->flags | 8); }
    *out = result;
}


extern "C" int FUN_002f00f0(int);
struct Cnt { int pad[11]; int count; };
struct Sub {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual struct Cnt * f20();
};
struct Mgr {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void f47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void f51(int);
    virtual void d52();
    virtual void f53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void f64(int);
};
/* The skip list 6/5/4/0 is a switch, which leaves the compare-chain delay slots empty. The second
 * loop is dead code and is kept. */
extern "C" void FUN_002f50e0(Mgr *arg0);


extern int g_igMemoryPool_metaObject[4];
extern "C" int FUN_002f5220(void);


extern char DAT_004fa580[];
extern char DAT_004fa5a0[];
extern char DAT_004fa5c0[];
extern char DAT_004fa5d0[];
extern char DAT_004fa5e8[];
extern char DAT_004fa5f0[];
extern char DAT_004fa600[];
extern char DAT_004fa610[];
class PoolDescTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual igResult load(int, char *); int rc; };
class PoolDescSetupBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual char *recordName(int); };
class PoolDescSetup : public PoolDescSetupBase { public: char q4[12]; PoolDescTable *table; PoolDescSlot slots[46]; };
struct PoolDescContext { char p0[56]; int config; };
static inline void releaseTable(PoolDescTable *t) {
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)(int)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
}
extern "C" void FUN_002f5230(int *out, PoolDescSetup *self, int config, char *name);


extern "C" void FUN_002f5c30(void *arg0);
struct Sub2 { char p[132]; int f132; };
struct Obj4 { char p0[4]; int refs; };
struct T { char p0[16]; Obj4 *f16; Sub2 f20; };
void FUN_002f5c30(void *arg0);


extern "C" void FUN_002f5cc0(int *arg0);


struct R3 { int v; R3() {} int get() { return v; } };
class OV;
class OV { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual void d15();
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual void d19();
  virtual void d20();
  virtual void d21();
  virtual R3 v96(int a, long long b, int c);
  virtual void d23();
  virtual void d24();
  virtual void d25();
  virtual void d26();
  virtual void d27();
  virtual void v120();
  virtual void d29();
  virtual void d30();
  virtual int v132();
  virtual void d32();
  virtual void d33();
  virtual void d34();
  virtual void d35();
  virtual void d36();
  virtual void d37();
  virtual void d38();
  virtual void d39();
  virtual void d40();
  virtual R3 v172(int a);
  virtual void d42();
  virtual R3 v180(igMemoryPoolInfo *c);
  virtual void d44();
  virtual void d45();
  virtual void d46();
  virtual void d47();
  virtual void d48();
  virtual void d49();
  virtual void d50();
  virtual void d51();
  virtual int v216(int a);
  virtual void d53();
  virtual void d54();
  virtual void d55();
  virtual void d56();
  virtual void d57();
  virtual void d58();
  virtual void d59();
  virtual void d60();
  virtual void d61();
  virtual void d62();
  virtual void d63();
  virtual void d64();
  virtual void d65();
  virtual void d66();
  virtual void d67();
  virtual void d68();
  virtual void d69();
  virtual void d70();
  virtual void d71();
  virtual void d72();
  virtual void d73();
  virtual void d74();
  virtual void d75();
  virtual void d76();
  virtual void d77();
  virtual void d78();
  virtual void d79();
  virtual void d80();
  virtual void d81();
  virtual void d82();
  virtual void d83();
  virtual void d84();
  virtual void d85();
  virtual void d86();
  virtual void d87();
  virtual void d88();
  virtual void d89();
  virtual void d90();
  virtual void d91();
  virtual void d92();
  virtual void d93();
  virtual void d94();
  virtual void d95();
  virtual void d96();
  virtual void d97();
  virtual void v400(igMemoryPool *o);
};
struct Slot { igMemoryPool *obj; char p[128]; igMemoryPoolInfo *cfg; int f136; int f140; };
class MC { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual void d15();
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual void d19();
  virtual void d20();
  virtual void d21();
  virtual igMemoryPool *v96(char *n);
  virtual void v100(int i, igMemoryPool *o);
  virtual void d24();
  virtual void d25();
  virtual void d26();
  virtual int v116(char *n);
  virtual void d28();
  virtual void d29();
  virtual void d30();
  virtual void d31();
  virtual void d32();
  virtual void d33();
  virtual void d34();
  virtual void d35();
  virtual void d36();
  virtual void d37();
  virtual void d38();
  virtual void d39();
  virtual void d40();
  virtual void d41();
  virtual void d42();
  virtual void d43();
  virtual void d44();
  virtual void d45();
  virtual void d46();
  virtual void d47();
  virtual void d48();
  virtual R3 v204(int i, int f);
  int a4, a8, flags, a16;
  Slot slots[8];
};
class Gl { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual int v68(int a, int b);
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual int v84();
};
extern "C" igMemoryPool *igAliasMemoryPool_Create(igMemoryPool *);
extern "C" igMemoryPool *igMetaObject_CreateInstance(int, igMemoryPool *);
extern "C" int igObjectSystem_FindMetaByNameDefault(char *);
extern "C" void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag);
extern int DAT_00587020[4];
extern int DAT_00587030[4];
extern int g_metadataAllocatorKey[4];
extern char DAT_004fa2a8[], DAT_004fa2b0[], DAT_004fa5e8[], DAT_004fa5f0[], DAT_004fa600[], DAT_004fa620[], DAT_004fa630[], DAT_004fa638[], DAT_004fa640[], DAT_004fa648[], DAT_004fa658[], DAT_004fa668[], DAT_004fa678[], DAT_004fa680[], DAT_004fa688[], DAT_004fa690[], DAT_004fa698[];
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag);


struct R4 { int v; R4() {} };
class Ctx3;
extern "C" void MemoryContext_BuildAndAttachEventTracker(struct R4 *arg0, class Ctx3 *arg1, int arg2);
class Trk { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void v360(void *); };
class Evt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void *v356(); };
class Obj5 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); int rc; };
class Ctx3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Evt *v92(int); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual R4 v204(int, int); int p4; int p8; int flags; };
struct Gl2 { char p[124]; void *f124; };
struct Slot2 { char p[20]; Trk *trk; char q[128]; igMemoryPoolInfo *sub; };
#define RC2(o) ((unsigned long long)(long long)((igObject *)(o))->_refCount & 0x7fffffULL)
void MemoryContext_BuildAndAttachEventTracker(R4 *out, Ctx3 *self, int idx);


extern "C" void *Memory_FindOwningAllocator(...);
extern "C" int Memory_FreeBuffer(...);
extern "C" void MemoryContext_RemoveAllocator(void *arg0, int arg1);
class C72 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual R4 vX(int,long long); };
class C96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual R4 vX(int,int,int); };
class C104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class C128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(); };
class C144 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
class C188 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(); };
class C348 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual int vX(int); };
typedef igObject Obj6;
struct Ctx4 { char p[8]; int f8; };
struct Slot3 { Obj6 *obj; char q[132]; int flags; };
void MemoryContext_RemoveAllocator(void *arg0, int arg1);


struct RefCount { union { int w; struct { unsigned cnt : 23; unsigned f : 9; } b; } u; };
struct StringHeader { int chunk; int refs; };
static inline void releaseString(char *p) {
    if (p != 0) {
        StringHeader *h = (StringHeader *)(p - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader(h->chunk, h); }
    }
}
class EventTracker { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void start();
    RefCount rc; char q8[36]; int users; };
class PoolLoader { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual igResult load(char *); virtual igResult finish(); virtual void p24(); virtual void p25(); virtual igResult attach(void *, int); virtual void p27(); virtual void p28(); virtual void optionA(); virtual void optionB();
    RefCount rc; };
struct LoadedObject { int vt; RefCount rc; };
class TrackedPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual int hasTracker(); virtual void setTracker(EventTracker *); };
class PoolSetupBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void setFlags(int); };
class PoolSetup : public PoolSetupBase { public: char q4[8]; int flags; char q16[4]; PoolDescSlot slots[46]; };
struct MemoryContextState {
    char p0[48]; TrackedPool *main; TrackedPool *second; int config; char p60[20];
    LoadedObject *loaded; EventTracker *tracker; char p88[28];
    unsigned char trackEvents; unsigned char flag117; unsigned char flag118; unsigned char flag119; unsigned char flag120; char p121[3];
    int value124; int value128; int value132; int value136; int value140;
};
extern int DAT_004c1eb0;
extern char DAT_004fa6a0[];
extern char DAT_004fa6c0[];
extern char DAT_004fa6e0[];
extern char DAT_004fa6f0[];
extern char DAT_004fa710[];
extern char DAT_004fa730[];
extern char DAT_004fa750[];
extern char DAT_004fa770[];
extern char DAT_004fa790[];
extern char DAT_004fa7b0[];
extern char DAT_004fa7e0[];
extern char DAT_004fa810[];
extern char DAT_004fa830[];
extern char DAT_004fa850[];
extern char DAT_004fa870[];
extern char DAT_004fa890[];
extern char DAT_004fa8b0[];
extern char DAT_004fa8d0[];
extern char DAT_004fa8f0[];
extern char DAT_004fa900[];
extern char DAT_004fa918[];
extern "C" int FUN_002f00e0(void);
extern "C" void FUN_00306910(int, int, char *, char **, char *, int);
extern "C" void FUN_002d31d0(MemoryContextState *, char *);
extern "C" void FUN_002d3240(MemoryContextState *, char *);
extern "C" void FUN_002d32b0(MemoryContextState *, char *);
extern "C" void FUN_002d3320(MemoryContextState *, char *);
extern "C" void FUN_002d3370(MemoryContextState *, char *);
extern "C" void FUN_002d33c0(MemoryContextState *, char *);
extern "C" void FUN_002f0db0(int);
extern "C" PoolLoader *FUN_002cec00(int);
extern "C" LoadedObject *FUN_002b8500(int);
static inline int trackerSizeFor(PoolDescRecord *record, int fallback) {
    int size = fallback;
    int n = record->a80;
    if (n != 0) { size = n; }
    return size;
}
extern "C" void FUN_002f69b0(PoolSetup *self);


extern "C" void FUN_002f7410(int arg0, int arg1);


extern "C" int FUN_0030d080(int);
extern "C" int FUN_0030d1d0(int, int);
extern "C" int FUN_0030d4a0(int, int);
extern "C" int *FUN_002ee430(int);
extern "C" void qsort(void *, int, int, int (*)(const void *, const void *));
extern "C" int FUN_002e1500(void *, int);
extern int DAT_004f95a0[4];
extern int DAT_004fa930[4];
extern int DAT_004fa988[4];
extern int DAT_004fa990[4];
extern int DAT_004fa9b0[4];
extern int DAT_004fa9d0[4];
enum LeakKind { LeakKindFirst = 0, LeakKindCount = 32 };
class LeakReportTracker { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void summary(int, int, int *, int *, int *, int *, int *, int *, int *, int *, int *, int, int, int *, int, int); virtual void describe(int, int, int, int *, int *, int *, int *);
  int rc; char q8[48]; int names; };
struct LeakReportContext { char p0[84]; LeakReportTracker *tracker; char p88[30]; unsigned char dumpLeaks; unsigned char dumpSummary; unsigned char dumpNames; };
class LeakReportOwner { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void flush(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual int count(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void dump(); };
class LeakReportPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual LeakReportOwner *owner(); virtual void release(int); };
struct LeakReportSlot { char p0[20]; LeakReportPool *pool; char p24[120]; };
extern "C" void FUN_002f7420(LeakReportSlot *self);


extern "C" int FUN_002dcc50(void *);
extern char DAT_004fab08[];
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual R v176(char *); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual VB * v356(); };
extern "C" void FUN_002f78b0(VA *arg0);
void FUN_002f78b0(VA *arg0);


class SlotOwnerObject { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual void vDrop();
};
class SlotPool { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48();
 virtual igResult vRelease(int, int);
 virtual void e51();
 virtual void vFree(int);
};
struct PoolSlotEntry { SlotOwnerObject *owner; char pad[136]; unsigned int flags; };
extern "C" igResult FUN_002f7a70(SlotPool *self, unsigned int kind, int free);


class DW4VC_356_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int vX(); };
struct Ent { char pad[20]; DW4VC_356_0 *obj; char pad2[120]; };
extern "C" void FUN_002f7bc0(Ent *arg0, int arg1);
void FUN_002f7bc0(Ent *arg0, int arg1);


struct E2 { char pad[20]; DW4VC_356_0 *f20; char pad2[120]; };
extern "C" void FUN_002f7cc0(E2 *arg0, int arg1, int *arg2, int arg3);
void FUN_002f7cc0(E2 *arg0, int arg1, int *arg2, int arg3);


extern "C" void FUN_002f7e00(E2 *arg0, int *arg1, int arg2);
void FUN_002f7e00(E2 *arg0, int *arg1, int arg2);


extern "C" void FUN_002f7f20(int arg0, int arg1);
void FUN_002f7f20(int arg0, int arg1);


struct Obj7 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual int vid();
};
struct Slot4 { char pad[20]; Obj7 *obj; char pad24[120]; };
extern "C" void FUN_002f8020(Slot4 *slots, int arg1, int *out, int n);


class V2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int vX(); };
struct Slot5 { char p[20]; V2 *f20; char p2[0x90 - 24]; };
/* The comma expression pins the operand order of the duplicate test. */
extern "C" void FUN_002f8160(Slot5 *arg0, int *arg1, int arg2);


struct Res {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual void r4();
    virtual void r5();
    virtual void r6();
    virtual void r7();
    virtual void r8();
    virtual void r9();
    virtual void r10();
    virtual void r11();
    virtual void r12();
    virtual void r13();
    virtual void r14();
    virtual void r15();
    virtual void r16();
    virtual void r17();
    virtual void r18();
    virtual void r19();
    virtual void r20();
    virtual void r21();
    virtual void r22();
    virtual void r23();
    virtual void v24(int *, int);
    int p[3];
    int flags;
    int p2;
    int mask;
};
struct Dev {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual Res *getRes();
};
struct Slot6 { char p[20]; Dev *dev; char q[120]; };
extern "C" int FUN_002e2250(int *, int, int, int, int, int, int, int, long long, long long);
extern "C" int FUN_002e2300(int *, int);
extern "C" void FUN_002f8280(Slot6 *arg0, int arg1, int arg2, int arg3);
/* The flag tests are `((x & m) ? 1 : 0) &&`; the ternary gives the materialised sltu. The two
 * later virtual slots are dummy-virtual stubs. */
void FUN_002f8280(Slot6 *arg0, int arg1, int arg2, int arg3);


extern char DAT_004fab10[], DAT_004fab20[], DAT_004f90b0[], DAT_004fab30[];
class VB2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void * v88(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void v348(int); };
struct Z { int w[7]; int f28; };
extern "C" void FUN_002f8420(VA *arg0, char *arg1, VB2 *arg2);
void FUN_002f8420(VA *arg0, char *arg1, VB2 *arg2);


extern "C" int FUN_002f0a60(...);
extern int DAT_004f95c8[4];
extern int DAT_004fab70[4];
extern int DAT_004fab90[4];
struct E3 { char p[20]; int f20; char q[120]; };
extern "C" void FUN_002f8580(E3 *arg0, int *arg1);
class DW4VC_144_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
class DW4VC_260_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual int vX(int, int); };
void FUN_002f8580(E3 *arg0, int *arg1);


extern int DAT_00586ffc[4];
extern "C" int Memory_GetCurrentContext(void);


extern "C" igResult FUN_002f86e0(void *arg1);


struct ContextStackEntry {
    int pad;
    union {
        int w;
        struct {
            unsigned cnt : 23;
            unsigned f : 9;
        } b;
    } u;
};
extern "C" struct ContextStackEntry *FUN_002f8760(void);


extern "C" int malloc(...);
extern "C" int igObject_AllocateRawStorageDefault(...);
extern "C" void FUN_002f87f0(int arg0);


extern "C" void free(void *allocation);
extern "C" void thunk_FUN_002ed460__002ff810(void *allocation);
/* Releases an allocation owned by a pool context. While the object system is active (flag byte at
 * the start of the record behind g_objectSystem[0]) the call goes to Memory_FreeBuffer through its
 * j-thunk; otherwise it takes the early-boot path free. Neither callee's argument is
 * touched here: `allocation` is passed straight through in the first argument register. */
/* Object-system record pointer; byte 0 is the "object system active" flag. */
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *allocation);



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
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }

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
void *FUN_002eb010(int);
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
extern char *DAT_004c2170[46];
extern void *DAT_00586dc8;
extern void *DAT_00586fd0;
extern void *DAT_00586f20;
extern void *DAT_00587218[4];
extern char DAT_004fa530[];
extern char DAT_004fa550[];
}

extern "C" int igObject_InitHeader(...);
extern int DAT_0052f510[4];
struct Ref { int pad0; int f4; };
struct BF { unsigned lo : 23; unsigned hi : 9; };
/* dispatch-only view of the object: 43 vtable slots then the init slot (no fields) */
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void vX(); };
/* Refcount field as a 23+9 bit-field (read-modify-write with a 64-bit constant) and a 43-slot
 * virtual call. */
/* matching construct: the word at +16 is stored/loaded as a reference pointer (the reflected _resolveState is a 1-byte bool there; code wins); the vtable is the reflected int _vtable, called through slot 45 */
extern "C" igMemoryPoolContextInfo *igMemoryPoolContextInfo_Construct(igMemoryPoolContextInfo *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)&DAT_0052f510[0];
    arg0->_name = 0x1E;
    arg0->_directory = 0;
    *(Ref **)&arg0->_resolveState = 0;
    if (*(Ref **)&arg0->_resolveState != 0) {
        (*(Ref **)&arg0->_resolveState)->f4 += 1;
    }
    arg0->_refCount = 0;
    ((BF *)&arg0->_refCount)->lo = 1;
    memset(&arg0->_memoryPoolInfos, 0, 0x19E0);
    ((Obj *)arg0)->vX();
    return arg0;
}


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
extern "C" void *igMemoryPoolContextInfo_Destruct(ContextView *self, long long deleteFlags) {
    if (self) {
        self->_vtable = (int)g_igMemoryPoolContextInfo_vtable; self->_refCount = 0;
        memset(self->records, 0, 6624); ((ContextVirtuals *)self)->InitializeRecordNames();
        if ((char *)self + 16) {
            igObject *parent = self->parent;
            if (parent) {
                --parent->_refCount;
                if (!(parent->_refCount & 0x7fffff)) igObject_Destroy(parent);
            }
        }
        if ((short)deleteFlags > 0) igMemoryPoolContextInfo_DeleteAllocation(self);
    }
    return self;
}


struct R { int a; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v92(int); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual R v208(int); };
struct E { int pad[5]; int key; int val[30]; };
struct Ctx : VC { };
extern int DAT_00587010[4];
extern "C" int FUN_002f2730(Ctx *arg0, int arg1);
int FUN_002f2730(Ctx *arg0, int arg1) {
    int i, j;
    int r = 0;
    if (arg1 >= 0 && arg1 < 46) {
        char *e = (char *)(arg1 * 144) + (int)arg0;
        int *pk = (int *)(e + 20);
        r = *pk;
        if (r == 0) {
            if (*(int *)(e + 160) & 0x04000000) {
                arg0->v208(arg1);
                return *pk;
            }
            if (1 < DAT_00587010[0]) {
                for (i = DAT_00587010[0] - 1; i >= 0; i--) {
                    if (DAT_00587000[i] == (VC *)arg0) break;
                }
                j = i - 1;
                if (j >= 0) {
                    VC *p = (VC *)DAT_00587000[j];
                    if (p != (VC *)arg0) r = p->v92(arg1);
                }
            }
        }
    }
    return r;
}


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
extern "C" void *FUN_002f2830(ContextVirtuals2 *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!strcmp(((ContextRecords *)self)->records[i].name, name)) return self->Lookup(i);
        }
    }
    return 0;
}


/* (vtable offset 100) Bind `value` to record `index` (0..45). Re-binding the same object is a no-
 * op; a different old binding is released through Clear first. The new object is retained, and a
 * non-null binding raises the used-record count. */
extern "C" void FUN_002f28d0(ContextView *self, int index, igObject *value) {
    if (index >= 0 && index < 46) {
        /* record address spelled as index * 144 + self (+ 20 for the allocator word); the
         * typed spelling &self->records[index] changes the bytes */
        unsigned int address = (unsigned int)index * 9; address <<= 4; address += (unsigned int)self;
        igObject **slot = (igObject **)(address + 20);
        igObject *previous = *slot;
        if (!previous || previous != value) {
            if (previous) ((ContextVirtuals *)self)->Clear(index);
            *slot = value;
            if (value) {
                ++value->_refCount;
                if (index >= self->usedRecords) self->usedRecords = index + 1;
            }
        }
    }
}


extern "C" int FUN_002f2990(int arg0, int arg1) {
    if ((arg1 >= 0) && (arg1 < 0x2E)) {
        return arg0 + (arg1 * 0x90) + 0x18;
    }
    return (int)&DAT_004f7910[0];
}


class VC2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int *v108(int); };
struct Ctx2 { E e[46]; };
extern "C" int *FUN_002f29d0(Ctx2 *arg0, int arg1);
/* The global count test is written `1 < n`. */
int *FUN_002f29d0(Ctx2 *arg0, int arg1) {
    int i, j;
    if (arg1 != 0) {
        for (i = 0; i < 46; i++) {
            { int k = arg0->e[i].key; if (k == arg1) return arg0->e[i].val; }
        }
    }
    if (1 < DAT_00587010[0]) {
        for (i = DAT_00587010[0] - 1; i >= 0; i--) {
            if (DAT_00587000[i] == (VC2 *)arg0) break;
        }
        j = i - 1;
        if (j >= 0) {
            VC2 *p = (VC2 *)DAT_00587000[j];
            if (p != (VC2 *)arg0) return p->v108(arg1);
        }
    }
    return (int *)DAT_004f7910;
}


#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_RECORD_SIZE 0x90
#define CONTEXT_RECORDS_OFFSET 0x14
#define CONTEXT_RECORD_NAME_MAX 0x7F
/* Renames record `recordIndex` of the context: copies at most 127 characters into the record's
 * inline 128-byte name field, terminates it, and renames the record's bound named object (if any)
 * to match. Out-of-range indices are ignored. The context holds 46 records of 144 bytes starting
 * at +0x14, each with a 128-byte inline name at +4. */
extern "C" void FUN_002f2ab0(int self, int recordIndex, int name) {
    int boundObject;
    void *record;

    if ((recordIndex >= 0) && (recordIndex < CONTEXT_RECORD_COUNT)) {
        record = (void *)(self + (recordIndex * CONTEXT_RECORD_SIZE) + CONTEXT_RECORDS_OFFSET);
        strncpy((char *)record + 4, name, CONTEXT_RECORD_NAME_MAX);
        *(char *)((char *)(record) + 131) = 0;
        boundObject = *(int *)((char *)(record) + 132);
        if (boundObject != 0) {
            igNamedObject_SetName(boundObject, name);
        }
    }
}


extern "C" int FUN_002f2b30(int arg0, char *arg1) {
    int i;

    if (arg1 != 0 && *arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(arg0 + (i * 0x90) + 0x18, arg1) == 0) {
                return i;
            }
        }
    }
    return -1;
}


extern "C" int strncmp(...);
extern int DAT_004fa3b0[4];
extern int DAT_004fa3c8[4];
extern "C" int FUN_002f2bc0(int arg0, char *arg1) {
    int i;
    char *s = arg1;
    if (s != 0 && *s != 0) {
        if (strncmp(s, &DAT_004fa3b0[0], 0x13) == 0) {
            s += 0x13;
        } else if (strncmp(s, &DAT_004fa3c8[0], 0xD) == 0) {
            s += 0xD;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(arg0 + i * 0x90 + 0x18, s) == 0) return i;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(*(int *)((char *)DAT_004c2170 + i * 4), s) == 0) return i;
        }
    }
    return -1;
}


extern "C" int FUN_002f2cd0(int arg0, int arg1) {
    int i;
    if (arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (arg1 == *(int *)((char *)((arg0 + (i * 0x90))) + 20)) {
                return i;
            }
        }
    }
    return -1;
}


struct R2 { int v; R2() {} R2(int x) { v = x; } };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
class Child { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual R2 vA(int, int); };
class Self { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual R2 vB(int, int); };
struct OB { int vt; int a4; int a8; int a12; RO *f16; };
extern "C" R2 FUN_002f2d20(OB *arg1, int arg2, int arg3) {
    int temp_s0;
    RO *temp_a0;
    if (arg1->f16 == 0) {
        temp_s0 = igObject_GetAllocator(arg1);
        temp_a0 = arg1->f16;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        arg1->f16 = (RO *)FUN_002c01f0(temp_s0);
    }
    if (arg2 == 0) {
        arg2 = *(int *)((char *)DAT_00586dc8 + 56);
    }
    R2 sp6C = ((Child *)arg1->f16)->vA(arg2, arg3);
    if (sp6C.v == DAT_004fb410.v) {
        R2 sp68 = ((Self *)arg1)->vB((int)arg1->f16, 1);
        sp6C = sp68;
    }
    return sp6C;
}


class Child2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual R2 vA(int, int); };
extern "C" R2 FUN_002f2e30(OB *arg1, int arg2, int arg3) {
    int temp_s0;
    RO *temp_a0;
    if (arg1->f16 == 0) {
        temp_s0 = igObject_GetAllocator(arg1);
        temp_a0 = arg1->f16;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        arg1->f16 = (RO *)FUN_002c01f0(temp_s0);
    }
    if (arg2 == 0) {
        arg2 = *(int *)((char *)DAT_00586dc8 + 56);
    }
    R2 sp6C = ((Child2 *)arg1->f16)->vA(arg2, arg3);
    if (sp6C.v == DAT_004fb410.v) {
        R2 sp68 = ((Self *)arg1)->vB((int)arg1->f16, 1);
        sp6C = sp68;
    }
    return sp6C;
}


struct igRefHead { int vt; int rc; };
class SlotReadTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual igResult readOne(int, igRefHead *);
};
extern "C" igResult FUN_002f2f40(SlotReadTable *self, int file) {
    igResult result = DAT_004fb410;
    int i;
    FUN_002f8b20(file);
    for (i = 0; i < 46; i++) {
        if (*(int *)((char *)self + i * 144 + 152) != 0) {
            igRefHead *o = (igRefHead *)FUN_002bfed0(igObject_GetAllocator(file));
            int fail;
            if (self->readOne(i, o).isFailed(fail)) {
                o->rc = o->rc - 1;
                result.v = fail;
                if (((unsigned long long)((long long)(int)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o);
            } else {
                FUN_002f8a80(file, o);
            }
        }
    }
    return result;
}


extern "C" int FUN_002f8a50(int);
extern "C" void *FUN_002f8a60(int, int);
struct DirSlotObject { int vt; int rc; };
struct DirSourceRecord { char p0[20]; int id; };
class DirSlotTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slotFor(int); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual igResult fillSlot(int, DirSourceRecord *, int);
  char q4[12]; DirSlotObject *slots; };
extern "C" igResult FUN_002f3060(DirSlotTable *self, int file, int arg) {
    int count = FUN_002f8a50(file);
    igResult result = DAT_004fb410;
    int fail;
    int i;
    if (self->slots == 0) {
        int allocator = igObject_GetAllocator(self);
        DirSlotObject *old = self->slots;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->slots = (DirSlotObject *)FUN_002c01f0(allocator);
    }
    for (i = 0; i < count; i++) {
        DirSourceRecord *r;
        if ((r = (DirSourceRecord *)FUN_002f8a60(file, i)) != 0) {
            if (self->fillSlot(self->slotFor(r->id), r, arg).isFailed(fail)) {
                result.v = fail;
            }
        }
    }
    return result;
}


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
extern int DAT_00586a88[4];
extern char DAT_004fa3e0[];
#define ASSIGN_TOKEN(field, source)                                           \
    text = (source);                                                          \
    if (DAT_00586f20 == 0) {                                               \
        poolObj = FUN_002eb010(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        DAT_00586f20 = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(DAT_00586f20, text);          \
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
    if (DAT_00586f20 == 0) {                                               \
        poolObj = FUN_002eb010(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        DAT_00586f20 = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(DAT_00586f20, (source));          \
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
 * from the table name 'kIGMemoryPoolHandle%s'. The status written through `result` is DAT_004fb410
 * on success and DAT_004fb418 for an out-of-range index. */
extern "C" void FUN_002f31b0(int *result, PoolTable *table, int index, PoolHandle *handle)
{
    StringToken *old;
    const char *text;
    SizedObject *object;
    StringTokenHeader *header;
    PoolEntry *entry;
    char nameBuf[128];
    void *poolObj;
    int count;
    StringToken *token;
    int status;

    status = DAT_004fb410.v;
    if (index >= 0 && index < 46) {
        entry = &table->entries[index];
        igNamedObject_SetName(handle, entry->name);
        if (entry->defaults != 0) {
            ASSIGN_TOKEN(handle->token0, entry->defaults->text0);
            object = table->entries[index].object;
            if (object != 0) {
                if (igObject_IsKindOf(object, DAT_00586a88[0]) != 0) {
                    if (object->count() != 0) {
                        if (object->total() > object->count()) {
                            entry->defaults->limit = (int)object->total();
                        }
                    } else if (object->hasLimitOrSize() != 0) {
                        entry->defaults->limit = (int)object->limit();
                    }
                } else if (object->limit() != 0) {
                    entry->defaults->limit = (int)object->limit();
                }
            }
            handle->limit = entry->defaults->limit;
            handle->field20 = entry->defaults->field20;
            handle->field24 = entry->defaults->field24;
            ASSIGN_TOKEN(handle->token1, entry->defaults->text1);
            ASSIGN_TOKEN(handle->token2, entry->defaults->text2);
            ASSIGN_TOKEN(handle->token3, entry->defaults->text3);
            ASSIGN_TOKEN(handle->token4, entry->defaults->text4);
            ASSIGN_TOKEN(handle->token5, entry->defaults->text5);
            ASSIGN_TOKEN(handle->token6, entry->defaults->text6);
            ASSIGN_TOKEN(handle->token7, entry->defaults->text7);
            ASSIGN_TOKEN(handle->token8, entry->defaults->text8);
            ASSIGN_TOKEN(handle->token9, entry->defaults->text9);
            ASSIGN_TOKEN(handle->token10, entry->defaults->text10);
            handle->field50 = entry->defaults->field50;
        }
        sprintf(nameBuf, DAT_004fa3e0, DAT_004c2170[index]);
        ASSIGN_TOKEN_DIRECT(handle->handleName, nameBuf);
    } else {
        status = DAT_004fb418.v;
    }
    *result = status;
}


extern char DAT_004e0858[];
extern int DAT_00587018[4];
struct PoolDescString { int chunk; int refs; };
static inline void *descPool() {
    if (DAT_00586f20 == 0) {
        void *p = FUN_002eb010(16);
        if (p != 0) { p = StringPool_Construct(p); }
        DAT_00586f20 = p;
    }
    return DAT_00586f20;
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
static inline char *descName(PoolDescRecord *r) { char *n = r->name; if (n != 0) { return n; } return DAT_004e0858; }
extern "C" igResult FUN_002f3910(PoolDescManager *self, int index, PoolDescRecord *desc, int build) {
    igResult result = DAT_004fb410;
    int fail;
    PoolDescSlot *slot;
    if (index == -1) {
        index = self->nextSlot;
        if (index < 46) {
            setDescString(&desc->alias, DAT_004c2170[index]);
            self->nextSlot = self->nextSlot + 1;
        }
    } else if (index >= self->nextSlot) {
        self->nextSlot = index + 1;
    }
    if (index >= 0 && index < 46) {
        slot = (PoolDescSlot *)((char *)self + index * 0x90 + 0x14);
        strncpy(slot->name, descName(desc), 0x7f);
        slot->name[127] = 0;
        slot->record = FUN_002f8be0(self->table, descName(desc));
        if (slot->record == 0) { slot->record = FUN_002f8ca0(self->table, desc->alias); }
        if (slot->record == 0) {
            slot->record = (PoolDescRecord *)FUN_002bfed0((int)Memory_GetAllocatorBySelector(DAT_00587018[0]));
            FUN_002f8a80(self->table, slot->record);
        }
        if (slot->record != desc) {
            { PoolDescRecord *d; char *src; src = desc->s24; d = slot->record; setDescString(&d->s24, src); }
            slot->record->a28 = desc->a28;
            slot->record->a32 = desc->a32;
            slot->record->a36 = desc->a36;
            { PoolDescRecord *d; char *src; src = desc->s40; d = slot->record; setDescString(&d->s40, src); }
            { PoolDescRecord *d; char *src; src = desc->s44; d = slot->record; setDescString(&d->s44, src); }
            { PoolDescRecord *d; char *src; src = desc->s48; d = slot->record; setDescString(&d->s48, src); }
            { PoolDescRecord *d; char *src; src = desc->s52; d = slot->record; setDescString(&d->s52, src); }
            { PoolDescRecord *d; char *src; src = desc->s56; d = slot->record; setDescString(&d->s56, src); }
            { PoolDescRecord *d; char *src; src = desc->s60; d = slot->record; setDescString(&d->s60, src); }
            { PoolDescRecord *d; char *src; src = desc->s64; d = slot->record; setDescString(&d->s64, src); }
            { PoolDescRecord *d; char *src; src = desc->s68; d = slot->record; setDescString(&d->s68, src); }
            { PoolDescRecord *d; char *src; src = desc->s72; d = slot->record; setDescString(&d->s72, src); }
            { PoolDescRecord *d; char *src; src = desc->s76; d = slot->record; setDescString(&d->s76, src); }
            slot->record->a80 = desc->a80;
        }
        if (build != 0) {
            if (self->build(index, 0).isFailed(fail)) { result.v = fail; }
        }
    } else {
        result = DAT_004fb418;
    }
    return result;
}


extern "C" void FUN_002f4060(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = arg1;
}


extern "C" void FUN_002f4070(void *arg0);
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
class DW4VC_152_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int); };
void FUN_002f4070(void *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void **temp_a0_2;
    void **temp_a0;
    void ***var_s1;
    int var_s0;

    var_s1 = (void ***)((char *)arg0 + 0x14);
    var_s0 = 0;
    do {
        temp_a0 = (void **)(*var_s1);
        if ((temp_a0 != 0) && (((DW4VC_132_0 *)(temp_a0))->vX() == 0)) {
            temp_a0_2 = (void **)(*var_s1);
            ((DW4VC_120_0 *)(temp_a0_2))->vX();
        }
        var_s0 += 1;
        var_s1 = (void ***)((char *)var_s1 + 144);
    } while (var_s0 < 0x2E);
    ((DW4VC_152_1 *)(((char *)(arg0) + 0)))->vX((int)(*(int *)((char *)(arg0) + 12) | 8));
}


class Obj2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual int v85(int); int f4; };
class Par { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v36(int); int f4; int f8; int f12; };
extern "C" void FUN_002f4110(Par *arg0) {
    Obj2 **p;
    int i;
    p = (Obj2 **)((char *)arg0 + 0x14);
    for (i = 0; i < 0x2E; i++) {
        Obj2 *o = *p;
        if (o != 0 && (o->f4 & 0x7FFFFF) == 1) {
            if (o->v45() != 0) {
                (*p)->v85(0);
            }
            (*p)->v30();
        }
        p = (Obj2 **)((char *)p + 0x90);
    }
    arg0->v36(arg0->f12 & ~8);
}


struct Obj3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void FUN_002f41e0(char *arg0);
void FUN_002f41e0(char *arg0) {
    Obj3 **p;
    int i;
    p = (Obj3 **)(arg0 + 20);
    i = 0;
    do {
        Obj3 *o = *p;
        if (o != 0) {
            if (o->u.b.cnt == 1) {
                o->v29();
            }
        }
        i++;
        p = (Obj3 **)((char *)p + 144);
    } while (i < 46);
}


extern "C" void FUN_002f4250(void **arg0);
class DW4VC_180_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual int vX(); };
class DW4VC_196_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual int vX(); };
class DW4VC_212_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int vX(int); };
class DW4VC_220_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(); };
void FUN_002f4250(void **arg0) {
    int var_s0;

    ((DW4VC_196_0 *)(arg0))->vX();
    ((DW4VC_220_0 *)(arg0))->vX();
    var_s0 = 0x2D;
    do {
        ((DW4VC_212_1 *)(arg0))->vX((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 20, 0, 0x19E0);
    ((DW4VC_180_0 *)(arg0))->vX();
}


extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" void FUN_002f42e0(void **arg0, int arg1);
void FUN_002f42e0(void **arg0, int arg1) {
    memset((char *)arg0 + 0x14, 0, 0x19E0);
    ((DW4VC_180_0 *)(arg0))->vX();
    Gap__Core__igObject__vfunc_11(arg0, arg1);
}


extern "C" int Gap__Core__igObject__vfunc_02(...);
extern "C" void FUN_002f4340(void **arg0);
void FUN_002f4340(void **arg0) {
    int var_s0;

    Gap__Core__igObject__vfunc_02();
    var_s0 = 0x2D;
    do {
        ((DW4VC_212_1 *)(arg0))->vX((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 0x14, 0, 0x19E0);
}


extern char *DAT_00586de8;
extern int DAT_004f8b50[4];
extern int DAT_004f8c80[4];
extern int DAT_00586fd8[4];
extern int DAT_00586fe0[4];
extern int DAT_00586fe8[4];
extern int DAT_00586ff0[4];
extern unsigned char GPR_00554c14;
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
#define NEW_POOL(p) { if (DAT_00586de8 != 0) { if (strcmp(DAT_00586de8, DAT_004f8b50) == 0) { NEW_LARGE_POOL(p) } else if (strcmp(DAT_00586de8, DAT_004f8c80) == 0) { NEW_SMALL(p) } else { NEW_LARGE_POOL(p) } } else { NEW_LARGE_POOL(p) } }
extern "C" void FUN_002f43a0(PoolSlotTable *self) {
    PoolObject *p;
    int i;
    FUN_002f86e0(self);
    i = 0;
    do {
        switch (i) {
        case 0:
            NEW_POOL(p)
            break;
        case 4: case 5: case 6:
            if (GPR_00554c14 != 0) { p = self->first; } else { NEW_POOL(p) }
            break;
        default:
            p = self->first;
            break;
        }
        *(PoolObject **)((char *)self + i * 144 + 20) = p;
        if (GPR_00554c14 != 0) {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                ((PoolContext *)DAT_00586dc8)->main = p;
                Memory_InitializeAllocatorRegistries(p);
                break;
            case 4:
                ((PoolContext *)DAT_00586dc8)->second = p;
                break;
            }
        } else {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                ((PoolContext *)DAT_00586dc8)->main = p;
                Memory_InitializeAllocatorRegistries(p);
                break;
            case 4:
                ((PoolContext *)DAT_00586dc8)->second = p;
                p->prepare();
                if (DAT_00586fe0[0] != 0) { p->setName(DAT_00586fe0[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            case 5:
                p->prepare();
                if (DAT_00586fe8[0] != 0) { p->setName(DAT_00586fe8[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            case 6:
                p->prepare();
                if (DAT_00586ff0[0] != 0) { p->setName(DAT_00586ff0[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            }
        }
        i++;
        p->rc = p->rc + 1;
    } while (i < 46);
}


extern "C" void FUN_002f48c0(void) {

}


class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void v96(); };
extern "C" int FUN_002f0460(void *);
extern "C" int Memory_ShutdownAllocatorRegistries(void *);
extern "C" int thunk_free_2(void *);
extern int D_00587010[4];
extern "C" void FUN_002f48d0(char *arg0);
void FUN_002f48d0(char *arg0) {
    int i;
    V *obj;
    V ***pp;
    void *ent;

    while (D_00587010[0] > 1) {
        FUN_002f8760();
    }
    *(int *)((char *)DAT_00586dc8 + 52) = 0;
    i = 6;
    if (GPR_00554c14 == 0) {
        do {
            pp = (V ***)(arg0 + i * 0x90 + 20);
            obj = (V *)*pp;
            if (obj != 0) {
                FUN_002f0460(obj);
                obj->v96();
                thunk_free_2(obj);
                *pp = 0;
            }
            i--;
        } while (i > 0);
    }
    ent = *(void **)(arg0 + 20);
    Memory_ShutdownAllocatorRegistries(ent);
    while (D_00587010[0] > 0) {
        FUN_002f8760();
    }
    *(int *)((char *)DAT_00586dc8 + 48) = 0;
    thunk_free_2(ent);
}


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
extern int g_memoryContextNames[4];
/* IgMemoryPoolContextInfo slot 180: write the 46 original context names (Bootstrap, Default,
 * Current, NonTracked, ...) into the name field of each 144-byte context record. Each name is
 * copied with a 127-character limit and the 128th byte is cleared explicitly. Called by the
 * constructor and the destructor. strncpy is a strncpy-like bounded string copy (dest, source,
 * limit). */
extern "C" void igMemoryPoolContextInfo_InitializeRecordNames(igMemoryPoolContextInfo *self) {
    int index;
    ContextPrefixedRecord *entry;

    index = 0;
    do {
        entry = (ContextPrefixedRecord *)((char *)self + index * sizeof(ContextRecord2));
        strncpy(entry->record.name, g_memoryContextNames[index], CONTEXT_NAME_LIMIT);
        index += 1;
        entry->record.name[CONTEXT_NAME_LIMIT] = 0;
    } while (index < CONTEXT_RECORD_COUNT);
}


extern "C" int FUN_002cd990();
extern "C" int FUN_002cd9f0();
extern "C" int FUN_002cda50();
extern "C" void FUN_00307470(int, int, int *, int, int *, int, int);
extern "C" void FUN_00307550(int, int, int *, int, int *, int, int);
extern int DAT_004c2228[4];
extern int DAT_004c2368[4];
extern int DAT_004c2370[4];
extern int DAT_004fa400[4];
extern int DAT_004fa420[4];
extern int DAT_004fa440[4];
extern int DAT_004fa460[4];
extern int DAT_004fa490[4];
extern int DAT_004fa4c0[4];
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
    config = ((PoolConfigContext *)DAT_00586dc8)->config;
    mainPool = ((PoolConfigContext *)DAT_00586dc8)->main;
    second = ((PoolConfigContext *)DAT_00586dc8)->second;
    options = DAT_004c2370[0];
    mainSize = 0;
    nextSize = 0;
    optB = DAT_004c2368[0];
    optC = DAT_005871f8[0];
    {
    int f = self->flags;
    result = DAT_004fb410.v;
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
        if (o != 0 && igObject_IsKindOf(o, DAT_00586a88[0]) != 0) {
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
    if (GPR_00554c14 == 0) {
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
    if (o != mainPool && o != second) { ((PoolConfigContext *)DAT_00586dc8)->a88 = o; }
    o = self->poolFor(7);
    if (o != mainPool && o != second) { ((PoolConfigContext *)DAT_00586dc8)->a96 = o; }
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && o->inUse() == 0) { o->finish(); }
    }
    if (DAT_004c2370[0] & 8) {
        mainPool->lock(1);
        if (second != mainPool) { second->lock(1); }
    }
    if (result == DAT_004fb410.v) { self->setFlags(self->flags | 8); }
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
extern "C" void FUN_002f50e0(Mgr *arg0) {
    int s0;
    Sub *p;
    Cnt *c;
    arg0->f47();
    if ((void *)arg0 == DAT_00586fd0) {
        FUN_002f00f0(0);
    }
    arg0->f53();
    if (*(unsigned char *)((char *)DAT_00586dc8 + 119) != 0) {
        arg0->f64(0);
    }
    s0 = 45;
    do {
        p = *(Sub **)((char *)arg0 + s0 * 144 + 20);
        switch (s0) {
        case 0: case 4: case 5: case 6:
            break;
        default:
            if (p != 0) {
                arg0->f51(s0);
            }
        }
        s0--;
    } while (s0 >= 0);
    while (s0 >= 0) {
        p = *(Sub **)((char *)arg0 + s0 * 144 + 20);
        if (p != 0) {
            c = p->f20();
            c->count = c->count - 1;
        }
        s0--;
    }
}


extern int DAT_00585ea0[4];
extern "C" int FUN_002f5220(void) {
    return DAT_00585ea0[0];
}


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
extern "C" void FUN_002f5230(int *out, PoolDescSetup *self, int config, char *name) {
    int defaultSize;
    int systemSize;
    int scratchSize;
    int driverSize;
    char buf[256];
    int i;
    PoolDescRecord *rec;
    PoolDescSlot *slot;
    int ctxConfig;
    ctxConfig = ((PoolDescContext *)DAT_00586dc8)->config;
    slot = self->slots;
    if (self->table != 0) {
        FUN_002f8b20(self->table);
        releaseTable(self->table);
        self->table = 0;
    }
    {
        int alloc = (int)Memory_GetAllocatorBySelector(DAT_00587018[0]);
        releaseTable(self->table);
        self->table = (PoolDescTable *)FUN_002c01f0(alloc);
    }
    i = 0;
    do {
        rec = (PoolDescRecord *)FUN_002bfed0((int)Memory_GetAllocatorBySelector(DAT_00587018[0]));
        igNamedObject_SetName(rec, self->recordName(i));
        setDescString(&rec->alias, DAT_004c2170[i]);
        switch (i) {
        case 0:
            if (rec->s60 != 0 && *rec->s60 != 0) {
                strncpy(buf, rec->s60, 255);
                buf[255] = 0;
            } else {
                buf[0] = 0;
            }
            if (strstr(buf, DAT_004fa530) == 0 && strstr(buf, DAT_004fa550) == 0) {
                if (buf[0] != 0) {
                    __memcpy(buf, (void *)" | InhibitEventTracker", 23);
                } else {
                    strncpy(buf, DAT_004fa530, 255);
                }
                setDescString(&rec->s60, buf);
            }
            break;
        case 1:
            if (self == DAT_00586fd0) {
                defaultSize = 0;
                FUN_003065f0(config, 2, DAT_004fa580, &defaultSize, 0, 0);
                if (defaultSize > 0) {
                    rec->a28 = defaultSize;
                    char *n = DAT_00586de8;
                    if (n != 0) { setDescString(&rec->s40, n); }
                }
            }
            break;
        case 2:
            break;
        case 4:
            if (self == DAT_00586fd0) {
                systemSize = 0;
                FUN_003065f0(config, 2, DAT_004fa5a0, &systemSize, 0, 0);
                if (systemSize > 0) {
                    rec->a28 = systemSize;
                    char *n = DAT_00586de8;
                    if (n != 0) { setDescString(&rec->s40, n); }
                }
            }
            break;
        case 5:
        case 6:
            break;
        case 7:
            FUN_003065f0(ctxConfig, 2, DAT_004fa5c0, &scratchSize, 0, 0);
            FUN_003065f0(ctxConfig, 2, DAT_004fa5d0, &scratchSize, scratchSize, 0);
            if (scratchSize != 0) {
                if (scratchSize > 16384) { scratchSize = 16384; }
                rec->a36 = 0x70000000;
                rec->a28 = 16384;
                setDescString(&rec->s44, DAT_004fa5e8);
                setDescString(&rec->s48, DAT_004fa5f0);
                rec->a28 = scratchSize;
            } else {
                setDescString(&rec->s24, DAT_004c2170[1]);
            }
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, DAT_004fa600); }
            break;
        case 20:
            if (self == DAT_00586fd0) {
                driverSize = 0;
                FUN_003065f0(config, 2, DAT_004fa610, &driverSize, 0, 0);
                if (driverSize != 0) {
                    rec = self->slots[20].record;
                    rec->a28 = driverSize;
                } else {
                    setDescString(&rec->s24, DAT_004c2170[1]);
                }
            } else {
                setDescString(&rec->s24, DAT_004c2170[1]);
            }
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, DAT_004fa600); }
            break;
        default:
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, DAT_004fa600); }
            setDescString(&rec->s24, DAT_004c2170[1]);
            break;
        }
        FUN_002f8a80(self->table, rec);
        i++;
        slot->record = rec;
        slot++;
    } while (i < 30);
    if (config != 0 && name != 0 && *name != 0) {
        self->table->load(config, name);
    }
    *out = DAT_004fb410.v;
}


extern "C" void FUN_002f5c30(void *arg0);
struct Sub2 { char p[132]; int f132; };
struct Obj4 { char p0[4]; int refs; };
struct T { char p0[16]; Obj4 *f16; Sub2 f20; };
void FUN_002f5c30(void *arg0) {
    T *t = (T *)arg0;
    Sub2 *s;
    Obj4 *o;
    s = &t->f20;
    goto set;
back:
    if (t->f16 != 0) {
        FUN_002f8b20(t->f16);
        o = t->f16;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)(int)o->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        t->f16 = 0;
    }
    return;
set:
    s->f132 = 0;
    goto back;
}


extern "C" void FUN_002f5cc0(int *arg0) {
    *arg0 = DAT_004fb410.v;
}


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
extern int DAT_00587040[4];
extern char DAT_004fa2a8[], DAT_004fa2b0[], DAT_004fa5e8[], DAT_004fa5f0[], DAT_004fa600[], DAT_004fa620[], DAT_004fa630[], DAT_004fa638[], DAT_004fa640[], DAT_004fa648[], DAT_004fa658[], DAT_004fa668[], DAT_004fa678[], DAT_004fa680[], DAT_004fa688[], DAT_004fa690[], DAT_004fa698[];
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag) {
    MC *ctx = (MC *)arg1;
    R3 r0, r1, r2, r3, r4, r5, r6, r7;
    igMemoryPool *obj;
    int meta;
    Slot *slot;
    igMemoryPool *allocA;
    igMemoryPoolInfo *cfg;
    int al;
    int aligned;
    igMemoryPool *mbc;
    char *sub;
    igMemoryPool *allocB;
    igMemoryPool **pslot;
    bool owned;
    igMemoryPool *a;
    slot = &ctx->slots[idx];
    meta = DAT_00586a88[0];
    allocA = ctx->slots[0].obj;
    allocB = ctx->slots[1].obj;
    mbc = ctx->slots[3].obj;
    cfg = slot->cfg;
    owned = true;
    obj = slot->obj;
    if (allocA == 0) allocA = Memory_GetAllocatorBySelector(DAT_00587018[0]);
    if (allocB == 0) {
        allocB = Memory_GetAllocatorBySelector(DAT_00587020[0]);
        if (allocB == 0) allocB = allocA;
    }
    if (mbc == 0) Memory_GetAllocatorBySelector(DAT_00587030[0]);
    if (idx == 2) {
        slot->obj = allocB;
        allocB->_refCount = allocB->_refCount + 1;
    }
    if (cfg == 0) {
        if (idx >= 30) { *out = DAT_004fb410.v; return; }
        *out = DAT_004fb418.v;
        return;
    }
    if (cfg->_scope != 0) {
        slot->f140 = 0;
        if (strstr((char *)cfg->_scope, DAT_004fa620) == 0) {
            if (strstr((char *)cfg->_scope, DAT_004fa2a8) != 0) slot->f140 = slot->f140 | 1;
            else if (strstr((char *)cfg->_scope, DAT_004fa2b0) != 0) slot->f140 = slot->f140 | 2;
        }
        if (strstr((char *)cfg->_scope, DAT_004fa630) != 0) slot->f140 = slot->f140 | 0x01000000;
        if (strstr((char *)cfg->_scope, DAT_004fa638) != 0) slot->f140 = slot->f140 | 0x02000000;
        if (strstr((char *)cfg->_scope, DAT_004fa600) != 0) slot->f140 = slot->f140 | 0x04000000;
        if (flag == 0) {
            int f = slot->f140;
            if ((((unsigned long long)((long long)f << 0x28)) >> 0x28) != 0 && (f & 0x05000000) != 0) {
                *out = DAT_004fb410.v;
                return;
            }
        }
    }
    if (obj != 0) {
        int size = cfg->_size;
        if (size != 0 && (cfg->_arenaType == 0 || strcmp((char *)cfg->_arenaType, DAT_004fa640) == 0)) {
            r0 = ((OV *)obj)->v172(size);
        }
    } else {
        char *name = (char *)cfg->_aliasedTo;
        if (name != 0 && *name != 0) {
            int j = ctx->v116(name);
            obj = 0;
            if (j != -1) {
                Slot *o = (Slot *)((char *)(j * 144) + (int)ctx + 20);
                pslot = &o->obj;
                obj = o->obj;
                if (obj == 0) {
                    int rv = ctx->v204(j, flag).get();
                    if (rv != DAT_004fb410.v) { *out = DAT_004fb418.v; return; }
                    obj = *pslot;
                }
            }
            if (obj != 0) {
                int refMode = !!(ctx->flags & 4);
                if (refMode) {
                    if (cfg->_scope != 0) {
                        if ((strstr((char *)cfg->_scope, DAT_004fa600) != 0 || strstr((char *)cfg->_scope, DAT_004fa648) != 0 || strstr((char *)cfg->_scope, DAT_004fa658) != 0) && flag == 0) {
                            *out = DAT_004fb410.v;
                            return;
                        }
                    }
                    if (idx == 5) {
                        if (Memory_GetAllocatorBySelector(DAT_00587040[0]) == 0) ctx->slots[5].obj = allocA;
                    }
                    {
                        igMemoryPool *old = obj;
                        obj = igAliasMemoryPool_Create(allocA);
                        ((OV *)obj)->v400(old);
                    }
                    if (idx == 5 && ctx->slots[5].obj == allocA) ctx->slots[5].obj = 0;
                } else {
                    owned = false;
                }
                ctx->v100(idx, obj);
                if (owned) {
                    obj->_refCount = obj->_refCount - 1;
                    if (RC(obj) == 0) igObject_Destroy(obj);
                }
                if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
                *out = DAT_004fb410.v;
                return;
            }
        }
    {
        char *mname = (char *)cfg->_class;
        if (mname != 0 && *mname != 0) {
            int m = igObjectSystem_FindMetaByNameDefault(mname);
            meta = m;
            if (m == 0) meta = DAT_00586a88[0];
        }
    }
    {
        obj = igMetaObject_CreateInstance(meta, allocA);
        igMemoryPool *o2 = obj;
        int size = cfg->_size;
        al = size + (((Gl *)DAT_00587218[0])->v84() - 1);
        aligned = al & ~(((Gl *)DAT_00587218[0])->v84() - 1);
        if (size != 0) {
            char *kind = (char *)cfg->_arenaType;
            if (kind == 0 || strcmp(kind, DAT_004fa640) == 0) {
                r2 = ((OV *)o2)->v172(size);
            } else if (strcmp((char *)cfg->_arenaType, DAT_004fa5e8) == 0) {
                sub = (char *)cfg->_source;
                if (sub == 0 || *sub == 0) { a = allocB; goto common; }
                if (strcmp(sub, DAT_004fa668) == 0) {
b78:
                    int v = ((Gl *)DAT_00587218[0])->v68(0, aligned);
                    r3 = ((OV *)o2)->v96(v, aligned, 0);
                    slot->f136 = slot->f136 | 2;
                } else if (strcmp(sub, DAT_004fa678) == 0 || strcmp(sub, DAT_004fa680) == 0 || strcmp(sub, DAT_004fa688) == 0) {
                    goto b78;
                } else if (strcmp(sub, DAT_004fa5f0) == 0) {
                    int dfl = cfg->_address;
                    int a2;
                    if (dfl != 0) a2 = dfl;
                    else a2 = 0x70000000;
                    r4 = ((OV *)o2)->v96(a2, (long long)size, 0);
                } else if (strcmp(sub, DAT_004fa690) != 0 && strcmp(sub, DAT_004fa698) != 0) {
                    a = ctx->v96(sub);
                    if (a == 0) a = allocB;
common:
                    if (((OV *)a)->v132() == 0) ((OV *)a)->v120();
                    r5 = ((OV *)o2)->v96(((OV *)a)->v216(size), (long long)size, 1);
                    a->_refCount = a->_refCount + 1;
                    slot->f136 = slot->f136 | 1;
                }
            }
        }
        r6 = ((OV *)o2)->v180(cfg);
        ctx->v100(idx, o2);
        o2->_refCount = o2->_refCount - 1;
        if (RC(o2) == 0) igObject_Destroy(o2);
    }
    }
    if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
    *out = DAT_004fb410.v;
}


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
void MemoryContext_BuildAndAttachEventTracker(R4 *out, Ctx3 *self, int idx) {
    void *ty;
    Trk *trk;
    Obj5 *o2;
    igMemoryPoolInfo **ps2;
    Obj5 *o;
    int tv;
    igMemoryPoolInfo **ps;
    R4 t = self->v204(idx, 1); tv = t.v;
    int off = idx * 0x90; Slot2 *slot = (Slot2 *)(off + (int)self);
    trk = slot->trk;
    /* +12 of the context is igInfo::_directory in reflection but is read here as a flag word. The second flag test below stays on Ctx3::flags: typing both makes MWCC hoist the member address into a saved register. */
    int h1 = (((igMemoryPoolContextInfo *)self)->_directory & 1) != 0;
    if (h1) {
        ty = 0;
        ps = &slot->sub; igMemoryPoolInfo *sub = *ps;
        if (sub != 0) ty = (void *)sub->_releaseOptions;
        if (ty == 0 || strstr(ty, &DAT_004fa530[0]) == 0) {
            int h2 = (self->flags & 2) != 0;
            if ((h2 && idx != 1) || (ty != 0 && strstr(ty, &DAT_004fa550[0]) != 0)) {
                o = (Obj5 *)FUN_002c5780(self->v92(3));
                void *b = ((Gl2 *)DAT_00586dc8)->f124;
                void *f = (void *)(*ps)->_eventTrackerCapacity;
                if (f != 0) b = f;
                FUN_002dcc40(o, b);
                o->v92();
                trk->v360(o);
                ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
                if (RC2(o) == 0) igObject_Destroy(o);
            } else {
                void *x = self->v92(1)->v356();
                if (x != 0) trk->v360(x);
            }
        }
    } else {
        void *ty2 = 0;
        ps2 = &slot->sub; igMemoryPoolInfo *sub2 = *ps2;
        if (sub2 != 0) ty2 = (void *)sub2->_releaseOptions;
        if (ty2 != 0 && strstr(ty2, &DAT_004fa550[0]) != 0) {
            o2 = (Obj5 *)FUN_002c5780(self->v92(3));
            void *b2 = ((Gl2 *)DAT_00586dc8)->f124;
            void *f2 = (void *)(*ps2)->_eventTrackerCapacity;
            if (f2 != 0) b2 = f2;
            FUN_002dcc40(o2, b2);
            o2->v92();
            trk->v360(o2);
            ((igObject *)o2)->_refCount = ((igObject *)o2)->_refCount - 1;
            if (RC2(o2) == 0) igObject_Destroy(o2);
        }
    }
    out->v = tv;
}


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
void MemoryContext_RemoveAllocator(void *arg0, int arg1) {
    R4 sp6C, sp68, sp64;
    if (arg1 >= 0 && arg1 < 0x2E) {
        Obj6 *o = *(Obj6 **)((char *)arg0 + arg1 * 0x90 + 20);
        Slot3 *slot = (Slot3 *)((char *)arg0 + arg1 * 0x90 + 20);
        if (o != 0) {
            slot->obj = 0;
            if (RC(o) == 1) {
                if (((C188 *)o)->vX() != 0) {
                    ((C348 *)o)->vX(0);
                }
                ((C128 *)o)->vX();
                {
                    int fl = slot->flags;
                    if (fl & 1) {
                        int a;
                        slot->flags = fl & ~1;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            void *own;
                            sp6C = ((C96 *)o)->vX(0, 0, 0);
                            own = Memory_FindOwningAllocator(a);
                            if (own != 0) {
                                Obj6 *ob = (Obj6 *)own;
                                ob->_refCount = ob->_refCount - 1;
                                if (RC(ob) == 0) igObject_Destroy(ob);
                                Memory_FreeBuffer(a);
                            }
                        }
                    } else if (fl & 2) {
                        int a;
                        slot->flags = fl & ~2;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            long long b = (long long)((C144 *)o)->vX();
                            sp68 = ((C96 *)o)->vX(0, 0, 0);
                            sp64 = ((C72 *)DAT_00587218[0])->vX(a, b);
                        }
                    }
                }
            }
            o->_refCount = o->_refCount - 1;
            if (RC(o) == 0) igObject_Destroy(o);
            { Ctx4 *c = (Ctx4 *)arg0; if (arg1 == c->f8 + 1) c->f8 = arg1; }
        }
    }
}


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
extern "C" void FUN_002f69b0(PoolSetup *self) {
    /* matching construct: greedy declaration-order sweep — the locals' order sets the s-register choice */
    unsigned char trackEvents;
    unsigned char trackAll;
    unsigned char flag118;
    unsigned char flag117;
    unsigned char flag119;
    unsigned char flag120;
    unsigned char optionA;
    unsigned char optionB;
    char *stringA;
    char *stringB;
    char *stringC;
    char *stringD;
    char *stringF;
    int trackerSize;
    int value172;
    int value128;
    int value132;
    int value136;
    int value140;
    char *stringE;
    TrackedPool *mainPool;
    int alloc;
    PoolLoader *loader;
    LoadedObject *loaded;
    int config;
    int i;
    TrackedPool *secondPool;
    EventTracker *tracker;
    EventTracker *t;
    TrackedPool *pool;
    char *options;
    int j;
    TrackedPool *unitPool;
    char *unitOptions;
    EventTracker *unitTracker;
    config = ((MemoryContextState *)DAT_00586dc8)->config;
    mainPool = ((MemoryContextState *)DAT_00586dc8)->main;
    secondPool = ((MemoryContextState *)DAT_00586dc8)->second;
    alloc = FUN_002f00e0();
    int defaultTrackEvents = (self->flags & 1) != 0;
    trackEvents = defaultTrackEvents;
    trackAll = (self->flags & 2) != 0;
    stringA = 0;
    stringB = 0;
    stringC = 0;
    stringD = 0;
    stringF = 0;
    stringE = 0;
    FUN_00306e50(config, 2, DAT_004fa6a0, &trackEvents, defaultTrackEvents, 0);
    self->setFlags(trackEvents ? self->flags | 1 : self->flags & ~1);
    ((MemoryContextState *)DAT_00586dc8)->trackEvents = trackEvents;
    FUN_00306e50(config, 2, DAT_004fa6c0, &trackAll, trackAll, 0);
    self->setFlags(trackAll ? self->flags | 2 : self->flags & ~2);
    FUN_00306e50(config, 2, DAT_004fa6e0, &flag118, 0, 0);
    ((MemoryContextState *)DAT_00586dc8)->flag118 = flag118;
    FUN_00306e50(config, 2, DAT_004fa6f0, &flag119, 0, 0);
    ((MemoryContextState *)DAT_00586dc8)->flag119 = flag119;
    FUN_00306e50(config, 2, DAT_004fa710, &flag120, 0, 0);
    ((MemoryContextState *)DAT_00586dc8)->flag120 = flag120;
    FUN_003065f0(config, 2, DAT_004fa730, &trackerSize, 0x80000, 0);
    ((MemoryContextState *)DAT_00586dc8)->value124 = trackerSize;
    FUN_003065f0(config, 2, DAT_004fa750, &value128, -1, 0);
    ((MemoryContextState *)DAT_00586dc8)->value128 = value128;
    FUN_003065f0(config, 2, DAT_004fa770, &value132, -1, 0);
    ((MemoryContextState *)DAT_00586dc8)->value132 = value132;
    FUN_003065f0(config, 2, DAT_004fa790, &DAT_004c1eb0, DAT_004c1eb0, 0);
    FUN_003065f0(config, 2, DAT_004fa7b0, &value136, -1, 0);
    ((MemoryContextState *)DAT_00586dc8)->value136 = value136;
    FUN_003065f0(config, 2, DAT_004fa7e0, &value140, -1, 0);
    ((MemoryContextState *)DAT_00586dc8)->value140 = value140;
    FUN_00306910(config, 2, DAT_004fa810, &stringA, DAT_004f7910, 0);
    FUN_002d31d0((MemoryContextState *)DAT_00586dc8, stringA);
    FUN_00306910(config, 2, DAT_004fa830, &stringB, DAT_004f7910, 0);
    FUN_002d3240((MemoryContextState *)DAT_00586dc8, stringB);
    FUN_00306910(config, 2, DAT_004fa850, &stringC, DAT_004f7910, 0);
    FUN_002d32b0((MemoryContextState *)DAT_00586dc8, stringC);
    FUN_003065f0(config, 2, DAT_004fa870, &value172, -1, 0);
    FUN_002f0db0(value172);
    FUN_00306e50(config, 2, DAT_004fa890, &flag117, 0, 0);
    ((MemoryContextState *)DAT_00586dc8)->flag117 = flag117;
    FUN_00306910(config, 2, DAT_004fa8b0, &stringD, DAT_004f7910, 0);
    FUN_002d3320((MemoryContextState *)DAT_00586dc8, stringD);
    FUN_00306910(config, 2, DAT_004fa8d0, &stringE, DAT_004f7910, 0);
    FUN_002d3370((MemoryContextState *)DAT_00586dc8, stringE);
    FUN_00306910(config, 2, DAT_004fa8f0, &stringF, DAT_004f7910, 0);
    FUN_002d33c0((MemoryContextState *)DAT_00586dc8, stringF);
    if (stringF != 0 && *stringF != 0) {
        loader = FUN_002cec00(alloc);
        loaded = FUN_002b8500(alloc);
        if (loader != 0) {
            if (loader->load(stringF) == DAT_004fb410) {
                if (loader->attach(loaded, 1) == DAT_004fb418) {
                    loaded->rc.u.w = loaded->rc.u.w - 1;
                    if (loaded->rc.u.b.cnt == 0) igObject_Destroy(loaded);
                    loaded = 0;
                }
                optionA = 0;
                FUN_00306e50(config, 2, DAT_004fa900, &optionA, 0, 0);
                if (optionA != 0) { loader->optionA(); }
                optionB = 0;
                FUN_00306e50(config, 2, DAT_004fa918, &optionB, 0, 0);
                if (optionB != 0) { loader->optionB(); }
                loader->finish();
            }
            loader->rc.u.w = loader->rc.u.w - 1;
            if (loader->rc.u.b.cnt == 0) igObject_Destroy(loader);
        }
        ((MemoryContextState *)DAT_00586dc8)->loaded = loaded;
    }
    if (trackEvents != 0) {
        tracker = (EventTracker *)FUN_002c5780(alloc);
        FUN_002dcc40(tracker, trackerSize);
        tracker->start();
        tracker->users = tracker->users + 1;
        if (*stringE != 0) {
            if (secondPool != mainPool) {
                t = (EventTracker *)FUN_002c5780(alloc);
                FUN_002dcc40(t, 0x6000);
                t->start();
                secondPool->setTracker(t);
                t->rc.u.w = t->rc.u.w - 1;
                if (t->rc.u.b.cnt == 0) igObject_Destroy(t);
            }
        }
        for (i = 0; i < 46; i++) {
            if (i != 3) {
                pool = (TrackedPool *)self->slots[i].pool;
                options = 0;
                if (self->slots[i].record != 0) { options = self->slots[i].record->s60; }
                if (pool != 0 && pool->hasTracker() == 0 && (options == 0 || strstr(options, DAT_004fa530) == 0)) {
                    if ((trackAll != 0 && i != 1) || (options != 0 && strstr(options, DAT_004fa550) != 0)) {
                        t = (EventTracker *)FUN_002c5780(alloc);
                        FUN_002dcc40(t, trackerSizeFor(self->slots[i].record, trackerSize));
                        t->start();
                        pool->setTracker(t);
                        t->rc.u.w = t->rc.u.w - 1;
                        if (t->rc.u.b.cnt == 0) igObject_Destroy(t);
                    } else {
                        pool->setTracker(tracker);
                    }
                }
            }
        }
        tracker->users = tracker->users - 1;
        if ((int)tracker->rc.u.b.cnt > 1) {
            ((MemoryContextState *)DAT_00586dc8)->tracker = tracker;
        } else {
            tracker->rc.u.w = tracker->rc.u.w - 1;
            if (tracker->rc.u.b.cnt == 0) igObject_Destroy(tracker);
        }
    } else {
        for (j = 0; j < 46; j++) {
            if (j != 3) {
                unitPool = (TrackedPool *)self->slots[j].pool;
                unitOptions = 0;
                if (self->slots[j].record != 0) { unitOptions = self->slots[j].record->s60; }
                if (unitPool != 0 && unitPool->hasTracker() == 0 && unitOptions != 0 && strstr(unitOptions, DAT_004fa550) != 0) {
                    unitTracker = (EventTracker *)FUN_002c5780(alloc);
                    FUN_002dcc40(unitTracker, trackerSizeFor(self->slots[j].record, trackerSize));
                    unitTracker->start();
                    unitPool->setTracker(unitTracker);
                    unitTracker->rc.u.w = unitTracker->rc.u.w - 1;
                    if (unitTracker->rc.u.b.cnt == 0) igObject_Destroy(unitTracker);
                }
            }
        }
    }
    releaseString(stringE);
    releaseString(stringF);
    releaseString(stringD);
    releaseString(stringC);
    releaseString(stringB);
    releaseString(stringA);
}


extern "C" void FUN_002f7410(int arg0, int arg1) {
    strcmp(*(int *)((char *)(arg0) + 0), *(int *)((char *)(arg1) + 0));
}


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
extern "C" void FUN_002f7420(LeakReportSlot *self) {
    int sizeA;
    int sizeB;
    int sizeC;
    int sizeD;
    int total;
    int f;
    int g;
    int h;
    int i2;
    int j2;
    int k2;
    int l2;
    int m2;
    char line[140];
    int counts[32];
    char type[80];
    LeakReportTracker *tracker = ((LeakReportContext *)DAT_00586dc8)->tracker;
    int i;
    if (tracker != 0) {
        if (((LeakReportContext *)DAT_00586dc8)->dumpNames != 0) {
            int n;
            int names;
            int k;
            int it;
            int bytes;
            int *list;
            names = tracker->names;
            if (names != 0) {
                n = FUN_0030d080(names);
                bytes = n * 4;
                it = 0;
                list = FUN_002ee430(bytes);
                memset(list, 0, bytes);
                FUN_00304430(DAT_004fa930);
                FUN_00304680();
                for (k = 0; k < n; k++) {
                    if (it == -1) { break; }
                    list[k] = FUN_0030d1d0(names, it);
                    it = FUN_0030d4a0(names, it);
                }
                qsort(list, n, 4, (int (*)(const void *, const void *))FUN_002f7410);
                for (it = 0; it < n; it++) {
                    int name = list[it];
                    tracker->describe(0, -1, name, &sizeA, &sizeB, &sizeC, &sizeD);
                    sprintf(line, DAT_004fa988, name);
                    FUN_00304430(DAT_004fa990, line, sizeA, sizeB, sizeC, sizeD);
                    FUN_00304680();
                }
            }
        }
        if (((LeakReportContext *)DAT_00586dc8)->dumpSummary != 0) {
            total = 0; f = 0; g = 0; h = 0; i2 = 0; j2 = 0; k2 = 0; l2 = 0; m2 = 0;
            tracker->summary(0, -1, &total, counts, &f, &g, &h, &i2, &j2, &k2, &l2, 1, 1, &m2, 2, -1);
            for (LeakKind t = LeakKindFirst; t < LeakKindCount; t = (LeakKind)(t + 1)) {
                int *c = &counts[t];
                if (*c != 0) {
                    sprintf(type, DAT_004f95a0, FUN_002e1500(tracker, t));
                    FUN_00304430(DAT_004fa9b0, type, *c);
                    FUN_00304680();
                }
            }
            FUN_00304430(DAT_004fa9d0, total, f, g, h, i2, l2, m2, j2, k2);
            FUN_00304680();
        }
    }
    for (i = 0; i < 46; i++) {
        LeakReportPool *p = self[i].pool;
        if (p != 0) {
            int j;
            int seen;
            LeakReportOwner *o;
            o = p->owner();
            seen = 0;
            if (o != 0) {
                for (j = 0; j < i; j++) {
                    LeakReportPool *q = self[j].pool;
                    if (q != 0 && q->owner() == o) { seen = 1; break; }
                }
                if (o != 0 && seen == 0) {
                    if (((LeakReportContext *)DAT_00586dc8)->dumpLeaks != 0) {
                        if (o->count() > 0) { o->dump(); }
                    }
                    o->flush();
                }
            }
        }
    }
    {
        LeakReportTracker *t = ((LeakReportContext *)DAT_00586dc8)->tracker;
        if (t != 0) {
            t->rc = t->rc - 1;
            if (((unsigned long long)((long long)(int)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            ((LeakReportContext *)DAT_00586dc8)->tracker = 0;
        }
    }
    for (int k = 0; k < 46; k++) {
        LeakReportPool *p = self[k].pool;
        if (p != 0 && p->owner() != 0) { p->release(0); }
    }
}


extern "C" int FUN_002dcc50(void *);
extern char DAT_004fab08[];
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual R v176(char *); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual VB * v356(); };
extern "C" void FUN_002f78b0(VA *arg0);
void FUN_002f78b0(VA *arg0) {
    char sp70[256];

    int s4;
    int s3;
    int s2;
    VB *s1;
    bool s0;

    VB *t;
    R r;
    s4 = 0;
    s0 = false;
    do {
        t = *(VB **)((char *)arg0 + s4 * 144 + 20);
        if (t != 0) {
            s1 = (VB *)t->v356();
            s2 = 0;
            if (s1 != 0) {
                s3 = 0;
                while (s3 < s4) {
                    t = *(VB **)((char *)arg0 + s3 * 144 + 20);
                    if (t != 0 && t->v356() == s1) {
                        s2 = 1;
                        break;
                    }
                    s3 += 1;
                }
                if (s2 == 0 && s1 != 0) {
                    sp70[255] = 0;
                    if (!s0) {
                        if (s4 == 0 || s4 == 1) {
                            strncpy(sp70, (char *)DAT_00586dc8 + 528, 255);
                            s0 = true;
                        } else {
                            goto b16;
                        }
                    } else {
b16:
                        if (s4 == 4) {
                            strncpy(sp70, (char *)DAT_00586dc8 + 656, 255);
                        } else {
                            sp70[0] = 0;
                        }
                    }
                    if (sp70[0] == 0) {
                        sprintf(sp70, DAT_004fab08, arg0->v104(s4));
                    }
                    if (FUN_002dcc50(s1) != 0) {
                        r = s1->v176(sp70);
                    }
                }
            }
        }
        s4 += 1;
    } while (s4 < 46);
}


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
extern "C" igResult FUN_002f7a70(SlotPool *self, unsigned int kind, int free) {
    int i;
    PoolSlotEntry *e;
    igResult r;
    unsigned int flags;
    i = 0;
    e = (PoolSlotEntry *)((char *)self + 20);
    r = DAT_004fb410;
    do {
        flags = e->flags;
        if ((flags & 0xFBFFFFFF) != 0 && (flags & 0xFFFFFF) == kind) {
            if (free != 0) {
                if (e->owner != 0) {
                    if (flags & 0x02000000) {
                        e->owner->vDrop();
                    }
                    if (e->flags & 0x01000000) {
                        self->vFree(i);
                    }
                }
            } else if (flags & 0x01000000) {
                if (self->vRelease(i, 1) == DAT_004fb418) {
                    r = DAT_004fb418;
                }
            }
        }
        i++;
        e++;
    } while (i < 46);
    return r;
}


class DW4VC_356_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int vX(); };
struct Ent { char pad[20]; DW4VC_356_0 *obj; char pad2[120]; };
extern "C" void FUN_002f7bc0(Ent *arg0, int arg1);
void FUN_002f7bc0(Ent *arg0, int arg1) {
    int i, j, found, id;
    DW4VC_356_0 *o;
    for (i = 0; i < 46; i++) {
        o = arg0[i].obj;
        if (o != 0) {
            id = o->vX();
            found = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    DW4VC_356_0 *o2 = arg0[j].obj;
                    if (o2 != 0) {
                        int r2 = o2->vX();
                        if (r2 == id) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found == 0 && id != 0) {
                    FUN_002dcc60(id, arg1);
                }
            }
        }
    }
}


struct E2 { char pad[20]; DW4VC_356_0 *f20; char pad2[120]; };
extern "C" void FUN_002f7cc0(E2 *arg0, int arg1, int *arg2, int arg3);
void FUN_002f7cc0(E2 *arg0, int arg1, int *arg2, int arg3) {
    /* matching construct: variant search — decl order [8, 7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int w;
    DW4VC_356_0 *temp_a0_2;
    DW4VC_356_0 *temp_a0;
    int *var_s5;
    int var_s4;
    int var_s3;
    int var_s2;
    int var_s1;
    int temp_v0;

    var_s5 = arg2;
    var_s4 = arg3;
    for (var_s3 = 0; var_s3 < 0x2E; var_s3++) {
        temp_a0 = arg0[var_s3].f20;
        if (temp_a0 == 0) { continue; }
        temp_v0 = temp_a0->vX();
        var_s1 = 0;
        if (temp_v0 == 0) { continue; }
        for (var_s2 = 0; var_s2 < var_s3; var_s2++) {
            temp_a0_2 = arg0[var_s2].f20;
            if (temp_a0_2 != 0) {
                w = temp_a0_2->vX();
                if (w == temp_v0) { var_s1 = 1; break; }
            }
        }
        if (var_s1 == 0 && temp_v0 != 0) {
            if (var_s4 <= 0) { return; }
            *var_s5 = temp_v0 + 0x2328;
            var_s4 -= 1;
            var_s5 += 1;
            FUN_002dcc60(temp_v0, arg1);
        }
    }
}


extern "C" void FUN_002f7e00(E2 *arg0, int *arg1, int arg2);
void FUN_002f7e00(E2 *arg0, int *arg1, int arg2) {
    /* matching construct: variant search — decl order [8, 7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int w;
    DW4VC_356_0 *temp_a0_2;
    DW4VC_356_0 *temp_a0;
    int *var_s5;
    int var_s4;
    int var_s3;
    int var_s2;
    int var_s1;
    int temp_v0;

    var_s5 = arg1;
    var_s4 = arg2;
    for (var_s3 = 0; var_s3 < 0x2E; var_s3++) {
        temp_a0 = arg0[var_s3].f20;
        if (temp_a0 == 0) { continue; }
        temp_v0 = temp_a0->vX();
        var_s1 = 0;
        if (temp_v0 == 0) { continue; }
        for (var_s2 = 0; var_s2 < var_s3; var_s2++) {
            temp_a0_2 = arg0[var_s2].f20;
            if (temp_a0_2 != 0) {
                w = temp_a0_2->vX();
                if (w == temp_v0) { var_s1 = 1; break; }
            }
        }
        if (var_s1 == 0 && temp_v0 != 0) {
            if (var_s4 <= 0) { return; }
            FUN_002dcc60(temp_v0, *var_s5);
            var_s5 += 1;
            var_s4 -= 1;
        }
    }
}


extern "C" void FUN_002f7f20(int arg0, int arg1);
void FUN_002f7f20(int arg0, int arg1) {
    /* matching construct: variant search — decl order [6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void **temp_a0_2;
    void **temp_a0;
    int var_s3;
    int var_s2;
    int w;
    int var_s1;
    int temp_v0;

    var_s3 = 0;
    do {
        temp_a0 = (void **)(*(int *)((char *)((arg0 + (var_s3 * 0x90))) + 20));
        if (temp_a0 != 0) {
            temp_v0 = ((DW4VC_356_0 *)(temp_a0))->vX();
            var_s1 = 0;
            if (temp_v0 != 0) {
                var_s2 = 0;
                while (var_s2 < var_s3) {
                    temp_a0_2 = (void **)(*(int *)((char *)((arg0 + (var_s2 * 0x90))) + 20));
                    if (temp_a0_2 != 0) {
                        w = ((DW4VC_356_0 *)(temp_a0_2))->vX();
                        if (w == temp_v0) {
                            var_s1 = 1;
                            break;
                        }
                    }
                    var_s2 += 1;
                }
                if ((var_s1 == 0) && (temp_v0 != 0)) {
                    FUN_002dcd70(temp_v0, arg1);
                }
            }
        }
        var_s3 += 1;
    } while (var_s3 < 0x2E);
}


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
extern "C" void FUN_002f8020(Slot4 *slots, int arg1, int *out, int n) {
    int i;
    int j;
    int found;
    int id;
    for (i = 0; i < 46; i++) {
        Obj7 *o = slots[i].obj;
        if (o != 0 && (id = o->vid(), found = 0, id != 0)) {
            for (j = 0; j < i; j++) {
                Obj7 *o2 = slots[j].obj;
                int k;
                if (o2 != 0 && (k = o2->vid(), k == id)) {
                    found = 1;
                    break;
                }
            }
            if (found == 0 && id != 0) {
                if (n <= 0) {
                    return;
                }
                *out = id + 0x242C;
                n--;
                out++;
                FUN_002dcd70(id, arg1);
            }
        }
    }
}


class V2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int vX(); };
struct Slot5 { char p[20]; V2 *f20; char p2[0x90 - 24]; };
/* The comma expression pins the operand order of the duplicate test. */
extern "C" void FUN_002f8160(Slot5 *arg0, int *arg1, int arg2) {
    int i;
    int j;
    int dup;
    int id;
    for (i = 0; i < 46; i++) {
        V2 *o = arg0[i].f20;
        if (o != 0) {
            id = o->vX();
            dup = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    V2 *o2 = arg0[j].f20;
                    int r;
                    if (o2 != 0 && (r = o2->vX(), r == id)) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0 && id != 0) {
                    if (arg2 > 0) {
                        FUN_002dcd70(id, *arg1);
                        arg1 += 1;
                        arg2--;
                    } else {
                        break;
                    }
                }
            }
        }
    }
}


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
void FUN_002f8280(Slot6 *arg0, int arg1, int arg2, int arg3) {
    int sp[40];
    int i;
    int j;
    int found;
    Res *r;
    Dev *d;
    for (i = 0; i < 46; i++) {
        d = arg0[i].dev;
        if (d != 0) {
            r = d->getRes();
            found = 0;
            if (r != 0) {
                for (j = 0; j < i; j++) {
                    Dev *e = arg0[j].dev;
                    if (e != 0 && e->getRes() == r) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && r != 0 && ((r->flags & 0x2000) ? 1 : 0) && ((r->mask & (1 << arg1)) ? 1 : 0)) {
                    FUN_002e2250(sp, arg1, arg2, arg3, 0, 0, 0, 0, 0, 0);
                    r->v24(sp, -1);
                    FUN_002e2300(sp, -1);
                }
            }
        }
    }
}


extern char DAT_004fab10[], DAT_004fab20[], DAT_004f90b0[], DAT_004fab30[];
class VB2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void * v88(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void v348(int); };
struct Z { int w[7]; int f28; };
extern "C" void FUN_002f8420(VA *arg0, char *arg1, VB2 *arg2);
void FUN_002f8420(VA *arg0, char *arg1, VB2 *arg2) {
    int s2, s1, s0;
    Z *s6;
    s1 = 0;
    s0 = -1;
    if (arg1 == 0) {
        arg1 = DAT_004fab10;
    }
    s2 = 0;
    do {
        if (arg2 == *(VB2 **)((char *)arg0 + s2 * 144 + 20)) {
            s6 = (Z *)arg2->v88();
            FUN_00304430(DAT_004fab20, arg1, arg0->v104(s2), s6->f28);
            FUN_00304680();
            s1 += 1;
            if (s1 == 1) {
                s0 = s2;
            }
        }
        s2 += 1;
    } while (s2 < 46);
    if (s1 == 0) {
        FUN_00304430(DAT_004f90b0, arg1);
        FUN_00304680();
    }
    arg2->v348(0);
    if (s0 != -1) {
        FUN_00304430(DAT_004fab30, DAT_004c2170[s0], s0);
        FUN_00304680();
    }
}


extern "C" int FUN_002f0a60(...);
extern int DAT_004f95c8[4];
extern int DAT_004fab70[4];
extern int DAT_004fab90[4];
struct E3 { char p[20]; int f20; char q[120]; };
extern "C" void FUN_002f8580(E3 *arg0, int *arg1);
class DW4VC_144_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
class DW4VC_260_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual int vX(int, int); };
void FUN_002f8580(E3 *arg0, int *arg1) {
    int *var_a1;
    int temp_a2;
    int j;
    int i;
    int found;
    var_a1 = arg1;
    if (var_a1 == 0) {
        var_a1 = (int *)(&DAT_004fab70[0]);
    }
    FUN_00304430(var_a1, var_a1);
    FUN_00304680();
    i = 0;
    do {
        temp_a2 = arg0[i].f20;
        found = 0;
        if (temp_a2 != 0) {
            for (j = 0; j < i; j++) {
                int w = arg0[j].f20;
                if (w == temp_a2) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                ((DW4VC_260_2 *)(arg0))->vX((int)(0), (int)(temp_a2));
            }
        }
        i += 1;
    } while (i < 0x2E);
    FUN_00304430(&DAT_004f95c8[0]);
    FUN_00304680();
    FUN_002f0a60(&DAT_004fab90[0]);
    ((DW4VC_144_0 *)((void **)DAT_00587218[0]))->vX();
}


extern int DAT_00586ffc[4];
extern "C" int Memory_GetCurrentContext(void) {
    if ((DAT_00587010[0] > 0) && (DAT_00587010[0] < 4)) {
        return DAT_00586ffc[DAT_00587010[0]];
    }
    if ((DAT_00587010[0] == 0) && (DAT_00586fd0 != 0)) {
        return (int)DAT_00586fd0;
    }
    return 0;
}


extern "C" igResult FUN_002f86e0(void *arg1) {

    if ((arg1 != 0) && (DAT_00587010[0] >= 0) && (DAT_00587010[0] < 4)) {
        DAT_00587000[DAT_00587010[0]] = arg1;
        DAT_00587010[0] += 1;
        *(int *)((char *)(arg1) + 4) = (int)((int) (*(int *)((char *)(arg1) + 4) + 1));
        return DAT_004fb410;
    } else {
        return DAT_004fb418;
    }
}


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
extern "C" struct ContextStackEntry *FUN_002f8760(void) {
    int n;
    struct ContextStackEntry *s;
    if (DAT_00587010[0] > 0 && DAT_00587010[0] < 5) {
        n = DAT_00587010[0] - 1;
        DAT_00587010[0] = n;
        s = (struct ContextStackEntry *)DAT_00587000[n];
        if (s != 0) {
            s->u.w = s->u.w - 1;
            if (s->u.b.cnt == 0) igObject_Destroy(s);
        }
        return s;
    }
    return 0;
}


extern "C" int malloc(...);
extern "C" int igObject_AllocateRawStorageDefault(...);
extern "C" void FUN_002f87f0(int arg0) {
    if (*(unsigned char *)DAT_00586dc8 != 0) {
        igObject_AllocateRawStorageDefault(arg0, 0);
        return;
    }
    malloc();
}


extern unsigned char *g_objectSystem[4];
extern "C" void free(void *allocation);
extern "C" void thunk_FUN_002ed460__002ff810(void *allocation);
/* Releases an allocation owned by a pool context. While the object system is active (flag byte at
 * the start of the record behind g_objectSystem) the call goes to Memory_FreeBuffer through its
 * j-thunk; otherwise it takes the early-boot path free. Neither callee's argument is
 * touched here: `allocation` is passed straight through in the first argument register. */
/* Object-system record pointer; byte 0 is the "object system active" flag. */
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *allocation) {
    if (*g_objectSystem[0] != 0) {
        thunk_FUN_002ed460__002ff810(allocation);
        return;
    }
    free(allocation);
}



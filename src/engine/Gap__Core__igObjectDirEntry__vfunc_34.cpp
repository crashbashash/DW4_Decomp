#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" {
int Gap__Core__igObject__vfunc_10(...);
int igObject_IsKindOf(void *object, int meta);
void ObjectList_ResizeRetained(void *list, int count);
void ObjectList_AppendRetained(void *list, void *object);
int FUN_002eb010(...);
void *StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
int igObject_WritePersistentFields(int, int, void *, int, unsigned char);
int FUN_002fe600(...);
int igObject_GetSerializedSize(...);
int igObject_RegisterInstance(...);
int FUN_002fff90(int, int, void *, int, unsigned char);
int FUN_00300250(int, int, void *, int, unsigned char);
extern int DAT_00585b60[4];
extern char DAT_004e0858[];
extern int DAT_004f6518[4];
extern void *DAT_00586f20[4];
/* The array extern keeps the load absolute. */
extern int g_igObjectDirEntry_metaObject[4];
}

/* ABI dispatch view of virtual slot 92 (21 leading virtuals); never instantiated. */
class DirEntryRefSetterView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int SetRef(int);
};

/* Drop the entry's object reference: virtual slot 92 (vfunc_23) is the setter of _ref (+24) that
 * retains the new value and releases the old one, so calling it with 0 releases the held object;
 * the igObject default of this slot (an empty stub) then runs. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self);

struct MetaInfo { char pad0[12]; int index; };
class DirEntryView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual MetaInfo *getMeta();
};
struct EntryList : public igObjectList {
    igObjectDirEntry *at(int index) const { return ((igObjectDirEntry *const *)_data)[index]; }
    void set(int index, igObject *object) {
        if (object != 0) object->_refCount = object->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igObject **)_data)[index] = object;
        }
    }
};
struct DirFile { char pad0[92]; EntryList *sharedEntries; char pad96[184]; int pool; };
extern "C" EntryList *FUN_002bd680(int pool);
static inline const char *nameOf(const igObjectDirEntry *entry) {
    return entry->_name != 0 ? (const char *)entry->_name : DAT_004e0858;
}
static inline EntryList *asEntryList(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00585b60[0]) != 0) return (EntryList *)object;
    return 0;
}

extern "C" igObjectDirEntry *Gap__Core__igObjectDirEntry__vfunc_26(igObjectDirEntry *self, DirFile *file);

extern "C" int Gap__Core__igObjectDirEntry__vfunc_22(void);

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_27(igObjectDirEntry *self, igObject *object);

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_28(igObjectDirEntry *self, igObject *object);

struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: string-pool header lives at s-8 (chunk) / s-4 (refcount); not a reflected class */
struct SRel { static inline void go(char *s) {
    if (s) {
        int *a1 = (int *)(s - 8);
        int v = *(int *)(s - 4) - 1;
        *(int *)(s - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
} };
struct Pool { static inline void *get() {
    if (DAT_00586f20[0] == 0) {
        void *p = (void *)FUN_002eb010(16);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
} };
extern "C" void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1);
void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1);

/* slot 23 of igObjectDirEntry: set the _ref reference (+24; reflected as a raw ref, but the code
 * treats it as a counted igObject). Reference-counted assignment: retain the new object, release
 * the old one (destroying it when its 23-bit count reaches zero), then store the new one. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_23(igObjectDirEntry *self, igObject *object);

class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_40(igObjectDirEntry *arg0, void *arg1);

struct DW4RT { char pad[64]; int (*fn)(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual DW4RT *vX(); };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_38(void *arg0);

struct S; struct A;
struct R { char p[64]; void *(*f64)(); };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual R * vX(); };

struct S { char p[24]; V *f24; char q[20]; int f48; };
struct A { char p[144]; int f144; int f148; char q[40]; int f192; };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_39(S *arg0, A *arg1);

extern "C" void Gap__Core__igObjectDirEntry__vfunc_36(igObjectDirEntry *arg0, int arg1);

class igObjectSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void vfunc_15();
};
class igObjectDirEntryView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igObjectSlots *_ref;
};

extern "C" void Gap__Core__igObjectDirEntry__vfunc_37(igObjectDirEntryView *self);

extern "C" void Gap__Core__igObjectDirEntry__vfunc_33(igObjectDirEntry *arg0, void *arg1);

extern "C" void Gap__Core__igObjectDirEntry__vfunc_34(igObjectDirEntry *arg0, void *arg1) {
    int temp_s0;
    temp_s0 = arg0->_ref;
    temp_s0 = FUN_00300250(temp_s0, ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX(), arg1, *(int *)((char *)(arg1) + 192), *(unsigned char *)((char *)(arg1) + 168));
    int r = ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX();
    ((DW4VC_104_1 *)(((char *)(arg1) + 0)))->vX(r + temp_s0);
}

typedef struct DirEntryCounted { char pad[4]; int _refCount; } DirEntryCounted;
typedef struct DirEntryMetaList { char pad[16]; DirEntryCounted **data; } DirEntryMetaList;
typedef struct DirEntryFileView { char pad[192]; DirEntryMetaList *metas; char pad2[80]; char failed; char pad3[11]; int pool; } DirEntryFileView;
typedef struct DirEntrySelf { char pad[12]; int index; char pad2[12]; DirEntryCounted *typeMeta; int typeMetaName; char pad3[8]; int pool; int typeMetaIndex; } DirEntrySelf;
extern "C" {
int FUN_002d7da0(DirEntryFileView *, int, DirEntryCounted *);
int Memory_GetAllocatorBySelector(int);
DirEntryCounted *igMetaObject_CreateInstanceWithPool(DirEntryCounted *, int);
DirEntryCounted *igObjectSystem_FindMetaByNameDefault(int);
}
static inline void addRef(DirEntryCounted *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }
static inline void dropRef(DirEntryCounted *o) {
    o->_refCount = o->_refCount - 1;
    if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
}
static inline void setMeta(DirEntrySelf *self, DirEntryCounted *m) {
    DirEntryCounted *old;
    addRef(m);
    old = self->typeMeta;
    if (old != 0) { dropRef(old); }
    self->typeMeta = m;
}
extern "C" void Gap__Core__igObjectDirEntry__vfunc_31(DirEntrySelf *self, DirEntryFileView *file);

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_24(igObjectDirEntry *self, igObject *object);

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_25(igObjectDirEntry *self, igObject *object);

/* igObjectDirEntry vtable slot 29: setter for `_memoryPoolHandle` (+44), the pool handle field of
 * the directory entry. Slot 30 is the matching getter; igMemoryDirEntry has the same pair. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_29(igObjectDirEntry *self, int memoryPoolHandle);

/* IgObjectDirEntry vtable slot 30, a plain getter that returns the reflected field
 * _memoryPoolHandle (+44). */
extern "C" int Gap__Core__igObjectDirEntry__vfunc_30(igObjectDirEntry *self);

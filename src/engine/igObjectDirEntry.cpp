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
extern "C" void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self) {
    ((DirEntryRefSetterView *)self)->SetRef((int)(0));
    Gap__Core__igObject__vfunc_10(self);
}

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

extern "C" igObjectDirEntry *Gap__Core__igObjectDirEntry__vfunc_26(igObjectDirEntry *self, DirFile *file) {
    igSmartPointer<EntryList> lists(file->sharedEntries, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((DirEntryView *)self)->getMeta()->index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained(lists.p, index + 1);
        lists->set(index, 0);
    }
    igSmartPointer<EntryList> entries(asEntryList(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->pool;
        entries.release();
        entries.p = FUN_002bd680(pool);
        lists->set(index, entries.p);
    }
    int i;
    EntryList *list;
    igObjectDirEntry *entry;
    int count;
    count = entries->_count;
    self->_index = -1;
    list = entries.p;
    for (i = 0; i < count; i++) {
        entry = ((igObjectDirEntry **)list->_data)[i];
        if (entry->_typeMeta == self->_typeMeta && nameOf(entry) == nameOf(self) &&
            entry->_memoryPoolHandle == self->_memoryPoolHandle) {
            return list->at(i);
        }
    }
    ObjectList_AppendRetained(list, self);
    return self;
}

extern "C" int Gap__Core__igObjectDirEntry__vfunc_22(void) {
    return g_igObjectDirEntry_metaObject[0];
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_27(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_28(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

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
void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1) {
    char *s0;
    if (arg1) {
        arg1->_refCount++;
    }
    /* matching construct: _typeMeta/_typeMetaName are 4-byte reference fields (int); cast to the typed pointer */
    Rel::go((igObject *)arg0->_typeMeta);
    arg0->_typeMeta = (int)arg1;
    if (arg1) {
        char *name = (char *)arg1->_name;
        void *pool = Pool::get();
        s0 = StringPool_Intern(pool, name);
        SRel::go((char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    } else {
        void *pool = Pool::get();
        s0 = StringPool_Intern(pool, DAT_004f6518);
        SRel::go((char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    }
}

/* slot 23 of igObjectDirEntry: set the _ref reference (+24; reflected as a raw ref, but the code
 * treats it as a counted igObject). Reference-counted assignment: retain the new object, release
 * the old one (destroying it when its 23-bit count reaches zero), then store the new one. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_23(igObjectDirEntry *self, igObject *object) {
    igObject *previousObject;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    previousObject = (igObject *)(self->_ref);
    if (previousObject != 0) {
        previousObject->_refCount = previousObject->_refCount - 1;
        if ((previousObject->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousObject);
        }
    }
    self->_ref = (int)object;
}

class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_40(igObjectDirEntry *arg0, void *arg1) {
    int temp_v0;

    temp_v0 = ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX();
    ((DW4VC_104_1 *)(((char *)(arg1) + 0)))->vX((int)(temp_v0 + igObject_WritePersistentFields(arg0->_ref, temp_v0, arg1, *(int *)((char *)(arg1) + 192), *(unsigned char *)((char *)(arg1) + 168))));
}

struct DW4RT { char pad[64]; int (*fn)(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual DW4RT *vX(); };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_38(void *arg0) {
    DW4VC_88_0 *a = *(DW4VC_88_0 **)((char *)arg0 + 24);
    if (a != 0) {
        int (*f)() = a->vX()->fn;
        if (f != 0) {
            FUN_00301590((igObjectDirEntry *)arg0, (igMetaObject *)f());
        }
    }
}

struct S; struct A;
struct R { char p[64]; void *(*f64)(); };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual R * vX(); };

struct S { char p[24]; V *f24; char q[20]; int f48; };
struct A { char p[144]; int f144; int f148; char q[40]; int f192; };
extern "C" void Gap__Core__igObjectDirEntry__vfunc_39(S *arg0, A *arg1) {
    int temp_s0_2;
    void *(*temp_v1)();
    V *temp_s0;
    void *var_v0;

    temp_s0 = arg0->f24;
    R *r = temp_s0->vX();
    var_v0 = r;
    temp_v1 = r->f64;
    if (temp_v1 != 0) {
        var_v0 = temp_v1();
    }
    arg0->f48 = FUN_002fe600(arg1->f192, var_v0);
    temp_s0_2 = arg1->f148;
    arg1->f148 = temp_s0_2 + igObject_GetSerializedSize(temp_s0);
    arg1->f144 = arg1->f144 + 1;
}

extern "C" void Gap__Core__igObjectDirEntry__vfunc_36(igObjectDirEntry *arg0, int arg1) {
    int temp_a0;

    temp_a0 = arg0->_ref;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            igObject_RegisterInstance(temp_a0, arg0->_typeMeta);
            return;
        }
        igObject_RegisterInstance(temp_a0, 0);
    }
}

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

extern "C" void Gap__Core__igObjectDirEntry__vfunc_37(igObjectDirEntryView *self)
{
    self->_ref->vfunc_15();
}

extern "C" void Gap__Core__igObjectDirEntry__vfunc_33(igObjectDirEntry *arg0, void *arg1) {
    int temp_s0;
    int temp_s0_2;

    temp_s0 = arg0->_ref;
    temp_s0_2 = FUN_002fff90(temp_s0, ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX(), arg1, *(int *)((char *)(arg1) + 192), *(unsigned char *)((char *)(arg1) + 168));
    int t3 = ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX();
    ((DW4VC_104_1 *)(((char *)(arg1) + 0)))->vX(t3 + temp_s0_2);
}

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
extern "C" void Gap__Core__igObjectDirEntry__vfunc_31(DirEntrySelf *self, DirEntryFileView *file) {
    int index;
    DirEntryCounted *m;
    DirEntryCounted *obj;
    int pool;
    int sel;
    index = self->typeMetaIndex;
    if (index == -1) {
        setMeta(self, igObjectSystem_FindMetaByNameDefault(self->typeMetaName));
    } else {
        setMeta(self, file->metas->data[index]);
    }
    if (self->typeMeta != 0) {
        sel = self->pool;
        if (sel == -1 || sel == 1 || sel == 2) {
            pool = file->pool;
        } else {
            pool = Memory_GetAllocatorBySelector(sel);
            if (pool == 0) {
                pool = file->pool;
            }
        }
        obj = igMetaObject_CreateInstanceWithPool(self->typeMeta, pool);
        if (obj == 0) {
            file->failed = 1;
            FUN_002d7da0(file, self->index, 0);
            return;
        }
        FUN_002d7da0(file, self->index, obj);
        dropRef(obj);
    } else {
        FUN_002d7da0(file, self->index, 0);
    }
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_24(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_25(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

/* igObjectDirEntry vtable slot 29: setter for `_memoryPoolHandle` (+44), the pool handle field of
 * the directory entry. Slot 30 is the matching getter; igMemoryDirEntry has the same pair. */
extern "C" void Gap__Core__igObjectDirEntry__vfunc_29(igObjectDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}

/* IgObjectDirEntry vtable slot 30, a plain getter that returns the reflected field
 * _memoryPoolHandle (+44). */
extern "C" int Gap__Core__igObjectDirEntry__vfunc_30(igObjectDirEntry *self) {
    return self->_memoryPoolHandle;
}

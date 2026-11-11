#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"

struct R12 { int a; };
class VO12 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual R12 v96(); virtual int v100(); };
struct Lst12 { int w0; int w4; int count; int w12; int *data; };
struct Obj12 { int w[6]; Lst12 *list; int w28; int f32; int w36[8]; VO12 *vo; };

typedef struct L7c50 { char pad0[8]; int n; char pad1[4]; unsigned *data; } L7c50;
typedef struct O7c50 { char pad[44]; L7c50 *l; } O7c50;

class VC92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
class VC96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };
struct L7da0 { char pad[8]; int cnt; char pad2[4]; int *arr; };
struct A7da0 { char pad[16]; VC92 **arr; char pad2[20]; int f40; struct L7da0 *l; };

class VC7e90 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };

struct FieldBindMeta;
class FieldBindObject : public igVirtualObject { public:
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual FieldBindMeta *GetMeta();
    virtual void Assign(void *value);

};
struct FieldBindSlotList : public igObject { int count; int capacity; FieldBindObject **data; };
struct FieldBindSet : public igObject { int count; int pad12; FieldBindObject **targets; char pad20[24]; FieldBindSlotList *overrides; };
struct FieldBindItem { int pad0; int pad4; int offset; char pad12[12]; FieldBindObject *source; };

extern "C" int List_RemoveWordAt(void *, int);
struct RemovableList : igTDataList<igObject *> {
    void removeAt(int index) {
        igObject *o = _data[index];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(this, index);
        _data[_count] = 0;
    }
};
struct RemovableListHolder { char pad[28]; RemovableList *list; };

class O83b0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vf(int, int); int a; int b; int c; unsigned char flag; };
struct Lst83b0 { int pad0; int pad1; int count; int pad3; O83b0 **data; };
struct T83b0 { char pad[28]; Lst83b0 *list; };

struct R8460 : public igObject { };

class VC8520 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int v172(int); };
struct Ent8520;
struct Lst8520 { int pad0; int pad1; int count; int pad3; Ent8520 **data; };
struct Ctx8520 { char pad[24]; Lst8520 *list; };

typedef struct A86b0 { char p[8]; int n; } A86b0;
typedef struct K86b0 { char p[8]; int f8; } K86b0;

struct FieldLinkInfo;
class FieldLinkObject : public igVirtualObject { public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual void Prepare();
    virtual void s14(); virtual void s15();
    virtual void Touch();
    virtual void SetPool(int pool);
    virtual void s18(); virtual void s19();
    virtual FieldLinkInfo *GetMeta();
    virtual void Assign(void *value);
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void SetContext(int mode);
    virtual void s28();
    virtual int Classify(void *pool);
};
struct FieldLinkInfo { char pad[64]; int (*poolFor)(); };
struct FieldLinkRecord : FieldLinkObject { int pad8; int index; int user; int extra; };
struct FieldLinkSet : public igObject { int count; char pad12[44]; char reset; char pad57[7]; unsigned char mode; unsigned char tracks; unsigned char namedPools; };

struct Ctx8a80 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual int v29(int); };
struct E8a80 : public igVirtualObject { virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(int); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(int); int p8; int idx; int f16; int f20; int p24; int f28; char p32[12]; int f44; int p48; char f52; };
struct L8a80 { char p0[8]; int count; char p12[53]; unsigned char f65; unsigned char f66; };

class R8d00 : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); int f8; int f12; int f16; int f20; };
struct Lst8d00 { char pad[8]; int n; };

struct P8eb0 { int pad[6]; int val; };

class Tgt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void v80(void *);  };
struct Sub { char pad[60]; int w60; };
struct Elem { char pad[24]; Tgt *t; Sub *s; };
struct Coll { char pad[8]; unsigned n; char pad2[44]; unsigned char done; };

typedef struct A8fe0 { char pad[20]; int *f20; } A8fe0;

struct Item { int pad[6]; int f24; };
struct Obj25 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();  virtual void vcall(int); int pad[7]; int key; int idx; };
struct Cont { int pad[2]; int count; };

struct SR { int w0; };
class A9130 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual SR vX(int); };
class B9130 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual SR vX(); };

struct RefCountResult { int w0; RefCountResult() {} RefCountResult(const RefCountResult &o) { w0 = o.w0; } };
class RefCountLock { public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual RefCountResult Unlock();
    virtual void s30();
    virtual RefCountResult Acquire(int wait);
};
struct RefCountedHandle;
typedef igTDataList<RefCountedHandle *> RefCountOwnerList;
struct RefCountOwnerHolder { char pad[16]; RefCountOwnerList *list; };
struct RefCountedHandle { int _vtable; unsigned int _refCount; char pad8[24]; RefCountOwnerHolder *holder; char pad36[16]; int refs; char pad56[12]; RefCountLock *lock; };

struct ConfigureResult { int value; };
struct Driver {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20();
    virtual ConfigureResult configure();
    int references;
};
struct DriverOwner { char pad[68]; Driver *driver; };
struct DriverType {};

extern "C" {
int StringList_AppendRetained(int, void **);
int Gap__Core__igObject__vfunc_09();
void FUN_002d78e0(void *arg0, int arg1);
void Gap__Core__igDirEntry__vfunc_27(void);
void Gap__Core__igDirEntry__vfunc_28(void);
int Gap__Core__igDirEntry__vfunc_26(int arg0);
int Gap__Core__igDirEntry__vfunc_42(void);
void Gap__Core__igDirEntry__vfunc_29(void);
int Gap__Core__igDirEntry__vfunc_30(void);
void Gap__Core__igDirEntry__vfunc_41(void);
void Gap__Core__igDirEntry__vfunc_40(void);
void Gap__Core__igDirEntry__vfunc_38(void);
void Gap__Core__igDirEntry__vfunc_39(void);
void Gap__Core__igDirEntry__vfunc_35(void);
void Gap__Core__igDirEntry__vfunc_36(void);
void Gap__Core__igDirEntry__vfunc_37(void);
void Gap__Core__igDirEntry__vfunc_33(void);
void Gap__Core__igDirEntry__vfunc_34(void);
void Gap__Core__igDirEntry__vfunc_32(void);
void Gap__Core__igDirEntry__vfunc_31(void);
void Gap__Core__igDirEntry__vfunc_11(int arg0);
void Gap__Core__igDirEntry__vfunc_23(void *arg0, int arg1);
void Gap__Core__igDirEntry__vfunc_24(void);
void Gap__Core__igDirEntry__vfunc_25(void);
int igResource_GetMetaObject();
int igObjectDirEntry_GetMetaObject();
int igMemoryDirEntry_GetMetaObject();
int igInfo_GetMetaObject();
int igExternalInfoEntry_GetMetaObject();
int igExternalIndexedEntry_GetMetaObject();
int igExternalDirEntry_GetMetaObject();
int igDirEntry_GetMetaObject();
int FUN_00309750(int, int);
int Gap__Core__igObject__vfunc_10(Obj12 *);
int igProperty_FindBySortedKey(O7c50 *, int, unsigned);
void *igProperty_FindByName(int, int, int);
int ObjectList_AppendRetained(...);
int igObject_IsKindOf(void *, int);
int igMetaObject_GetFieldCount(FieldBindMeta *);
FieldBindItem *igMetaObject_GetFieldAt(FieldBindMeta *, int);
void igObjectRefMetaField_Assign(FieldBindItem *, igVirtualObject *, void *);
int igNamedObject_SetName(...);
int igObject_VisitFields(...);
void *igObject_GetAllocator(void *);
FieldLinkRecord *FUN_002bd8f0(void *);
void List_InsertWords(void *, int, int, void *);
char *igMetaObject_GetPoolName(FieldLinkInfo *);
void *Memory_GetAllocatorByName(char *);
FieldLinkObject *Memory_GetCurrentContextAlias(void);
void FUN_00301590(FieldLinkRecord *, FieldLinkInfo *);
int FUN_002cc2c0();
int FUN_00301000(L8a80 *);
E8a80 *FUN_002c0d80(int);
void FUN_002eed00(E8a80 *, int);
int Memory_GetBufferSize(int);
int FUN_002fb8d0(int);
int FUN_002f8920(int);
int FUN_002f04f0(int);
Ctx8a80 *FUN_002f88d0();
void *FUN_002c77e0(...);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
Driver *FUN_002ba650(int);
extern int DAT_00586730[4];
extern int DAT_00585b70[4];
extern int DAT_00585b20;
extern int DAT_00586140;
extern int DAT_00585be0[4];
extern int DAT_00586710[4];
extern int DAT_00586f20[4];
extern int DAT_004fb410[4];

void FUN_002d7b00(void);
void Gap__Core__igDirectory__vfunc_12(Obj12 *arg0);
int FUN_002d7c50(O7c50 *arg0, unsigned key);
void *thunk_FUN_002d7e90(int *arg0, int arg1);
int FUN_002d7d60(void *arg0, int arg1);
void FUN_002d7da0(A7da0 *a, int i, int x);
void *FUN_002d7e90(int *arg0, int arg1);
int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value);
void FUN_002d81f0(void *arg0, int arg1);
void FUN_002d8230(RemovableListHolder *h, igObject *object);
void FUN_002d8310(void *arg0, void *arg1);
void igDirectory_FindInfoByName(int *arg0, int arg1);
int FUN_002d8370(void *arg0, int arg1);
int FUN_002d83b0(T83b0 *arg0, int arg1, int arg2);
int FUN_002d8460(void *dir, unsigned key);
int FUN_002d8520(int arg0, VC8520 *arg1, Ctx8520 *arg2);
int FUN_002d8620(int arg0, int arg1, int arg2);
int FUN_002d86b0(A86b0 *arg0, K86b0 *arg1, unsigned arg2);
int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user);
int FUN_002d8a80(L8a80 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7);
int FUN_002d8d00(Lst8d00 *list, int key, int name, int val);
int Gap__Core__igDirEntry__vfunc_22(void);
int FUN_002d8e70(int arg0, int arg1);
int FUN_002d8eb0(int arg0, int arg1);
void *FUN_002d8f10(int arg0, int arg1);
void FUN_002d8f20(Coll *arg0);
void FUN_002d8fe0(A8fe0 *arg0, int arg1);
int Gap__Core__igDirectory__vfunc_25(Cont *c, Obj25 *o);
int FUN_002d9120(void *arg0);
int FUN_002d9130(int *arg0);
int FUN_002d91c0(RefCountedHandle *self);
void FUN_002d9330(DriverOwner *owner);
}

void FUN_002d78e0(void *arg0, int arg1) {
    void *sp3C;
    int *temp_a1;
    int temp_v1;
    int var_v0_2;
    void *var_v0;

    if (arg1 == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], arg1));
    }
    sp3C = (void *)(var_v0);
    StringList_AppendRetained(*(int *)((char *)(arg0) + 20), &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v1 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
}

void Gap__Core__igDirEntry__vfunc_27(void) {

}

void Gap__Core__igDirEntry__vfunc_28(void) {

}

int Gap__Core__igDirEntry__vfunc_26(int arg0) {
    return arg0;
}

int Gap__Core__igDirEntry__vfunc_42(void) {
    return 0;
}

void Gap__Core__igDirEntry__vfunc_29(void) {

}

int Gap__Core__igDirEntry__vfunc_30(void) {
    return -1;
}

void Gap__Core__igDirEntry__vfunc_41(void) {

}

void Gap__Core__igDirEntry__vfunc_40(void) {

}

void Gap__Core__igDirEntry__vfunc_38(void) {

}

void Gap__Core__igDirEntry__vfunc_39(void) {

}

void Gap__Core__igDirEntry__vfunc_35(void) {

}

void Gap__Core__igDirEntry__vfunc_36(void) {

}

void Gap__Core__igDirEntry__vfunc_37(void) {

}

void Gap__Core__igDirEntry__vfunc_33(void) {

}

void Gap__Core__igDirEntry__vfunc_34(void) {

}

void Gap__Core__igDirEntry__vfunc_32(void) {

}

void Gap__Core__igDirEntry__vfunc_31(void) {

}

void Gap__Core__igDirEntry__vfunc_11(int arg0) {
    Gap__Core__igObject__vfunc_09();
    igNamedObject_SetName(arg0, 0);
}

void Gap__Core__igDirEntry__vfunc_23(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}

void Gap__Core__igDirEntry__vfunc_24(void) {

}

void Gap__Core__igDirEntry__vfunc_25(void) {

}

void FUN_002d7b00(void) {
    igDirEntry_GetMetaObject();
    igObjectDirEntry_GetMetaObject();
    igMemoryDirEntry_GetMetaObject();
    igExternalDirEntry_GetMetaObject();
    igExternalIndexedEntry_GetMetaObject();
    igExternalInfoEntry_GetMetaObject();
    igInfo_GetMetaObject();
    igResource_GetMetaObject();
}

void Gap__Core__igDirectory__vfunc_12(Obj12 *arg0) {
    R12 sp4C;
    int temp_s2;
    int i;
    int *temp_v0;
    Lst12 *l;

    if (arg0->f32 != 0) {
        for (i = 0; i < arg0->list->count; i++) {
            FUN_00309750(arg0->f32, ((int *)arg0->list->data[i])[5]);
        }
    }
    temp_s2 = FUN_002d9120(arg0);
    for (i = 0; i < temp_s2; i++) {
        temp_v0 = (int *)FUN_002d8370(arg0, i);
        if (temp_v0[3] == (int)arg0) {
            temp_v0[3] = 0;
        }
    }
    Gap__Core__igObject__vfunc_10(arg0);
    if (arg0->vo != 0 && arg0->vo->v100() != 0) {
        sp4C = arg0->vo->v96();
    }
}

int FUN_002d7c50(O7c50 *arg0, unsigned key) {
    L7c50 *l = arg0->l;
    int lo, hi, mid, idx, n;
    unsigned v;
    int r;
    if (l != 0) {
        n = l->n;
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            v = l->data[mid];
            if (v < key) {
                lo = mid + 1;
            } else if (key < v) {
                hi = mid - 1;
            } else {
                idx = mid;
                goto found;
            }
        }
        if (n == 0) {
            idx = -1;
        } else {
            v = l->data[lo];
            if (key < v || v < key) {
                idx = -1;
            } else {
                idx = lo;
            }
        }
found:
        v = l->data[idx];
        if (v == key) {
            return (int)FUN_002d7e90((int *)arg0, idx);
        }
        return 0;
    }
    return igProperty_FindBySortedKey(arg0, DAT_00586730[0], key);
}

void *thunk_FUN_002d7e90(int *arg0, int arg1)
{
    return FUN_002d7e90(arg0, arg1);
}

int FUN_002d7d60(void *arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 44));
    if (temp_v0 != 0) {
        return *(int *)(*(int *)((char *)(temp_v0) + 16) + (arg1 * 4));
    }
    return *(int *)((char *)((*(int *)(*(int *)((char *)(arg0) + 16) + (arg1 * 4)))) + 24);
}

void FUN_002d7da0(A7da0 *a, int i, int x) {
    if (a->l != 0 && a->f40 != 0) {
        VC92 *o = a->arr[i];
        o->vX(x);
        ((VC96 *)o)->vX(x);
        {
            struct L7da0 *l = a->l;
            if (l->cnt != 0 && i >= 0 && i < l->cnt) l->arr[i] = x;
        }
    } else {
        a->arr[i]->vX(x);
    }
}

void *FUN_002d7e90(int *arg0, int arg1) {
    if (arg0[11] != 0) {
        VC7e90 *t = (VC7e90 *)((int *)arg0[4])[arg1];
        t->vX(FUN_002d7d60(arg0, arg1));
        ((int *)t)[3] = arg1;
        return t;
    }
    return (void *)((int *)arg0[4])[arg1];
}

static inline void releaseBound(FieldBindObject *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline FieldBindItem *castBinding(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00585b70[0]) != 0) {
        return o;
    }
    return 0;
}
static inline FieldBindItem *castRefField(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00585b20) != 0) {
        return o;
    }
    return 0;
}
static inline void setSlot(FieldBindSlotList *l, int i, FieldBindObject *v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = (FieldBindObject *)v;
    }
}

int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value) {
    int changed = 0;
    int i;
    int j;
    int n;
    FieldBindObject *current;
    FieldBindItem *item;
    for (i = 0; i < self->count; i++) {
        current = *field;
        if ((FieldBindObject *)FUN_002d7d60(self, i) == (FieldBindObject *)current) {
            if (self->overrides != 0) {
                releaseBound(*field);
                if (*value != 0) {
                    (*value)->_refCount = (*value)->_refCount + 1;
                }
                setSlot(self->overrides, i, *value);
            } else {
                self->targets[i]->Assign(*value);
            }
            changed++;
        }
        item = castBinding((FieldBindItem *)FUN_002d7e90((int *)self, i));
        if (item != 0) {
            igSmartPointer<igVirtualObject> source(item->source, kRetainReference);
            if (source.get() == 0) {
                continue;
            }
            n = igMetaObject_GetFieldCount(((FieldBindObject *)source.get())->GetMeta());
            for (j = 0; j < n; j++) {
                FieldBindItem *f;
                f = castRefField(igMetaObject_GetFieldAt(((FieldBindObject *)source.get())->GetMeta(), j));
                if (f != 0) {
                    if (*(FieldBindObject **)((char *)source.get() + f->offset) == *field) {
                        igObjectRefMetaField_Assign(f, source.get(), *value);
                        changed++;
                    }
                }
            }
        }
    }
    return changed;
}

void FUN_002d81f0(void *arg0, int arg1) {
    FUN_002d8230((RemovableListHolder *)arg0, (igObject *)igProperty_FindByName(*(int *)((char *)arg0 + 28), *(int *)0x585BE0, arg1));
}

void FUN_002d8230(RemovableListHolder *h, igObject *object) {
    int idx;
    RemovableList *f;
    f = h->list;
    idx = f->find(object);
    if (-1 < idx) {
        h->list->removeAt(idx);
    }
}

void FUN_002d8310(void *arg0, void *arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 28));
    *(int *)((char *)(arg1) + 12) = (int)(arg0);
}

void igDirectory_FindInfoByName(int *arg0, int arg1) {
    igProperty_FindByName(arg0[7], DAT_00585be0[0], arg1);
}

/* The lower bound is spelled `arg1 <= -1` so it fuses into slti at. */
int FUN_002d8370(void *arg0, int arg1) {
    void *temp_a0;
    if (!(arg1 <= -1)) {
        temp_a0 = (void *)(*(int *)((char *)(arg0) + 28));
        if (arg1 < *(int *)((char *)(temp_a0) + 8)) {
            return *(int *)(*(int *)((char *)(temp_a0) + 16) + (arg1 * 4));
        }
    }
    return 0;
}

int FUN_002d83b0(T83b0 *arg0, int arg1, int arg2) {
    int i;
    O83b0 *o;

    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->data[i];
        if (o->flag == 1 && (o->vf(arg1, arg2) & 0xFF) == 1) {
            return 1;
        }
    }
    return 0;
}

int FUN_002d8460(void *dir, unsigned key) {
    igSmartPointer<R8460> h((R8460 *)FUN_002d7c50((O7c50 *)dir, key), kRetainReference);
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}

int FUN_002d8520(int arg0, VC8520 *arg1, Ctx8520 *arg2) {
    int i;
    int n;
    if (arg0 == 0) {
        return 1;
    }
    if (arg1 != 0) {
        return arg1->v172(arg0) == -1;
    }
    if ((FUN_002d8460(arg2, arg0) & 0xFF) == 1) {
        return 1;
    }
    n = arg2->list->count;
    for (i = 0; i < n; i++) {
        if ((FUN_002d83b0((T83b0 *)arg2->list->data[i], (int)arg2, arg0) & 0xFF) == 1) {
            return 1;
        }
    }
    FUN_002d87b0((FieldLinkSet *)arg2, (FieldLinkObject *)arg0, 0, 0);
    return 0;
}

int FUN_002d8620(int arg0, int arg1, int arg2) {
    int temp_v0;

    if (arg1 != 0) {
        igObject_VisitFields(arg1, &FUN_002d8520, arg0);
        temp_v0 = FUN_002d86b0((A86b0 *)arg0, (K86b0 *)DAT_00586730[0], arg1);
        igNamedObject_SetName(FUN_002d7e90((int *)arg0, temp_v0), arg2);
        return temp_v0;
    }
    return -1;
}

int FUN_002d86b0(A86b0 *arg0, K86b0 *arg1, unsigned arg2) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned v;
    if (arg1 == 0) return -1;
    n = arg0->n;
    hi = n - 1;
    if (n <= 0) return 0;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        v = *(unsigned *)((char *)FUN_002d7e90((int *)arg0, mid) + arg1->f8);
        if (v < arg2) {
            lo = mid + 1;
        } else if (arg2 < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    v = *(unsigned *)((char *)FUN_002d7e90((int *)arg0, lo) + arg1->f8);
    if (v < arg2) lo++;
    return lo;
}

template <class T> struct RetainedWord {
    T *p;
    RetainedWord(T *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};

int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user) {
    int index = 0;
    FieldLinkInfo *info;
    void *pool;
    int mode;
    if (obj == 0) {
        return -1;
    }
    if (self->count > 0) {
        index = FUN_002d86b0((A86b0 *)self, (K86b0 *)DAT_00586730[0], (unsigned)obj);
        if (self->count > index && (FieldLinkObject *)FUN_002d7d60(self, index) == obj) {
            return -1;
        }
    }
    if (obj != 0) {
        obj->Touch();
        if (igObject_IsKindOf(self, DAT_00586140) != 0) {
            if (self->mode == 1) {
                obj->Prepare();
            }
            {
                FieldLinkInfo *m = obj->GetMeta();
                int (*fn)() = m->poolFor;
                if (fn != 0) {
                    self->reset = 0;
                    obj->SetPool(fn());
                }
            }
        }
    }
    igSmartPointer<FieldLinkRecord> record(FUN_002bd8f0(igObject_GetAllocator(self)));
    record.get()->index = index;
    RetainedWord<FieldLinkRecord> inserted(record.get());
    List_InsertWords(self, index, 1, &inserted);
    if (name != 0) {
        igNamedObject_SetName(record.get(), name);
    }
    record.get()->user = user;
    record.get()->extra = 0;
    record.get()->Assign(obj);
    if (self->tracks != 0) {
        info = obj->GetMeta();
        pool = 0;
        if (self->namedPools != 0 && info != 0 && igMetaObject_GetPoolName(info) != 0) {
            pool = Memory_GetAllocatorByName(igMetaObject_GetPoolName(info));
        }
        if (pool == 0) {
            pool = igObject_GetAllocator(obj);
        }
        if (pool != 0) {
            mode = Memory_GetCurrentContextAlias()->Classify(pool);
            if (mode == 1 || mode == 2) {
                mode = -1;
            }
            record.get()->SetContext(mode);
        }
    }
    if (obj != 0) {
        FUN_00301590(record.get(), obj->GetMeta());
    }
    return index;
}

int FUN_002d8a80(L8a80 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7) {
    int s0;
    int s0b;
    int v;
    if (arg2 == 0) return -1;
    s0 = 0;
    if (arg0->count > 0) {
        s0 = FUN_002d86b0((A86b0 *)arg0, (K86b0 *)DAT_00586730[0], arg2);
        if (s0 < arg0->count) { int r = FUN_002d7d60(arg0, s0); if (r == arg2) return -1; }
    }
    if (arg3 == 0) arg3 = FUN_002cc2c0();
    igSmartPointer<E8a80> record(FUN_002c0d80(FUN_00301000(arg0)));
    record.get()->idx = s0;
    RetainedWord<E8a80> inserted(record.get());
    List_InsertWords(arg0, s0, 1, &inserted);
    if (arg5) igNamedObject_SetName(record.get(), arg5);
    record.get()->f16 = arg6;
    record.get()->f20 = 1;
    FUN_002eed00(record.get(), arg3);
    int size = Memory_GetBufferSize(arg2);
    record.get()->f28 = size;
    record.get()->f44 = arg4;
    record.get()->v21(arg2);
    record.get()->f52 = arg7;
    if (arg0->f65) {
        s0b = 0;
        if (arg0->f66 && arg1 && FUN_002fb8d0(arg1)) s0b = FUN_002f8920(FUN_002fb8d0(arg1));
        if (s0b == 0) s0b = FUN_002f04f0(arg2);
        if (s0b) {
            v = FUN_002f88d0()->v29(s0b);
            if (v == 1 || v == 2) v = -1;
            record.get()->v27(v);
        }
    }
    return record.get()->idx;
}

struct Retained {
    R8d00 *p;
    Retained(R8d00 *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};
int FUN_002d8d00(Lst8d00 *list, int key, int name, int val) {
    int idx, cnt;
    if (key == 0) {
        return -1;
    }
    idx = FUN_002d86b0((A86b0 *)list, (K86b0 *)DAT_00586730[0], key);
    cnt = list->n;
    if (cnt > 0) {
        if (idx < cnt) {
            int f = FUN_002d7d60(list, idx);
            if (f == key) return -1;
        }
    }
    igSmartPointer<R8d00> entry((R8d00 *)FUN_002c77e0(igObject_GetAllocator(list)));
    igNamedObject_SetName(entry.get(), name);
    entry.get()->f16 = val;
    entry.get()->f20 = 2;
    entry.get()->vX(key);
    entry.get()->f12 = idx;
    Retained retained(entry.get());
    List_InsertWords(list, idx, 1, &retained);
    return entry.get()->f12;
}

int Gap__Core__igDirEntry__vfunc_22(void) {
    return DAT_00586710[0];
}

int FUN_002d8e70(int arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(igProperty_FindByName(arg0, DAT_00585be0[0], arg1));
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 24);
}

int FUN_002d8eb0(int arg0, int arg1) {
    struct P8eb0 *s0;
    s0 = (struct P8eb0 *)igProperty_FindByName(arg0, DAT_00585be0[0], arg1); if (s0 == 0) return 0; if (igObject_IsKindOf(s0, DAT_00585b70[0]) != 0) return s0->val; return 0;
}

void *FUN_002d8f10(int arg0, int arg1) {
    return igProperty_FindByName(arg0, DAT_00585be0[0], arg1);
}

void FUN_002d8f20(Coll *arg0) {
    unsigned n;
    unsigned i;
    Elem *e;
    if (arg0->done != 1) {
        n = arg0->n;
        i = 0;
        while (i < n) {
            e = (Elem *)FUN_002d7e90((int *)arg0, i);
            if (e != 0 && igObject_IsKindOf(e, DAT_00585b70[0]) != 0) {
                if (e->s != 0 && e->s->w60 != 0) {
                    e->t->v80(e->s);
                }
            }
            i++;
        }
        arg0->done = 1;
    }
}

void FUN_002d8fe0(A8fe0 *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(DAT_00586f20[0], arg1);
    temp_a0 = arg0->f20;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->f20 = temp_s0;
}

int Gap__Core__igDirectory__vfunc_25(Cont *c, Obj25 *o) {
if (o->key != 0) { Item *it = (Item *)FUN_002d8f10((int)c, o->key); if (it) { o->vcall(it->f24); return 1; } } else { int i = o->idx; int n = c->count; if (i >= 0 && i < n) { Item *it = (Item *)FUN_002d7e90((int *)c, i); o->vcall(it->f24); return 1; } } return 0;
}

int FUN_002d9120(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 28)) + 8);
}

int FUN_002d9130(int *arg0) {
    SR a;
    SR b;
    int v;

    if (arg0[17] == 0) {
        v = arg0[13] + 1;
        arg0[13] = v;
        return v;
    }
    a = ((A9130 *)arg0[17])->vX(1);
    v = arg0[13];
    if (a.w0 == DAT_004fb410[0]) {
        v += 1;
        arg0[13] = v;
        b = ((B9130 *)arg0[17])->vX();
    }
    return v;
}

int FUN_002d91c0(RefCountedHandle *self) {
    int left;
    if (self->lock == 0) {
        left = self->refs - 1;
        self->refs = left;
    } else {
        self->lock->Acquire(1);
        left = self->refs - 1;
        self->refs = left;
    }
    if (left <= 0) {
        if (self->lock != 0) {
            self->lock->Unlock();
        }
        if (self->holder != 0) {
            RefCountOwnerList *list = self->holder->list;
            int index = list->find(self);
            RefCountedHandle *o = list->_data[index];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(list, index);
            list->_data[list->_count] = 0;
        }
    } else {
        if (self->lock != 0) {
            self->lock->Unlock();
        }
    }
    return left;
}

static inline Driver *recreateDriver(DriverOwner *owner, DriverType) {
    Driver *old = owner->driver;
    if (old != 0) {
        old->references = old->references - 1;
        if ((old->references & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    owner->driver = FUN_002ba650(0);
    return owner->driver;
}
void FUN_002d9330(DriverOwner *owner) {
    if (owner->driver == 0) {
        recreateDriver(owner, DriverType())->configure();
    }
}

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" void igMetaObject_RunStaticInit(...);
struct Rc;
extern "C" void FUN_00239390(void);
extern "C" unsigned char g_CollisionLibrary_registered;
extern "C" void CollisionLibrary_MarkRegistered(void);
extern "C" igMetaObject *g_igCreateCollisionDatabase_metaObject[4];
extern "C" igMetaObject *igCreateCollisionDatabase_GetMetaObject(void);
struct W { int *vt; int f[19]; };
extern "C" int igObject_InitHeader(...);
extern "C" int FUN_0019c840(...);
extern "C" int FUN_00225790(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int DAT_0052d130[4];
extern "C" void * DAT_00586dc8[4];
extern "C" int igCreateCollisionDatabase_GetVTable(void);
extern "C" int FUN_00100610(void *);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_00239530(O *arg0, short arg1);
extern "C" void FUN_002395b0(void);
extern "C" char igOptBase_GetPublishedMetaObject[];
extern "C" char igOptBase_Register[];
extern "C" char g_igCreateCollisionDatabase_callbackList[];
extern "C" char igCreateCollisionDatabase_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igCreateCollisionDatabase_Register(void);
extern "C" void thunk_igCreateCollisionDatabase_GetMetaObject(void);
extern "C" int FUN_002be610(...);
extern "C" int FUN_002ea4b0(...);
extern "C" int FUN_00303460(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_00498300[4];
extern "C" int DAT_00498320[4];
extern "C" int DAT_00498340[4];
extern "C" int DAT_00498360[4];
extern "C" int DAT_0056dc88[4];
extern "C" void igCreateCollisionDatabase_InitFields(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" Rc *FUN_002397a0(int arg0);
extern "C" igMetaObject *g_igCollisionInfo_metaObject[4];
extern "C" igMetaObject *igCollisionInfo_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int DAT_00524950[4];
extern "C" int DAT_0052d4d0[4];
union U { int vt; char b[32]; };
extern "C" int igCollisionInfo_GetVTable(void);
extern "C" void FUN_00239910(void);
extern "C" char igInfo_GetPublishedMetaObject[];
extern "C" char igInfo_Register[];
extern "C" char g_igCollisionInfo_callbackList[];
extern "C" char igCollisionInfo_className[];
extern "C" void igCollisionInfo_Register(void);
extern "C" void thunk_igCollisionInfo_GetMetaObject(void);
extern "C" int DAT_00498388[4];
extern "C" int DAT_00498390[4];
extern "C" int DAT_00498398[4];
extern "C" int DAT_004983a0[4];
extern "C" int DAT_0056dcc8[4];
extern "C" void igCollisionInfo_InitFields(void);
extern "C" int igMetaObject_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int DAT_0056dcd8[4];
extern "C" int DAT_00587040[4];
extern "C" int FUN_00239a40(void);
extern "C" igMetaObject *g_igCollisionGroupList_metaObject[4];
extern "C" igMetaObject *igCollisionGroupList_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int DAT_0052d460[4];
extern "C" int igCollisionGroupList_GetVTable(void);
extern "C" void FUN_00239b20(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igCollisionGroupList_callbackList[];
extern "C" char igCollisionGroupList_className[];
extern "C" void igCollisionGroupList_Register(void);
extern "C" void thunk_igCollisionGroupList_GetMetaObject(void);
extern "C" igMetaObject *g_igCollisionGroup_metaObject[4];
extern "C" igMetaObject *igCollisionGroup_GetMetaObject(void);
extern "C" int FUN_001a7580(...);
extern "C" int FUN_00195a90(...);
extern "C" int DAT_0052d3c0[4];
union U_239c00 { int vt; char b[96]; };
extern "C" int igCollisionGroup_GetVTable(void);
extern "C" void FUN_00239c80(void);
extern "C" char igGroup_GetPublishedMetaObject[];
extern "C" char igGroup_Register[];
extern "C" char g_igCollisionGroup_callbackList[];
extern "C" char igCollisionGroup_className[];
extern "C" void igCollisionGroup_Register(void);
extern "C" void thunk_igCollisionGroup_GetMetaObject(void);
extern "C" int FUN_00196190(...);
extern "C" int DAT_004983c0[4];
extern "C" int DAT_004983e0[4];
extern "C" int DAT_00498400[4];
extern "C" int DAT_00498420[4];
extern "C" int DAT_0056dce0[4];
extern "C" void igCollisionGroup_InitFields(void);
extern "C" igMetaObject *g_igCollisionGridHelper_metaObject[4];
extern "C" igMetaObject *igCollisionGridHelper_GetMetaObject(void);
union U_239e00 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int DAT_0052d360[4];
extern "C" int igCollisionGridHelper_GetVTable(void);
extern "C" void FUN_00239ee0(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igCollisionGridHelper_callbackList[];
extern "C" char igCollisionGridHelper_className[];
extern "C" void igCollisionGridHelper_Register(void);
extern "C" void thunk_igCollisionGridHelper_GetMetaObject(void);
extern "C" int DAT_00498450[4];
extern "C" int DAT_00498458[4];
extern "C" int DAT_00498460[4];
extern "C" int DAT_00498468[4];
extern "C" int DAT_0056dd28[4];
extern "C" void igCollisionGridHelper_InitFields(void);
extern "C" void FUN_0023a040(int arg0);
extern "C" int DAT_0056dd40[4];
extern "C" int FUN_0023a080(void);
extern "C" igMetaObject *g_igCollisionGrid_metaObject[4];
extern "C" igMetaObject *igCollisionGrid_GetMetaObject(void);
extern "C" int FUN_00198190(...);
extern "C" int DAT_0052d1c0[4];
union U_23a120 { int vt; char b[80]; };
extern "C" int igCollisionGrid_GetVTable(void);
extern "C" void **FUN_0023a240(void **arg0, long long arg1);
extern "C" void **FUN_0023a2c0(void **arg0, short arg1);
extern "C" void FUN_0023a340(void);
extern "C" char g_igCollisionGrid_callbackList[];
extern "C" char igCollisionGrid_className[];
extern "C" void igCollisionGrid_Register(void);
extern "C" void thunk_igCollisionGrid_GetMetaObject(void);
extern "C" int FUN_0018a6a0(...);
extern "C" int DAT_00498480[4];
extern "C" int DAT_004984c0[4];
extern "C" int DAT_00498500[4];
extern "C" int DAT_00498540[4];
extern "C" void igCollisionGrid_InitFields(void);
extern "C" int DAT_0056ddc0[4];
extern "C" int FUN_0023a570(void);
extern "C" igMetaObject *g_igCollisionCellList_metaObject[4];
extern "C" igMetaObject *igCollisionCellList_GetMetaObject(void);
extern "C" int DAT_0052d2f0[4];
extern "C" int igCollisionCellList_GetVTable(void);
extern "C" void FUN_0023a650(void);
extern "C" char g_igCollisionCellList_callbackList[];
extern "C" char igCollisionCellList_className[];
extern "C" void igCollisionCellList_Register(void);
extern "C" void thunk_igCollisionCellList_GetMetaObject(void);
extern "C" igCollisionCell *FUN_0023a6e0(int arg0);
extern "C" igMetaObject *g_igCollisionCell_metaObject[4];
extern "C" igMetaObject *igCollisionCell_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int DAT_0052d290[4];
struct Obj_23a770 {
    int *vt; int w0; T *r1; int w2; T *r3; int w4; int w5; int w6;
    inline void rel1() {
        T **self = &r1;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel3() {
        T **self = &r3;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" int igCollisionCell_GetVTable(void);
extern "C" void FUN_0023a850(void);
extern "C" char g_igCollisionCell_callbackList[];
extern "C" char igCollisionCell_className[];
extern "C" void igCollisionCell_Register(void);
extern "C" void thunk_igCollisionCell_GetMetaObject(void);
extern "C" int DAT_004985a0[4];
extern "C" int DAT_004985c0[4];
extern "C" int DAT_004985e0[4];
extern "C" int DAT_00498600[4];
extern "C" int DAT_0056ddc8[4];
extern "C" void igCollisionCell_InitFields(void);
extern "C" void FUN_0023a9d0(int arg0);
extern "C" igMetaObject *g_igBoundingSphereMaker_metaObject[4];
extern "C" igMetaObject *igBoundingSphereMaker_GetMetaObject(void);
extern "C" int DAT_0052d230[4];
union U_23aa60 { int vt; char b[16]; };
extern "C" int igBoundingSphereMaker_GetVTable(void);
extern "C" void FUN_0023aaf0(void);
extern "C" char g_igBoundingSphereMaker_callbackList[];
extern "C" char igBoundingSphereMaker_className[];
extern "C" void igBoundingSphereMaker_Register(void);
extern "C" void thunk_igBoundingSphereMaker_GetMetaObject(void);
extern "C" int FUN_00187e50(...);
extern "C" int DAT_00498620[4];
extern "C" int DAT_00498628[4];
extern "C" int DAT_00498630[4];
extern "C" int DAT_00498638[4];
extern "C" int DAT_0056de00[4];
extern "C" void igBoundingSphereMaker_InitFields(void);
extern "C" int FUN_0018d630(...);
extern "C" void FUN_0023b110(void *arg0, void *arg1);
extern "C" int FUN_0018de10(...);
extern "C" int FUN_0023ac20(...);
extern "C" int igObject_IsKindOf(...);
extern "C" int DAT_005612b0[4];
extern "C" int DAT_005619f8[4];
extern "C" int DAT_00561a38[4];
typedef struct S1 { char pad4[4]; int f4; } S1;
struct Ls { char p[8]; unsigned int n; char q[4]; struct Q **a; };
struct Q { char p[28]; struct Ls *f28; };
struct R { char p[8]; int f8; };
extern "C" void FUN_0023b140(struct R *arg0, struct Q *arg1);
struct ObjectSlotOwner {
    char pad[8];
    igObject *slot;
    void setSlot(const igSmartPointer<igObject> &object) {
        igObject *retained = object.get();
        igObject *previous;
        if (retained != 0) {
            retained->_refCount = retained->_refCount + 1;
        }
        previous = slot;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        slot = retained;
    }
    void clearSlot() {
        igObject *previous = slot;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        slot = 0;
    }
};
extern "C" igObject *FUN_00187e10(int);
extern "C" igSmartPointer<igObject> FUN_0023b270(ObjectSlotOwner *owner, int value);
struct RefCounted { int pad; int _refCount; };
struct RetainedList { int pad0[2]; void *_words; int pad1[2]; int _count;
};
extern "C" int List_InsertWords(void *list, int at, int n, void *from);
extern "C" void FUN_0023b3b0(RetainedList *list, RefCounted *object);
extern "C" void FUN_00301ee0(int, int);
extern "C" void FUN_0023b410(int *arg0, int arg1, int arg2, int arg3);
struct CellList : public igObjectList {
    void set(int index, const igSmartPointer<igCollisionCell> &cell) {
        igCollisionCell *entry = cell.p;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igCollisionCell **)_data)[index] = entry;
        }
    }
};
extern "C" void FUN_0023b430(igCollisionGrid *grid);
typedef struct B { int pad[2]; float v[3]; } B;
typedef struct G { char pad[16]; int nx, ny, nz; char pad2[28]; B *box; float sx, sy, sz; } G;
extern "C" void FUN_0023b720(G *g, float *p, int *ox, int *oy, int *oz);
extern "C" int FUN_0018ffa0(...);
class Sph { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vX();
    char pad[4]; float f8; float f12; float f16; float f20; };
struct Tab { char pad[16]; int *f16; };
struct Grid { char pad[8]; Tab *f8; int f12; int f16; int f20; };
struct Ent { char pad[16]; int f16; };
struct Arg1 { char pad[12]; Sph *f12; };
extern "C" int DAT_00560fa0[4];
extern "C" void FUN_0023b820(Grid *arg0, Arg1 *arg1);
struct E { char pad[36]; float f36; float f40; float f44; char pad2[12]; float f60; float f64; float f68; char pad3[16]; int f88; };
struct L { char pad[8]; int count; char pad2[4]; struct E **data; };
extern "C" int Gap__igCollisionGrid__vfunc_23(int arg0, struct L *arg1, int arg2);
typedef struct R_23ba40 { int pad; int f4; } R_23ba40;
typedef struct L_23ba40 { char pad[8]; int f8; int pad2; R_23ba40 **f16; } L_23ba40;
typedef struct A { char pad[44]; L_23ba40 *f44; L_23ba40 *f48; L_23ba40 *f52; } A;
extern "C" int Gap__igCollisionGrid__vfunc_24(A *arg0);
extern "C" void FUN_0023bc30(igCollisionGroup *arg0);
extern "C" int Gap__igCreateCollisionDatabase__vfunc_31(void);
extern "C" int Gap__igCreateCollisionDatabase__vfunc_33(void);
typedef struct Rc : public igObject { } Rc;
class Obj_23c250 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
typedef struct Inst { int pad[5]; Rc *f20; } Inst;
extern "C" Rc *FUN_002c37e0(int);
extern "C" int FUN_002d8fe0(Rc *, int);
extern "C" int FUN_002d8310(Rc *, Rc *);
extern "C" void FUN_0023c250(int *arg0);
extern "C" int Gap__igCreateCollisionDatabase__vfunc_22(void);
extern "C" int Gap__igCollisionGrid__vfunc_22(void);
extern "C" int Gap__igBoundingSphereMaker__vfunc_22(void);
extern "C" int Gap__igCollisionCell__vfunc_22(void);
extern "C" int Gap__igCollisionCellList__vfunc_22(void);
extern "C" int Gap__igCollisionGridHelper__vfunc_22(void);
extern "C" int Gap__igCollisionGroup__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionGroupList__vfunc_22(void);
extern "C" int Gap__igCollisionInfo__vfunc_22(void);
extern "C" int Gap__igCollisionCellList__vfunc_24(void);
extern "C" igMetaObject *Gap__igCollisionGroupList__vfunc_24(void);

void FUN_00239390(void) {
    FUN_002395b0();
    FUN_00239910();
    FUN_00239c80();
    FUN_00239b20();
    FUN_00239ee0();
    FUN_0023a340();
    FUN_0023a850();
    FUN_0023a650();
    FUN_0023aaf0();
}

void CollisionLibrary_MarkRegistered(void) {
    if (g_CollisionLibrary_registered == 0) {
        g_CollisionLibrary_registered = 1;
    }
}

igMetaObject *igCreateCollisionDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igCreateCollisionDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002395b0();
    return g_igCreateCollisionDatabase_metaObject[0];
}

int igCreateCollisionDatabase_GetVTable(void) {
    struct W o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader(&o);
    o.f[7] = 0;
    o.f[8] = 0;
    o.vt = &DAT_0052d130[0];
    p16 = &o.f[12];
    *p16 = 0;
    p17 = &o.f[13];
    *p17 = 0;
    p18 = &o.f[14];
    *p18 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052d130[0];
    FUN_0019c840(&o.f[15], -1);
    FUN_0019c840(p18, -1);
    FUN_00239530((O *)p17, -1);
    StringRef_Destruct_00130720(p16, -1);
    FUN_00225790(&o, 0);
    return r;
}

O *FUN_00239530(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_002395b0(void)
{
    igMetaObject_RunStaticInit(igCreateCollisionDatabase_Register);
}

void igCreateCollisionDatabase_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCreateCollisionDatabase_metaObject,
        igOptBase_Register,
        igOptBase_GetPublishedMetaObject,
        thunk_igCreateCollisionDatabase_GetMetaObject,
        igCreateCollisionDatabase_className,
        0x44, /* instance size */
        igCreateCollisionDatabase_GetVTable,
        &igCreateCollisionDatabase_InitFields,
        0, /* extra callback item */
        g_igCreateCollisionDatabase_callbackList /* callback list */
    );
}

void thunk_igCreateCollisionDatabase_GetMetaObject(void) {
    igCreateCollisionDatabase_GetMetaObject();
}

void igCreateCollisionDatabase_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498300[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1, igCollisionGrid_GetMetaObject());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0023a080();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498320[0], &DAT_00498340[0], &DAT_00498360[0], temp_s2);
}

Rc *FUN_002397a0(int arg0) {
    FUN_00239910();
    return (Rc *)igMetaObject_CreateInstance(*(int *)0x56DCC8, arg0);
}

igMetaObject *igCollisionInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239910();
    return g_igCollisionInfo_metaObject[0];
}

int igCollisionInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0052d4d0[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d4d0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00239910(void)
{
    igMetaObject_RunStaticInit(igCollisionInfo_Register);
}

void igCollisionInfo_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igCollisionInfo_GetMetaObject,
        igCollisionInfo_className,
        0x18, /* instance size */
        igCollisionInfo_GetVTable,
        &igCollisionInfo_InitFields,
        0, /* extra callback item */
        g_igCollisionInfo_callbackList /* callback list */
    );
}

void thunk_igCollisionInfo_GetMetaObject(void) {
    igCollisionInfo_GetMetaObject();
}

void igCollisionInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dcc8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498388[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0023a080();
    igMetaObject_NameFields(temp_s0, &DAT_00498390[0], &DAT_00498398[0], &DAT_004983a0[0], temp_s2);
}

int FUN_00239a40(void) {
    if (DAT_0056dcd8[0] == 0) {
        DAT_0056dcd8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dcd8[0];
}

igMetaObject *igCollisionGroupList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroupList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239b20();
    return g_igCollisionGroupList_metaObject[0];
}

int igCollisionGroupList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d460[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00239b20(void)
{
    igMetaObject_RunStaticInit(igCollisionGroupList_Register);
}

void igCollisionGroupList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionGroupList_GetMetaObject,
        igCollisionGroupList_className,
        0x14, /* instance size */
        igCollisionGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionGroupList_callbackList /* callback list */
    );
}

void thunk_igCollisionGroupList_GetMetaObject(void) {
    igCollisionGroupList_GetMetaObject();
}

igMetaObject *igCollisionGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239c80();
    return g_igCollisionGroup_metaObject[0];
}

int igCollisionGroup_GetVTable(void) {
    union U_239c00 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_0052d3c0[0];
    p = (int *)&u.b[32];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d3c0[0];
    FUN_001a7580(p, -1);
    FUN_00195a90(u.b, 0);
    return temp_s0;
}

void FUN_00239c80(void)
{
    igMetaObject_RunStaticInit(igCollisionGroup_Register);
}

void igCollisionGroup_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroup_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igCollisionGroup_GetMetaObject,
        igCollisionGroup_className,
        0x60, /* instance size */
        igCollisionGroup_GetVTable,
        &igCollisionGroup_InitFields,
        0, /* extra callback item */
        g_igCollisionGroup_callbackList /* callback list */
    );
}

void thunk_igCollisionGroup_GetMetaObject(void) {
    igCollisionGroup_GetMetaObject();
}

void igCollisionGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dce0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004983c0[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, &DAT_004983e0[0], &DAT_00498400[0], &DAT_00498420[0], temp_s2);
}

igMetaObject *igCollisionGridHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGridHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239ee0();
    return g_igCollisionGridHelper_metaObject[0];
}

int igCollisionGridHelper_GetVTable(void) {
    union U_239e00 u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader(u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&DAT_0052d360[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d360[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s1;
}

void FUN_00239ee0(void)
{
    igMetaObject_RunStaticInit(igCollisionGridHelper_Register);
}

void igCollisionGridHelper_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGridHelper_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGridHelper_GetMetaObject,
        igCollisionGridHelper_className,
        0x10, /* instance size */
        igCollisionGridHelper_GetVTable,
        &igCollisionGridHelper_InitFields,
        0, /* extra callback item */
        g_igCollisionGridHelper_callbackList /* callback list */
    );
}

void thunk_igCollisionGridHelper_GetMetaObject(void) {
    igCollisionGridHelper_GetMetaObject();
}

void igCollisionGridHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dd28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498450[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0023a080();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    igMetaObject_NameFields(temp_s0, &DAT_00498458[0], &DAT_00498460[0], &DAT_00498468[0], temp_s2);
}

void FUN_0023a040(int arg0) {
    FUN_0023a340();
    igMetaObject_CreateInstance(*(int *)0x56DD40, arg0);
}

int FUN_0023a080(void) {
    if (DAT_0056dd40[0] == 0) {
        DAT_0056dd40[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dd40[0];
}

igMetaObject *igCollisionGrid_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGrid_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a340();
    return g_igCollisionGrid_metaObject[0];
}

int igCollisionGrid_GetVTable(void) {
    union U_23a120 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052d1c0[0];
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d1c0[0];
    FUN_00198190(&u.b[56], -1);
    FUN_0023a2c0((void **)&u.b[52], -1);
    FUN_0023a2c0((void **)&u.b[48], -1);
    FUN_0023a2c0((void **)&u.b[44], -1);
    FUN_0023a2c0((void **)&u.b[40], -1);
    FUN_0023a240((void **)&u.b[36], -1);
    FUN_0023a240((void **)&u.b[12], -1);
    FUN_0023a240((void **)&u.b[8], -1);
    return r;
}

void **FUN_0023a240(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_0023a2c0(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0023a340(void)
{
    igMetaObject_RunStaticInit(igCollisionGrid_Register);
}

void igCollisionGrid_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGrid_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGrid_GetMetaObject,
        igCollisionGrid_className,
        0x4C, /* instance size */
        igCollisionGrid_GetVTable,
        &igCollisionGrid_InitFields,
        0, /* extra callback item */
        g_igCollisionGrid_callbackList /* callback list */
    );
}

void thunk_igCollisionGrid_GetMetaObject(void) {
    igCollisionGrid_GetMetaObject();
}

void igCollisionGrid_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dd40[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498480[0], 0xF);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0023a570();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0023a570();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0023a570();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00239a40();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00239a40();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00239a40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00239a40();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004984c0[0], &DAT_00498500[0], &DAT_00498540[0], temp_s1);
}

int FUN_0023a570(void) {
    if (DAT_0056ddc0[0] == 0) {
        DAT_0056ddc0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056ddc0[0];
}

igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a650();
    return g_igCollisionCellList_metaObject[0];
}

int igCollisionCellList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d2f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0023a650(void)
{
    igMetaObject_RunStaticInit(igCollisionCellList_Register);
}

void igCollisionCellList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCellList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionCellList_GetMetaObject,
        igCollisionCellList_className,
        0x14, /* instance size */
        igCollisionCellList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionCellList_callbackList /* callback list */
    );
}

void thunk_igCollisionCellList_GetMetaObject(void) {
    igCollisionCellList_GetMetaObject();
}

igCollisionCell *FUN_0023a6e0(int arg0) {
    FUN_0023a850();
    return (igCollisionCell *)igMetaObject_CreateInstance(*(int *)0x56DDC8, arg0);
}

igMetaObject *igCollisionCell_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCell_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a850();
    return g_igCollisionCell_metaObject[0];
}

int igCollisionCell_GetVTable(void) {
    Obj_23a770 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d290[0];
    obj.r1 = 0;
    obj.r3 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052d290[0];
    obj.rel3();
    obj.rel1();
    return r;
}

void FUN_0023a850(void)
{
    igMetaObject_RunStaticInit(igCollisionCell_Register);
}

void igCollisionCell_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCell_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionCell_GetMetaObject,
        igCollisionCell_className,
        0x20, /* instance size */
        igCollisionCell_GetVTable,
        &igCollisionCell_InitFields,
        0, /* extra callback item */
        g_igCollisionCell_callbackList /* callback list */
    );
}

void thunk_igCollisionCell_GetMetaObject(void) {
    igCollisionCell_GetMetaObject();
}

void igCollisionCell_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056ddc8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004985a0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00239a40();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0023a080();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004985c0[0], &DAT_004985e0[0], &DAT_00498600[0], temp_s2);
}

void FUN_0023a9d0(int arg0) {
    FUN_0023aaf0();
    igMetaObject_CreateInstance(*(int *)0x56DE00, arg0);
}

igMetaObject *igBoundingSphereMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingSphereMaker_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023aaf0();
    return g_igBoundingSphereMaker_metaObject[0];
}

int igBoundingSphereMaker_GetVTable(void) {
    union U_23aa60 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&DAT_0052d230[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d230[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_0023aaf0(void)
{
    igMetaObject_RunStaticInit(igBoundingSphereMaker_Register);
}

void igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingSphereMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingSphereMaker_GetMetaObject,
        igBoundingSphereMaker_className,
        0xC, /* instance size */
        igBoundingSphereMaker_GetVTable,
        &igBoundingSphereMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingSphereMaker_callbackList /* callback list */
    );
}

void thunk_igBoundingSphereMaker_GetMetaObject(void) {
    igBoundingSphereMaker_GetMetaObject();
}

void igBoundingSphereMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056de00[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498620[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00187e50();
    igMetaObject_NameFields(temp_s0, &DAT_00498628[0], &DAT_00498630[0], &DAT_00498638[0], temp_s2);
}

void FUN_0023b110(void *arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        FUN_0018d630(*(int *)((char *)(arg0) + 8), (char *)arg1 + 0x20);
    }
}

void FUN_0023b140(struct R *arg0, struct Q *arg1) {
    S1 *sp5C;
    S1 *t;
    unsigned int var_s1;
    unsigned int var_s0;
    struct Ls *temp_v0;

    if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) {
        temp_v0 = arg1->f28;
        var_s1 = 0;
        if (temp_v0 != 0) {
            var_s1 = temp_v0->n;
        }
        var_s0 = 0;
        while (var_s0 < var_s1) {
            FUN_0023b140(arg0, arg1->f28->a[var_s0]);
            var_s0 += 1;
        }
    }
    if (igObject_IsKindOf(arg1, DAT_00561a38[0]) != 0) {
        FUN_0023ac20(&sp5C, arg0, arg1);
        FUN_0018de10(arg0->f8, sp5C);
        t = sp5C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    } else if (igObject_IsKindOf(arg1, DAT_005612b0[0]) != 0) {
        FUN_0023b110(arg0, arg1);
    }
}

igSmartPointer<igObject> FUN_0023b270(ObjectSlotOwner *owner, int value) {
    igSmartPointer<igObject> object(FUN_00187e10(0), AdoptReference());
    owner->setSlot(object);
    FUN_0023b140((R *)owner, (Q *)value);
    owner->clearSlot();
    return object;
}

void FUN_0023b3b0(RetainedList *list, RefCounted *object) {
    int at = list->_count;
    void *words = list->_words;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    List_InsertWords(words, at, 1, &object);
    list->_count = list->_count + 1;
}

void FUN_0023b410(int *arg0, int arg1, int arg2, int arg3) {
    arg0[4] = arg1; arg0[5] = arg2; arg0[6] = arg3;
    FUN_00301ee0(arg0[2], arg1 * arg2 * arg3);
}

static inline float minOf(float a, float b) { return a < b ? a : b; }

static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void FUN_0023b430(igCollisionGrid *grid) {
    igAABox *bound = (igAABox *)grid->_bound;
    float &stepY = grid->_deltas[1];
    float &stepZ = grid->_deltas[2];
    grid->_deltas[0] = bound->_max[0] - bound->_min[0];
    grid->_deltas[1] = bound->_max[1] - bound->_min[1];
    grid->_deltas[2] = bound->_max[2] - bound->_min[2];
    grid->_deltas[0] = grid->_deltas[0] / (float)grid->_sizeX;
    grid->_deltas[1] = grid->_deltas[1] / (float)grid->_sizeY;
    grid->_deltas[2] = grid->_deltas[2] / (float)grid->_sizeZ;
    grid->_maxRadius = minOf(grid->_deltas[0], grid->_deltas[1]);
    grid->_maxRadius = minOf(grid->_maxRadius, stepZ);
    grid->_maxRadius = grid->_maxRadius * 0.5f;
    int index = 0;
    const float *origin = ((igAABox *)grid->_bound)->_min;
    float x = origin[0];
    float y = origin[1];
    float z = origin[2];
    for (int k = 0; k < grid->_sizeZ; k++) {
        for (int j = 0; j < grid->_sizeY; j++) {
            for (int i = 0; i < grid->_sizeX; i++) {
                igSmartPointer<igCollisionCell> cell(FUN_0023a6e0(0), AdoptReference());
                float maxX = x + grid->_deltas[0];
                float maxY = y + grid->_deltas[1];
                float maxZ = z + grid->_deltas[2];
                cell->_grid = (int)grid;
                igCollisionCell *c = cell.p;
                setVec3(((igAABox *)c->_box)->_min, x, y, z);
                setVec3(((igAABox *)c->_box)->_max, maxX, maxY, maxZ);
                ((CellList *)grid->_cells)->set(index, cell);
                index++;
                x += grid->_deltas[0];
            }
            origin = ((igAABox *)grid->_bound)->_min;
            x = origin[0];
            y += stepY;
        }
        y = origin[1];
        z += stepZ;
    }
}

void FUN_0023b720(G *g, float *p, int *ox, int *oy, int *oz) {
    float x = p[0], y = p[1], z = p[2];
    B *b = g->box;
    float *v = b->v;
    float *nv = b->v;
    float t;
    t = b->v[0]; if (x < t) x = t;
    t = v[1]; if (y < t) y = t;
    t = v[2]; if (z < t) z = t;
    {
    float a0 = nv[0], a1 = nv[1], a2 = nv[2];
    x = x - a0; y = y - a1; z = z - a2;
    x = x / g->sx; y = y / g->sy; z = z / g->sz;
    }
    *ox = (int)x;
    if (g->nx <= *ox) *ox = g->nx - 1;
    *oy = (int)y;
    if (g->ny <= *oy) *oy = g->ny - 1;
    *oz = (int)z;
    if (g->nz <= *oz) *oz = g->nz - 1;
}

void FUN_0023b820(Grid *arg0, Arg1 *arg1) {
    int mnx, mny, mnz, mxx, mxy, mxz;
    float v[3];
    Sph *s0;
    int z;
    int y;
    int x;
    int base1, base2;
    Ent *e;
    float r;
    s0 = arg1->f12;
    mnx = -1; mny = -1; mnz = -1; mxx = -1; mxy = -1; mxz = -1;
    if (DAT_00560fa0[0] == s0->vX()) {
        r = s0->f20;
        v[0] = s0->f8 - r;
        v[1] = s0->f12 - r;
        v[2] = s0->f16 - r;
        FUN_0023b720((G *)arg0, v, &mnx, &mny, &mnz);
        v[0] = s0->f8 + r;
        v[1] = s0->f12 + r;
        v[2] = s0->f16 + r;
        FUN_0023b720((G *)arg0, v, &mxx, &mxy, &mxz);
    }
    for (z = mnz; z <= mxz; z++) {
        base1 = arg0->f20 * z;
        for (y = mny; y <= mxy; y++) {
            base2 = arg0->f16 * (y + base1);
            for (x = mnx; x <= mxx; x++) {
                e = (Ent *)arg0->f8->f16[x + base2];
                if (FUN_0018ffa0(e->f16, arg1->f12) != 0) {
                    FUN_0023b3b0((RetainedList *)e, (RefCounted *)arg1);
                }
            }
        }
    }
}

int Gap__igCollisionGrid__vfunc_23(int arg0, struct L *arg1, int arg2) {
    struct E *e;
    int n = arg1->count;
    while (arg2 < n) {
        e = arg1->data[arg2];
        arg2++;
        e->f88 = 0x3F800000;
        e->f60 = e->f36;
        e->f64 = e->f40;
        e->f68 = e->f44;
    }
    return 0;
}

int Gap__igCollisionGrid__vfunc_24(A *arg0) {
    L_23ba40 *l;
    int n;
    int i;
    R_23ba40 *o;
    int n2;
    int j;

    l = arg0->f44;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f48;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f52;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;
    return 0;
}

void FUN_0023bc30(igCollisionGroup *arg0) {
    igSphere *temp_v1;

    *(int *)&arg0->_time = 0xBF800000;
    temp_v1 = (igSphere *)arg0->_bound;
    *(float *)&arg0->_position[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_position[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_position[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_lastPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_lastPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_lastPosition[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_collisionPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_collisionPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_collisionPosition[2] = (float) *(float *)&temp_v1->_center[2];
    arg0->_radius = (float) temp_v1->_radius;
}

int Gap__igCreateCollisionDatabase__vfunc_31(void) {
    return 1;
}

int Gap__igCreateCollisionDatabase__vfunc_33(void) {
    return 1;
}

/* Selects the constructor that takes over the factory's reference. */

void FUN_0023c250(int *arg0) {    igSmartPointer<Rc> a(FUN_002c37e0(0), AdoptReference());
    FUN_002d8fe0(a.get(), arg0[13]);
    igSmartPointer<Rc> b(FUN_002397a0(0), AdoptReference());
    {
    Rc *s1 = (Rc *)arg0[14];
    Inst *s0 = (Inst *)b.get();
    if (s1) s1->_refCount = s1->_refCount + 1;
    Rc *t = s0->f20;
    if (t) { t->_refCount = t->_refCount - 1; if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t); }
    s0->f20 = s1;
    }
    FUN_002d8310(a.get(), b.get());
    ((Obj_23c250 *)a.get())->vX(arg0[13]);
}

int Gap__igCreateCollisionDatabase__vfunc_22(void) {
    return DAT_0056dc88[0];
}

int Gap__igCollisionGrid__vfunc_22(void) {
    return DAT_0056dd40[0];
}

int Gap__igBoundingSphereMaker__vfunc_22(void) {
    return DAT_0056de00[0];
}

int Gap__igCollisionCell__vfunc_22(void) {
    return DAT_0056ddc8[0];
}

int Gap__igCollisionCellList__vfunc_22(void) {
    return DAT_0056ddc0[0];
}

int Gap__igCollisionGridHelper__vfunc_22(void) {
    return DAT_0056dd28[0];
}

int Gap__igCollisionGroup__vfunc_22(void) {
    return DAT_0056dce0[0];
}

igMetaObject *Gap__igCollisionGroupList__vfunc_22(void) {
    return g_igCollisionGroupList_metaObject[0];
}

int Gap__igCollisionInfo__vfunc_22(void) {
    return DAT_0056dcc8[0];
}

int Gap__igCollisionCellList__vfunc_24(void) {
    return DAT_0056ddc8[0];
}

igMetaObject *Gap__igCollisionGroupList__vfunc_24(void) {
    return g_igCollisionGroup_metaObject[0];
}


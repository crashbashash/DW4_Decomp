#ifndef DW4_COLLISION_LIBRARY_H
#define DW4_COLLISION_LIBRARY_H

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
extern "C" void * g_objectSystem[4];
extern "C" int igCreateCollisionDatabase_GetVTable(void);
extern "C" int __dl__FPv(void *);
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
extern "C" int g_igCreateCollisionDatabase_ctorTable[4];
extern "C" int g_igCreateCollisionDatabase_fieldTable[4];
extern "C" int DAT_00498340[4];
extern "C" int DAT_00498360[4];
extern "C" void igCreateCollisionDatabase_InitFields(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" Rc *FUN_002397a0(int arg0);
extern "C" igMetaObject *g_igCollisionInfo_metaObject[4];
extern "C" igMetaObject *igCollisionInfo_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int g_igNamedObject_vtable[4];
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
extern "C" int g_igCollisionInfo_ctorTable[4];
extern "C" int g_igCollisionInfo_fieldTable[4];
extern "C" int DAT_00498398[4];
extern "C" int DAT_004983a0[4];
extern "C" void igCollisionInfo_InitFields(void);
extern "C" igMetaObject *igMetaObject_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igMetaObject *g_igCollisionGroupList_metaObject[4];
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" igMetaObject *FUN_00239a40(void);
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
extern "C" int g_igCollisionGroup_ctorTable[4];
extern "C" int g_igCollisionGroup_fieldTable[4];
extern "C" int DAT_00498400[4];
extern "C" int DAT_00498420[4];
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
extern "C" int g_igCollisionGridHelper_ctorTable[4];
extern "C" int g_igCollisionGridHelper_fieldTable[4];
extern "C" int DAT_00498460[4];
extern "C" int DAT_00498468[4];
extern "C" void igCollisionGridHelper_InitFields(void);
extern "C" void FUN_0023a040(int arg0);
extern "C" igMetaObject *g_igCollisionGrid_metaObject[4];
extern "C" igMetaObject *FUN_0023a080(void);
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
extern "C" int g_igCollisionGrid_ctorTable[4];
extern "C" int g_igCollisionGrid_fieldTable[4];
extern "C" int DAT_00498500[4];
extern "C" int DAT_00498540[4];
extern "C" void igCollisionGrid_InitFields(void);
extern "C" igMetaObject *g_igCollisionCellList_metaObject[4];
extern "C" igMetaObject *FUN_0023a570(void);
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
extern "C" int g_igCollisionCell_ctorTable[4];
extern "C" int g_igCollisionCell_fieldTable[4];
extern "C" int DAT_004985e0[4];
extern "C" int DAT_00498600[4];
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
extern "C" int g_igBoundingSphereMaker_ctorTable[4];
extern "C" int g_igBoundingSphereMaker_fieldTable[4];
extern "C" int DAT_00498630[4];
extern "C" int DAT_00498638[4];
extern "C" void igBoundingSphereMaker_InitFields(void);
extern "C" int FUN_0018d630(...);
extern "C" void FUN_0023b110(void *arg0, void *arg1);
extern "C" int FUN_0018de10(...);
extern "C" int FUN_0023ac20(...);
extern "C" int igObject_IsKindOf(...);
extern "C" int g_igTransform_metaObject[4];
extern "C" int g_igGroup_metaObject[4];
extern "C" int g_igGeometry_metaObject[4];
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
extern "C" int g_igSphere_metaObject[4];
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
extern "C" igMetaObject *Gap__igCreateCollisionDatabase__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionGrid__vfunc_22(void);
extern "C" igMetaObject *Gap__igBoundingSphereMaker__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionCell__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionCellList__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionGridHelper__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionGroup__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionGroupList__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__igCollisionCellList__vfunc_24(void);
extern "C" igMetaObject *Gap__igCollisionGroupList__vfunc_24(void);

#endif

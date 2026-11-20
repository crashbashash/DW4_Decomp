#ifndef DW4_COLLISION_LIBRARY_H
#define DW4_COLLISION_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/support/ClassRegistration.h"

#include "dw4/core/igMetaObject.h"
class igMemoryPoolView;
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
struct Rc;
extern "C" unsigned char g_CollisionLibrary_registered;
extern "C" void CollisionLibrary_MarkRegistered(void);
extern "C" igMetaObject *g_igCreateCollisionDatabase_metaObject;
extern "C" igMetaObject *igCreateCollisionDatabase_GetMetaObject(void);
struct W { int *vt; int f[19]; };
#include "dw4/core/igObject.h"
extern "C" int g_igCreateCollisionDatabase_vtable[4];
#include "dw4/core/igObjectSystem.h"
#include "dw4/base/igOptBase.h"
#include "dw4/core/igIGBFile.h"
#include "dw4/core/igDirectory.h"
extern "C" int igCreateCollisionDatabase_GetVTable(void);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_00239530(O *arg0, short arg1);
extern "C" void igCreateCollisionDatabase_EnsureRegistered(void);
extern "C" igMetaObject *igOptBase_GetPublishedMetaObject(void);
extern "C" CallbackArray *igCreateCollisionDatabase_Register(void);
extern "C" void igCreateCollisionDatabase_GetMetaObjectFunction(void);
extern "C" void igCreateCollisionDatabase_InitFields(void);
extern "C" Rc *igCollisionInfo_Create(int arg0);
extern "C" igMetaObject *g_igCollisionInfo_metaObject;
extern "C" igMetaObject *igCollisionInfo_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
#include "dw4/core/StringPool.h"
#include "dw4/core/igNamedObject.h"
extern "C" int g_igCollisionInfo_vtable[4];
union U { int vt; char b[32]; };
extern "C" int igCollisionInfo_GetVTable(void);
extern "C" void igCollisionInfo_EnsureRegistered(void);
#include "dw4/core/igInfo.h"
extern "C" CallbackArray *igCollisionInfo_Register(void);
extern "C" void igCollisionInfo_GetMetaObjectFunction(void);
extern "C" void igCollisionInfo_InitFields(void);
#include "dw4/core/igMemoryPoolContext.h"
extern "C" igMetaObject *g_igCollisionGroupList_metaObject;
extern "C" igMetaObject *igCollisionGroupList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCollisionGroupList_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int g_igCollisionGroupList_vtable[4];
extern "C" int igCollisionGroupList_GetVTable(void);
extern "C" void igCollisionGroupList_EnsureRegistered(void);
#include "dw4/core/igObjectList.h"
extern "C" CallbackArray *igCollisionGroupList_Register(void);
extern "C" void igCollisionGroupList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igCollisionGroup_metaObject;
extern "C" igMetaObject *igCollisionGroup_GetMetaObject(void);
extern "C" int g_igCollisionGroup_vtable[4];
union U_239c00 { int vt; char b[96]; };
extern "C" int igCollisionGroup_GetVTable(void);
extern "C" void igCollisionGroup_EnsureRegistered(void);
#include "dw4/scenegraph/igGroup.h"
extern "C" CallbackArray *igCollisionGroup_Register(void);
extern "C" void igCollisionGroup_GetMetaObjectFunction(void);
#include "dw4/scenegraph/igTransform.h"
#include "dw4/maths/igAABox.h"
extern "C" void igCollisionGroup_InitFields(void);
extern "C" igMetaObject *g_igCollisionGridHelper_metaObject;
extern "C" igMetaObject *igCollisionGridHelper_GetMetaObject(void);
union U_239e00 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int g_igCollisionGridHelper_vtable[4];
extern "C" int igCollisionGridHelper_GetVTable(void);
extern "C" void igCollisionGridHelper_EnsureRegistered(void);
extern "C" CallbackArray *igCollisionGridHelper_Register(void);
extern "C" void igCollisionGridHelper_GetMetaObjectFunction(void);
extern "C" void igCollisionGridHelper_InitFields(void);
extern "C" igObject *igCollisionGrid_Create(int arg0);
extern "C" igMetaObject *g_igCollisionGrid_metaObject;
extern "C" igMetaObject *igCollisionGrid_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCollisionGrid_GetMetaObject(void);
extern "C" int g_igCollisionGrid_vtable[4];
union U_23a120 { int vt; char b[80]; };
extern "C" int igCollisionGrid_GetVTable(void);
extern "C" void **FUN_0023a240(void **arg0, long long arg1);
extern "C" void **FUN_0023a2c0(void **arg0, short arg1);
extern "C" void igCollisionGrid_EnsureRegistered(void);
extern "C" CallbackArray *igCollisionGrid_Register(void);
extern "C" void igCollisionGrid_GetMetaObjectFunction(void);
extern "C" void igCollisionGrid_InitFields(void);
extern "C" igMetaObject *g_igCollisionCellList_metaObject;
extern "C" igMetaObject *igCollisionCellList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCollisionCellList_GetMetaObject(void);
extern "C" int g_igCollisionCellList_vtable[4];
extern "C" int igCollisionCellList_GetVTable(void);
extern "C" void igCollisionCellList_EnsureRegistered(void);
extern "C" CallbackArray *igCollisionCellList_Register(void);
extern "C" void igCollisionCellList_GetMetaObjectFunction(void);
extern "C" igCollisionCell *igCollisionCell_Create(int arg0);
extern "C" igMetaObject *g_igCollisionCell_metaObject;
extern "C" igMetaObject *igCollisionCell_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int g_igCollisionCell_vtable[4];
struct Obj_23a770 {
    int *vt; int w0; T *r1; int w2; T *r3; int w4; int w5; int w6;
    inline void rel1() {
        T **self = &r1;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
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
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igCollisionCell_GetVTable(void);
extern "C" void igCollisionCell_EnsureRegistered(void);
extern "C" CallbackArray *igCollisionCell_Register(void);
extern "C" void igCollisionCell_GetMetaObjectFunction(void);
extern "C" void igCollisionCell_InitFields(void);
extern "C" igObject *igBoundingSphereMaker_Create(int arg0);
extern "C" igMetaObject *g_igBoundingSphereMaker_metaObject;
extern "C" igMetaObject *igBoundingSphereMaker_GetMetaObject(void);
extern "C" int g_igBoundingSphereMaker_vtable[4];
union U_23aa60 { int vt; char b[16]; };
extern "C" int igBoundingSphereMaker_GetVTable(void);
extern "C" void igBoundingSphereMaker_EnsureRegistered(void);
extern "C" CallbackArray *igBoundingSphereMaker_Register(void);
extern "C" void igBoundingSphereMaker_GetMetaObjectFunction(void);
extern "C" void igBoundingSphereMaker_InitFields(void);
extern "C" void FUN_0018d630(igSphere*, float const*);
extern "C" void FUN_0023b110(void *arg0, void *arg1);
/* A new sphere bounding the vertices of `geometry` (Ritter's method). */
extern "C" igSmartPointer<igSphere> FUN_0023ac20(igBoundingSphereMaker *self, igGeometry *geometry);
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/gfx/igVertexArray.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/scenegraph/igNode.h"
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
#include "dw4/core/igDataLists.h"
#include "dw4/maths/igSphere.h"
extern "C" void FUN_0023b3b0(RetainedList *list, RefCounted *object);
#include "dw4/support/list-services.h"
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
extern "C" int FUN_0018ffa0(void**, void**);
class Sph { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vX();
    char pad[4]; float f8; float f12; float f16; float f20; };
struct Tab { char pad[16]; int *f16; };
struct Grid { char pad[8]; Tab *f8; int f12; int f16; int f20; };
struct Ent { char pad[16]; int f16; };
struct Arg1 { char pad[12]; Sph *f12; };
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
extern "C" void FUN_0023c250(int *arg0);
extern "C" igMetaObject *igCreateCollisionDatabase_GetMeta(void);
extern "C" igMetaObject *igCollisionGrid_GetMeta(void);
extern "C" igMetaObject *igBoundingSphereMaker_GetMeta(void);
extern "C" igMetaObject *igCollisionCell_GetMeta(void);
extern "C" igMetaObject *igCollisionCellList_GetMeta(void);
extern "C" igMetaObject *igCollisionGridHelper_GetMeta(void);
extern "C" igMetaObject *igCollisionGroup_GetMeta(void);
extern "C" igMetaObject *igCollisionGroupList_GetMeta(void);
extern "C" igMetaObject *igCollisionInfo_GetMeta(void);
extern "C" igMetaObject *igCollisionCellList_GetElementMeta(void);
extern "C" igMetaObject *igCollisionGroupList_GetElementMeta(void);

#endif

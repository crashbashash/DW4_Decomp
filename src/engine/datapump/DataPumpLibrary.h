#ifndef DW4_DATA_PUMP_LIBRARY_H
#define DW4_DATA_PUMP_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igSmartPointerDestruct.h"
#include "dw4/igDataPumpInfo.h"
#include "dw4/igVec3f.h"
#include "dw4/igNonRefCountedObjectStack.h"
#include "dw4/igRandomNumber.h"


class igMemoryPoolView;
#include "dw4/igBoolMetaField.h"
#include "dw4/igFloatMetaField.h"
#include "dw4/igIntMetaField.h"
#include "dw4/igMatrix44fMetaField.h"
#include "dw4/igObjectRefMetaField.h"
#include "dw4/igStringMetaField.h"
#include "dw4/igUnsignedIntArrayMetaField.h"
#include "dw4/igObject.h"
#include "dw4/igMetaField.h"
extern "C" char text_value[];

#include "dw4/igMetaObject.h"
#include "dw4/igRegistry.h"
extern "C" void DataPumpLibrary_MarkRegistered(void);
#include "dw4/igMemoryPoolContext.h"
extern "C" igMetaObject *FUN_001e4010(void);
extern "C" igMetaObject *igLongStack_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int g_igLongStack_vtable[4];
#include "dw4/igObjectSystem.h"
extern "C" int igLongStack_GetVTable(void);
extern "C" void FUN_001e40f0(void);
#include "dw4/igDataLists.h"
extern "C" void igLongStack_InitFields_001e4180(void);
extern "C" CallbackArray *igLongStack_Register(void);
extern "C" void thunk_igLongStack_GetMetaObject(void);
extern "C" int igLongMetaField_GetDefaultDescriptor(...);
extern "C" int ObjectPointerList_FindIndex(...);
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void FUN_001e4180(void);
extern "C" igMetaObject *igRandomNumber_GetMetaObject(void);
extern "C" void igRandomNumber_InitFields_001e4370(void);
extern "C" CallbackArray *igRandomNumber_Register(void);
extern "C" void thunk_igRandomNumber_GetMetaObject(void);
extern "C" void FUN_001e4370(void);
extern "C" void thunk_igMersenneTwisterRandomNumber_GetMetaObject(void);
extern "C" igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void);
extern "C" int g_igNonRefCountedObjectStack_vtable[4];
extern "C" int igNonRefCountedObjectStack_GetVTable(void);
extern "C" void FUN_001e4430(void);
extern "C" void igNonRefCountedObjectStack_InitFields_001e44c0(void);
extern "C" void thunk_igNonRefCountedObjectStack_GetMetaObject(void);
extern "C" int igObjectRefMetaField_GetDefaultDescriptor(...);
extern "C" void FUN_001e44c0(void);
extern "C" igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void);
struct Obj_1e45e0 { int *vt; char pad[2508]; };
extern "C" int g_igMersenneTwisterRandomNumber_vtable[4];
extern "C" int igMersenneTwisterRandomNumber_GetVTable(void);
extern "C" void FUN_001e4620(void);
extern "C" igMetaObject *igRandomNumber_GetPublishedMetaObject(void);
extern "C" CallbackArray *igMersenneTwisterRandomNumber_Register(void);
extern "C" igMetaObject *FUN_001e46a0(void);
struct F { char pad[52]; int f52; };
extern "C" void igMersenneTwisterRandomNumber_InitFields(void);
extern "C" igMetaObject *FUN_001e4740(void);
extern "C" igMetaObject *igMatrixStack_GetMetaObject(void);
extern "C" int g_igMatrixStack_vtable[4];
extern "C" int igMatrixStack_GetVTable(void);
extern "C" void FUN_001e4820(void);
extern "C" void igMatrixStack_InitFields_001e48b0(void);
extern "C" CallbackArray *igMatrixStack_Register(void);
extern "C" void thunk_igMatrixStack_GetMetaObject(void);
extern "C" int FUN_001888e0(...);
extern "C" void FUN_001e48b0(void);
extern "C" igMetaObject *FUN_001e4970(void);
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void);
extern "C" int g_igNonRefCountedMatrixObjectList_vtable[4];
extern "C" int igNonRefCountedMatrixObjectList_GetVTable(void);
extern "C" void FUN_001e4a50(void);
#include "dw4/igNonRefCountedObjectList.h"
extern "C" CallbackArray *igNonRefCountedObjectList_Register(void);
extern "C" CallbackArray *igNonRefCountedMatrixObjectList_Register(void);
extern "C" void thunk_igNonRefCountedMatrixObjectList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001e4ae0(void);
extern "C" igMetaObject *igMatrixObjectList_GetMetaObject(void);
extern "C" int g_igMatrixObjectList_vtable[4];
extern "C" int igMatrixObjectList_GetVTable(void);
extern "C" void FUN_001e4bc0(void);
#include "dw4/igObjectList.h"
extern "C" CallbackArray *igMatrixObjectList_Register(void);
extern "C" void thunk_igMatrixObjectList_GetMetaObject(void);
extern "C" void FUN_001e4c50(int arg0);
extern "C" igMetaObject *igMatrixObject_GetMetaObject(void);
struct Obj_1e4ce0 { int *vt; char pad[76]; };
#include "dw4/igMatrix44f.h"
extern "C" int g_igMatrixObject_vtable[4];
extern "C" int igMatrixObject_GetVTable(void);
extern "C" void FUN_001e4d30(void);
extern "C" CallbackArray *igMatrixObject_Register(void);
extern "C" void thunk_igMatrixObject_GetMetaObject(void);
extern "C" void igMatrixObject_InitFields(void);
extern "C" igMetaObject *igIntObject_GetMetaObject(void);
struct Obj_1e4e80 { int *vt; char pad[12]; };
extern "C" int g_igIntObject_vtable[4];
extern "C" int igIntObject_GetVTable(void);
extern "C" void FUN_001e4ec0(void);
extern "C" CallbackArray *igIntObject_Register(void);
extern "C" void thunk_igIntObject_GetMetaObject(void);
extern "C" void igIntObject_InitFields(void);
extern "C" igMetaObject *igFloatObject_GetMetaObject(void);
struct Obj_1e5010 { int *vt; char pad[12]; };
extern "C" int g_igFloatObject_vtable[4];
extern "C" int igFloatObject_GetVTable(void);
extern "C" void FUN_001e5050(void);
extern "C" CallbackArray *igFloatObject_Register(void);
extern "C" void thunk_igFloatObject_GetMetaObject(void);
extern "C" void igFloatObject_InitFields(void);
extern "C" igMetaObject *FUN_001e5150(void);
extern "C" igMetaObject *igDataPumpManager_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int g_igDataPumpManager_vtable[4];
struct Obj_1e51f0 {
    int *vt; int w0[1]; T *ref; int w1[1]; 
    inline void release() {
        T **self = &ref;
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
extern "C" int igDataPumpManager_GetVTable(void);
extern "C" void FUN_001e5280(void);
extern "C" CallbackArray *igDataPumpManager_Register(void);
extern "C" void thunk_igDataPumpManager_GetMetaObject(void);
extern "C" void igDataPumpManager_InitFields(void);
extern "C" igMetaObject *FUN_001e53c0(void);
extern "C" igMetaObject *igDataPumpList_GetMetaObject(void);
extern "C" int g_igDataPumpList_vtable[4];
extern "C" int igDataPumpList_GetVTable(void);
extern "C" void FUN_001e54a0(void);
extern "C" CallbackArray *igDataPumpList_Register(void);
extern "C" void thunk_igDataPumpList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001e5530(void);
extern "C" igMetaObject *igDataPumpInterface_GetMetaObject(void);
extern "C" void FUN_001e55d0(void);
extern "C" CallbackArray *igDataPumpInterface_Register(void);
extern "C" void thunk_igDataPumpInterface_GetMetaObject(void);
extern "C" void FUN_001e5650(int arg0);
extern "C" igMetaObject *FUN_001e5690(void);
extern "C" igMetaObject *igDataPumpInfo_GetMetaObject(void);
#include "dw4/StringPool.h"
#include "dw4/igNamedObject.h"
extern "C" int g_igDataPumpInfo_vtable[4];
struct Obj_1e5730 {
    int *vt; int w0; int *r1; int w2; int w3; T *r4; int w5; int w6;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    inline void rel4() {
        T **self = &r4;
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
extern "C" int igDataPumpInfo_GetVTable(void);
extern "C" void FUN_001e5810(void);
#include "dw4/igInfo.h"
extern "C" CallbackArray *igInfo_Register(void);
extern "C" CallbackArray *igDataPumpInfo_Register(void);
extern "C" void thunk_igDataPumpInfo_GetMetaObject(void);
extern "C" void igDataPumpInfo_InitFields(void);
extern "C" void FUN_001e5950(int arg0);
extern "C" igMetaObject *igDataPump_GetMetaObject(void);
struct Obj_1e59e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int FUN_001c7600(...);
extern "C" int g_igDataPump_vtable[4];
extern "C" int igDataPump_GetVTable(void);
extern "C" void FUN_001e5ab0(void);
extern "C" CallbackArray *igDataPump_Register(void);
extern "C" void thunk_igDataPump_GetMetaObject(void);
extern "C" int igMetaField_GetOrCreateMetaObject(...);
extern "C" int g_igObject_metaObject[4];
extern "C" void igDataPump_InitFields(void);
extern "C" igMetaObject *igBoolObject_GetMetaObject(void);
struct O { int *vt; char post[12]; };
extern "C" int g_igBoolObject_vtable[4];
extern "C" int igBoolObject_GetVTable(void);
extern "C" void FUN_001e5ce0(void);
extern "C" CallbackArray *igBoolObject_Register(void);
extern "C" void thunk_igBoolObject_GetMetaObject(void);
extern "C" void igBoolObject_InitFields(void);
typedef struct Vec3fList { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } Vec3fList;
extern "C" void FUN_001e5de0(Vec3fList *list, unsigned short *out, float base, float range);
extern "C" void FUN_001e6130(igQuaternionfList *list, short *quantized, float *minimum, float *range);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
class Src { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2);
typedef struct S0 { char pad24[24]; int f18; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
typedef struct S_temp_s0 { char pad4[4]; int f4; } S_temp_s0;
extern "C" void FUN_001e6410(S0 *arg0, void **arg1);
struct Value : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); int offset; };
struct Source { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Value *value(); virtual void select(int); };
struct Sink { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); virtual void d21(); virtual void write(int, int); };
struct FieldDesc { int w0; int w4; int offset; };
struct ValueBinding { char pad[8]; int key; Sink *sink; char pad2[8]; Source *source; };
typedef void (*Notify)(int);
extern "C" int FUN_001e6490(ValueBinding *binding, int selection);
extern "C" void Gap__igDataPump__vfunc_17(igDataPump *pump);
extern "C" void Gap__igDataPump__vfunc_14(void);
extern "C" int FUN_001e6770(int *p);
extern "C" int FUN_001e6780(void *arg0, igObject *object);
typedef struct L { char pad[8]; int count; int pad2; int *data; } L;
typedef struct S { char pad[8]; L *list; } S;
extern "C" int FUN_001e67a0(S *arg0, int arg1);
struct L_1e6820 { char pad[8]; int count; int pad2; int *items; };
struct D { char pad[8]; int f8; };
extern "C" int FUN_001e6820(struct D *arg0, struct L_1e6820 *arg1);
extern "C" int FUN_001e68a0(int arg0, int arg1);
extern "C" int igMatrix44f_PreMultiply(...);
extern "C" int igMatrix44f_Copy(...);
typedef struct Mat { int w[16]; } Mat;
typedef struct Lst { int w0; int w4; int count; int cap; Mat *data; } Lst;
extern "C" int FUN_001e68e0(Lst *arg0, int arg1);
extern "C" int igMatrix44f_Multiply(...);
struct S_1e69e0 { char pad[8]; int f8; int f12; char *f16; };
extern "C" int FUN_001e69e0(struct S_1e69e0 *arg0, int arg1);
struct S1e { int a, b, cnt, d, base; };
extern "C" void FUN_001e6ae0(struct S1e *arg0);
extern "C" void FUN_001e6b00(void *arg0, int arg1);
extern "C" void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed);
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void Gap__igMersenneTwisterRandomNumber__vfunc_13(void **arg0, int flags);
#include <stdio.h>
extern "C" int FUN_0018be80(...);
extern "C" int FUN_001e6d80(int arg0, int *arg1, const char *format);
typedef struct FormattedObject : public igObject { int f8; } FormattedObject;
typedef struct Vector3f { float x, y, z; } Vector3f;
#include "dw4/igStringObj.h"
#include "dw4/softfloat.h"
extern "C" int igStringObj_Format(...);

extern "C" int FUN_001e6de0(int *result, Vector3f *value, const char *format);
struct QuadNamed : public igObject { int name; };
struct Quad { float x, y, z, w; };
struct Tag { };
extern "C" int FUN_001e6f10(int *result, Quad *quad, const char *kind);
extern "C" int text_f_f_f_2[4];
extern "C" int FUN_001e70a0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int FUN_001e71f0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" igMetaObject *Gap__igMersenneTwisterRandomNumber__vfunc_22(void);
extern "C" unsigned int Gap__igMersenneTwisterRandomNumber__vfunc_24(igMersenneTwisterRandomNumber *self);
extern "C" igMetaObject *Gap__igDataPump__vfunc_22(void);
extern "C" igMetaObject *Gap__igBoolObject__vfunc_22(void);
extern "C" igMetaObject *Gap__igDataPumpInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__igDataPumpList__vfunc_22(void);
extern "C" igMetaObject *Gap__igDataPumpManager__vfunc_22(void);
extern "C" igMetaObject *Gap__igFloatObject__vfunc_22(void);
extern "C" igMetaObject *Gap__igIntObject__vfunc_22(void);
extern "C" igMetaObject *Gap__igMatrixObject__vfunc_22(void);
extern "C" igMetaObject *Gap__igMatrixObjectList__vfunc_22(void);
extern "C" igMetaObject *Gap__igNonRefCountedMatrixObjectList__vfunc_22(void);
extern "C" igMetaObject *Gap__igMatrixStack__vfunc_22(void);
extern "C" igMetaObject *Gap__igLongStack__vfunc_22(void);
extern "C" igMetaObject *Gap__igNonRefCountedMatrixObjectList__vfunc_24(void);
extern "C" igMetaObject *Gap__igDataPumpList__vfunc_24(void);
extern "C" igMetaObject *Gap__igMatrixObjectList__vfunc_24(void);
extern "C" void Gap__igLongStack__vfunc_18(igDataList *arg0);
extern "C" void Gap__igMatrixStack__vfunc_18(igDataList *arg0);
extern "C" unsigned int FUN_001e6bc0(igMersenneTwisterRandomNumber *self);
extern "C" void FUN_001e5f00(Vec3fList *list, unsigned short *quantized, float *minimum, float *range);
extern "C" void FUN_001e5fe0(igQuaternionfList *list, short *quantized, float minimum, float range);

#endif

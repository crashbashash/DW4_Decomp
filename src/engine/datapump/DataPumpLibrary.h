#ifndef DW4_DATA_PUMP_LIBRARY_H
#define DW4_DATA_PUMP_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/datapump/igDataPumpInfo.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/datapump/igNonRefCountedObjectStack.h"
#include "dw4/datapump/igRandomNumber.h"


class igMemoryPoolView;
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igUnsignedIntArrayMetaField.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igMetaField.h"
extern "C" char text_value[];

#include "dw4/core/igMetaObject.h"
#include "dw4/core/igRegistry.h"
extern "C" void DataPumpLibrary_MarkRegistered(void);
#include "dw4/core/igMemoryPoolContext.h"
extern "C" igMetaObject *igLongStack_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igLongStack_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int g_igLongStack_vtable[4];
#include "dw4/core/igObjectSystem.h"
extern "C" int igLongStack_GetVTable(void);
extern "C" void igLongStack_EnsureRegistered(void);
#include "dw4/core/igDataLists.h"
#include "dw4/core/internalNonRefCountedObjectList.h"
#include "dw4/core/igLongMetaField.h"
extern "C" CallbackArray *igLongStack_Register(void);
extern "C" void igLongStack_GetMetaObjectFunction(void);
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void igLongStack_InitFields(void);
extern "C" igMetaObject *igRandomNumber_GetMetaObject(void);
extern "C" CallbackArray *igRandomNumber_Register(void);
extern "C" void igRandomNumber_GetMetaObjectFunction(void);
extern "C" void igRandomNumber_SetAbstractProxy(void);
extern "C" void igMersenneTwisterRandomNumber_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void);
extern "C" int g_igNonRefCountedObjectStack_vtable[4];
extern "C" int igNonRefCountedObjectStack_GetVTable(void);
extern "C" void igNonRefCountedObjectStack_EnsureRegistered(void);
extern "C" void igNonRefCountedObjectStack_GetMetaObjectFunction(void);
extern "C" void igNonRefCountedObjectStack_InitFields(void);
extern "C" igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void);
struct Obj_1e45e0 { int *vt; char pad[2508]; };
extern "C" int g_igMersenneTwisterRandomNumber_vtable[4];
extern "C" int igMersenneTwisterRandomNumber_GetVTable(void);
extern "C" void igMersenneTwisterRandomNumber_EnsureRegistered(void);
extern "C" igMetaObject *igRandomNumber_GetPublishedMetaObject(void);
extern "C" CallbackArray *igMersenneTwisterRandomNumber_Register(void);
extern "C" igMetaObject *igRandomNumber_GetPublishedMetaObject(void);
struct F { char pad[52]; int f52; };
extern "C" void igMersenneTwisterRandomNumber_InitFields(void);
extern "C" igMetaObject *igMatrixStack_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMatrixStack_GetMetaObject(void);
extern "C" int g_igMatrixStack_vtable[4];
extern "C" int igMatrixStack_GetVTable(void);
extern "C" void igMatrixStack_EnsureRegistered(void);
extern "C" CallbackArray *igMatrixStack_Register(void);
extern "C" void igMatrixStack_GetMetaObjectFunction(void);
extern "C" void igMatrixStack_InitFields(void);
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void);
extern "C" int g_igNonRefCountedMatrixObjectList_vtable[4];
extern "C" int igNonRefCountedMatrixObjectList_GetVTable(void);
extern "C" void igNonRefCountedMatrixObjectList_EnsureRegistered(void);
#include "dw4/core/igNonRefCountedObjectList.h"
extern "C" CallbackArray *igNonRefCountedMatrixObjectList_Register(void);
extern "C" void igNonRefCountedMatrixObjectList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMatrixObjectList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMatrixObjectList_GetMetaObject(void);
extern "C" int g_igMatrixObjectList_vtable[4];
extern "C" int igMatrixObjectList_GetVTable(void);
extern "C" void igMatrixObjectList_EnsureRegistered(void);
#include "dw4/core/igObjectList.h"
extern "C" CallbackArray *igMatrixObjectList_Register(void);
extern "C" void igMatrixObjectList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMatrixObject_GetMetaObject(void);
struct Obj_1e4ce0 { int *vt; char pad[76]; };
#include "dw4/maths/igMatrix44f.h"
extern "C" int g_igMatrixObject_vtable[4];
extern "C" int igMatrixObject_GetVTable(void);
extern "C" void igMatrixObject_EnsureRegistered(void);
extern "C" CallbackArray *igMatrixObject_Register(void);
extern "C" void igMatrixObject_GetMetaObjectFunction(void);
extern "C" void igMatrixObject_InitFields(void);
struct Obj_1e4e80 { int *vt; char pad[12]; };
extern "C" int g_igIntObject_vtable[4];
extern "C" int igIntObject_GetVTable(void);
extern "C" void igIntObject_EnsureRegistered(void);
extern "C" CallbackArray *igIntObject_Register(void);
extern "C" void igIntObject_GetMetaObjectFunction(void);
extern "C" void igIntObject_InitFields(void);
struct Obj_1e5010 { int *vt; char pad[12]; };
extern "C" int g_igFloatObject_vtable[4];
extern "C" int igFloatObject_GetVTable(void);
extern "C" void igFloatObject_EnsureRegistered(void);
extern "C" CallbackArray *igFloatObject_Register(void);
extern "C" void igFloatObject_GetMetaObjectFunction(void);
extern "C" void igFloatObject_InitFields(void);
extern "C" igMetaObject *igDataPumpManager_GetOrCreateMetaObject(void);
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
extern "C" void igDataPumpManager_EnsureRegistered(void);
extern "C" CallbackArray *igDataPumpManager_Register(void);
extern "C" void igDataPumpManager_GetMetaObjectFunction(void);
extern "C" void igDataPumpManager_InitFields(void);
extern "C" igMetaObject *igDataPumpList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDataPumpList_GetMetaObject(void);
extern "C" int g_igDataPumpList_vtable[4];
extern "C" int igDataPumpList_GetVTable(void);
extern "C" void igDataPumpList_EnsureRegistered(void);
extern "C" CallbackArray *igDataPumpList_Register(void);
extern "C" void igDataPumpList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igDataPumpInterface_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDataPumpInterface_GetMetaObject(void);
extern "C" void igDataPumpInterface_EnsureRegistered(void);
extern "C" CallbackArray *igDataPumpInterface_Register(void);
extern "C" void igDataPumpInterface_GetMetaObjectFunction(void);
extern "C" void igDataPumpInfo_Create(int arg0);
extern "C" igMetaObject *igDataPumpInfo_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDataPumpInfo_GetMetaObject(void);
#include "dw4/core/StringPool.h"
#include "dw4/core/igNamedObject.h"
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
extern "C" void igDataPumpInfo_EnsureRegistered(void);
#include "dw4/core/igInfo.h"
extern "C" CallbackArray *igDataPumpInfo_Register(void);
extern "C" void igDataPumpInfo_GetMetaObjectFunction(void);
extern "C" void igDataPumpInfo_InitFields(void);
extern "C" void igDataPump_Create(int arg0);
extern "C" igMetaObject *igDataPump_GetMetaObject(void);
struct Obj_1e59e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_igDataPump_vtable[4];
extern "C" int igDataPump_GetVTable(void);
extern "C" void igDataPump_EnsureRegistered(void);
extern "C" CallbackArray *igDataPump_Register(void);
extern "C" void igDataPump_GetMetaObjectFunction(void);
extern "C" void igDataPump_InitFields(void);
struct O { int *vt; char post[12]; };
extern "C" int g_igBoolObject_vtable[4];
extern "C" int igBoolObject_GetVTable(void);
extern "C" void igBoolObject_EnsureRegistered(void);
extern "C" CallbackArray *igBoolObject_Register(void);
extern "C" void igBoolObject_GetMetaObjectFunction(void);
extern "C" void igBoolObject_InitFields(void);
typedef struct Vec3fList { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } Vec3fList;
extern "C" void igCompressVec3fListRange(Vec3fList *list, unsigned short *out, float base, float range);

extern "C" void igDataPump_SetDestByFieldName(igDataPump *self, igObjectDispatchView **destObj, const char *destName);
extern "C" void igDataPump_SetDataPumpInterface(igDataPump *self, igObject **dpi);
struct Value : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); int offset; };
struct Source { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Value *value(); virtual void select(long long time); };
struct Sink { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); virtual void d21(); virtual void write(int, int); };
struct FieldDesc { int w0; int w4; int offset; };
struct ValueBinding { char pad[8]; int key; Sink *sink; char pad2[8]; Source *source; };
typedef void (*Notify)(int);
extern "C" int igDataPump_Update(ValueBinding *binding, long long time);
extern "C" void igDataPump_UserPostLoad(igDataPump *pump);
extern "C" void igDataPump_UserPreWrite(void);
#include "dw4/datapump/igDataPumpManager.h"
#include "dw4/datapump/igMatrixStack.h"
extern "C" void igMersenneTwisterRandomNumber_Seed(igMersenneTwisterRandomNumber *self, unsigned int seed);
#include "dw4/datapump/igRandomNumberDispatchView.h"
extern "C" void igMersenneTwisterRandomNumber_resetFields(igMersenneTwisterRandomNumber *self, int flags);
#include <stdio.h>
#include "dw4/datapump/igRegistryValue.h"
#include "dw4/core/igStringRef.h"
#include "dw4/core/igStringObj.h"
#include "dw4/support/softfloat.h"
#include "dw4/datapump/igMatrixObject.h"
#include "dw4/datapump/igBoolObject.h"
#include "dw4/datapump/igFloatObject.h"
#include "dw4/datapump/igIntObject.h"
#include "dw4/datapump/igCompressVec.h"

struct Tag { };
/* igStringObj as the two vector formatters hold it: each smart-pointer instance emits its own destructor. */
struct FormattedObject : public igObject { int buffer; };
struct QuadNamed : public igObject { int name; };
extern "C" igMetaObject *igMersenneTwisterRandomNumber_GetMeta(void);
extern "C" unsigned int igMersenneTwisterRandomNumber_GetNumber(igMersenneTwisterRandomNumber *self);
extern "C" igMetaObject *igDataPump_GetMeta(void);
extern "C" igMetaObject *igBoolObject_GetMeta(void);
extern "C" igMetaObject *igDataPumpInfo_GetMeta(void);
extern "C" igMetaObject *igDataPumpList_GetMeta(void);
extern "C" igMetaObject *igDataPumpManager_GetMeta(void);
extern "C" igMetaObject *igFloatObject_GetMeta(void);
extern "C" igMetaObject *igIntObject_GetMeta(void);
extern "C" igMetaObject *igMatrixObject_GetMeta(void);
extern "C" igMetaObject *igMatrixObjectList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetMeta(void);
extern "C" igMetaObject *igMatrixStack_GetMeta(void);
extern "C" igMetaObject *igLongStack_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetElementMeta(void);
extern "C" igMetaObject *igDataPumpList_GetElementMeta(void);
extern "C" igMetaObject *igMatrixObjectList_GetElementMeta(void);
extern "C" void igLongStack_TrimCapacity(igDataList *arg0);
extern "C" void igMatrixStack_TrimCapacity(igDataList *arg0);
extern "C" unsigned int igMersenneTwisterRandomNumber_GetNumberNonVirtual(igMersenneTwisterRandomNumber *self);

extern "C" void igCompressVec4fListRange(igQuaternionfList *list, short *quantized, float minimum, float range);

#endif

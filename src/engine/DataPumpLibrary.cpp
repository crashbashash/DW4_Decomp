#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int igMetaObject_RunStaticInit(...);
extern "C" int FUN_003065f0(...);
extern "C" int FUN_003066b0(...);
extern "C" int FUN_00306770(...);
extern "C" int FUN_00306e50(...);
extern "C" unsigned char g_DataPumpLibrary_registered;
extern "C" void DataPumpLibrary_MarkRegistered(void);
extern "C" int igMetaObject_Create(int);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int DAT_00562b60[4];
extern "C" int DAT_00587040[4];
extern "C" int FUN_001e4010(void);
extern "C" igMetaObject *g_igLongStack_metaObject[4];
extern "C" igMetaObject *igLongStack_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int igObject_InitHeader(...);
extern "C" int DAT_0052bdb0[4];
extern "C" char *DAT_00586dc8[4];
extern "C" int igLongStack_GetVTable(void);
extern "C" void FUN_001e40f0(void);
extern "C" char igDataList_GetPublishedMetaObject[];
extern "C" char igDataList_Register[];
extern "C" char igLongStack_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" int igLongStack_InitFields_001e4180[4];
extern "C" void igLongStack_Register(void);
extern "C" void thunk_igLongStack_GetMetaObject(void);
extern "C" int FUN_002c1c70(...);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" igObject *igMetaObject_FindFieldByName(...);
extern "C" int DAT_004e48c8[4];
extern "C" int DAT_00562b68[4];
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void FUN_001e4180(void);
extern "C" int DAT_00562b70[4];
extern "C" int FUN_001e4240(void);
extern "C" igMetaObject *g_igRandomNumber_metaObject[4];
extern "C" igMetaObject *igRandomNumber_GetMetaObject(void);
extern "C" void FUN_001e42e0(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char igRandomNumber_className[];
extern "C" int igRandomNumber_InitFields_001e4370[4];
extern "C" void igRandomNumber_Register(void);
extern "C" void thunk_igRandomNumber_GetMetaObject(void);
extern "C" void FUN_001e4370(void);
extern "C" void thunk_igMersenneTwisterRandomNumber_GetMetaObject(void);
extern "C" igMetaObject *g_igNonRefCountedObjectStack_metaObject[4];
extern "C" igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void);
extern "C" int DAT_00524fe0[4];
extern "C" int igNonRefCountedObjectStack_GetVTable(void);
extern "C" void FUN_001e4430(void);
extern "C" char igNonRefCountedObjectStack_className[];
extern "C" int igNonRefCountedObjectStack_InitFields_001e44c0[4];
extern "C" void igNonRefCountedObjectStack_Register(void);
extern "C" void thunk_igNonRefCountedObjectStack_GetMetaObject(void);
extern "C" int igObjectRefMetaField_GetDefaultDescriptor(...);
extern "C" void * DAT_00562b78[4];
extern "C" int DAT_00562b80[4];
extern "C" void FUN_001e44c0(void);
extern "C" igMetaObject *g_igMersenneTwisterRandomNumber_metaObject[4];
extern "C" igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void);
struct Obj_1e45e0 { int *vt; char pad[2508]; };
extern "C" int DAT_0052b8e0[4];
extern "C" int igMersenneTwisterRandomNumber_GetVTable(void);
extern "C" void FUN_001e4620(void);
extern "C" char igRandomNumber_GetPublishedMetaObject[];
extern "C" char igMersenneTwisterRandomNumber_className[];
extern "C" void igMersenneTwisterRandomNumber_Register(void);
extern "C" int FUN_001e46a0(void);
struct F { char pad[52]; int f52; };
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_0048daf0[4];
extern "C" int DAT_0048daf8[4];
extern "C" int DAT_0048db00[4];
extern "C" int DAT_0048db08[4];
extern "C" int DAT_00562b88[4];
extern "C" void igMersenneTwisterRandomNumber_InitFields(void);
extern "C" int DAT_00562ba0[4];
extern "C" int FUN_001e4740(void);
extern "C" igMetaObject *g_igMatrixStack_metaObject[4];
extern "C" igMetaObject *igMatrixStack_GetMetaObject(void);
extern "C" int DAT_0052bd50[4];
extern "C" int igMatrixStack_GetVTable(void);
extern "C" void FUN_001e4820(void);
extern "C" char igMatrixStack_className[];
extern "C" int igMatrixStack_InitFields_001e48b0[4];
extern "C" void igMatrixStack_Register(void);
extern "C" void thunk_igMatrixStack_GetMetaObject(void);
extern "C" int FUN_001888e0(...);
extern "C" int DAT_00562ba8[4];
extern "C" void FUN_001e48b0(void);
extern "C" int DAT_00562bb0[4];
extern "C" int FUN_001e4970(void);
extern "C" igMetaObject *g_igNonRefCountedMatrixObjectList_metaObject[4];
extern "C" igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void);
extern "C" int DAT_0052bce0[4];
extern "C" int igNonRefCountedMatrixObjectList_GetVTable(void);
extern "C" void FUN_001e4a50(void);
extern "C" char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern "C" char igNonRefCountedObjectList_Register[];
extern "C" char g_igNonRefCountedMatrixObjectList_callbackList[];
extern "C" char igNonRefCountedMatrixObjectList_className[];
extern "C" void igNonRefCountedMatrixObjectList_Register(void);
extern "C" void thunk_igNonRefCountedMatrixObjectList_GetMetaObject(void);
extern "C" int DAT_00562bb8[4];
extern "C" int FUN_001e4ae0(void);
extern "C" igMetaObject *g_igMatrixObjectList_metaObject[4];
extern "C" igMetaObject *igMatrixObjectList_GetMetaObject(void);
extern "C" int DAT_0052bc70[4];
extern "C" int igMatrixObjectList_GetVTable(void);
extern "C" void FUN_001e4bc0(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igMatrixObjectList_callbackList[];
extern "C" char igMatrixObjectList_className[];
extern "C" void igMatrixObjectList_Register(void);
extern "C" void thunk_igMatrixObjectList_GetMetaObject(void);
extern "C" int igMetaObject_CreateInstance(...);
extern "C" int DAT_00562bc0[4];
extern "C" void FUN_001e4c50(int arg0);
extern "C" igMetaObject *g_igMatrixObject_metaObject[4];
extern "C" igMetaObject *igMatrixObject_GetMetaObject(void);
struct Obj_1e4ce0 { int *vt; char pad[76]; };
extern "C" int igMatrix44f_SetIdentity(char *);
extern "C" int DAT_0052bc10[4];
extern "C" int igMatrixObject_GetVTable(void);
extern "C" void FUN_001e4d30(void);
extern "C" char igMatrixObject_className[];
extern "C" void igMatrixObject_Register(void);
extern "C" void thunk_igMatrixObject_GetMetaObject(void);
extern "C" int DAT_0048db20[4];
extern "C" int DAT_0048db28[4];
extern "C" int DAT_0048db30[4];
extern "C" int DAT_0048db38[4];
extern "C" void igMatrixObject_InitFields(void);
extern "C" igMetaObject *g_igIntObject_metaObject[4];
extern "C" igMetaObject *igIntObject_GetMetaObject(void);
struct Obj_1e4e80 { int *vt; char pad[12]; };
extern "C" int DAT_0052bbb0[4];
extern "C" int igIntObject_GetVTable(void);
extern "C" void FUN_001e4ec0(void);
extern "C" char igIntObject_className[];
extern "C" void igIntObject_Register(void);
extern "C" void thunk_igIntObject_GetMetaObject(void);
extern "C" int DAT_0048db40[4];
extern "C" int DAT_0048db48[4];
extern "C" int DAT_0048db50[4];
extern "C" int DAT_0048db58[4];
extern "C" int DAT_00562bd0[4];
extern "C" void igIntObject_InitFields(void);
extern "C" igMetaObject *g_igFloatObject_metaObject[4];
extern "C" igMetaObject *igFloatObject_GetMetaObject(void);
struct Obj_1e5010 { int *vt; char pad[12]; };
extern "C" int DAT_0052bb50[4];
extern "C" int igFloatObject_GetVTable(void);
extern "C" void FUN_001e5050(void);
extern "C" char igFloatObject_className[];
extern "C" void igFloatObject_Register(void);
extern "C" void thunk_igFloatObject_GetMetaObject(void);
extern "C" int DAT_0048db60[4];
extern "C" int DAT_0048db68[4];
extern "C" int DAT_0048db70[4];
extern "C" int DAT_0048db78[4];
extern "C" int DAT_00562be0[4];
extern "C" void igFloatObject_InitFields(void);
extern "C" int DAT_00562bf0[4];
extern "C" int FUN_001e5150(void);
extern "C" igMetaObject *g_igDataPumpManager_metaObject[4];
extern "C" igMetaObject *igDataPumpManager_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int DAT_0052baf0[4];
struct Obj_1e51f0 {
    int *vt; int w0[1]; T *ref; int w1[1]; 
    inline void release() {
        T **self = &ref;
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
extern "C" int igDataPumpManager_GetVTable(void);
extern "C" void FUN_001e5280(void);
extern "C" char g_igDataPumpManager_callbackList[];
extern "C" char igDataPumpManager_className[];
extern "C" void igDataPumpManager_Register(void);
extern "C" void thunk_igDataPumpManager_GetMetaObject(void);
extern "C" int DAT_0048db88[4];
extern "C" int DAT_0048db90[4];
extern "C" int DAT_0048db98[4];
extern "C" int DAT_0048dba0[4];
extern "C" void igDataPumpManager_InitFields(void);
extern "C" int DAT_00562c00[4];
extern "C" int FUN_001e53c0(void);
extern "C" igMetaObject *g_igDataPumpList_metaObject[4];
extern "C" igMetaObject *igDataPumpList_GetMetaObject(void);
extern "C" int DAT_0052ba80[4];
extern "C" int igDataPumpList_GetVTable(void);
extern "C" void FUN_001e54a0(void);
extern "C" char g_igDataPumpList_callbackList[];
extern "C" char igDataPumpList_className[];
extern "C" void igDataPumpList_Register(void);
extern "C" void thunk_igDataPumpList_GetMetaObject(void);
extern "C" int DAT_00562c08[4];
extern "C" int FUN_001e5530(void);
extern "C" igMetaObject *g_igDataPumpInterface_metaObject[4];
extern "C" igMetaObject *igDataPumpInterface_GetMetaObject(void);
extern "C" void FUN_001e55d0(void);
extern "C" char igDataPumpInterface_className[];
extern "C" void igDataPumpInterface_Register(void);
extern "C" void thunk_igDataPumpInterface_GetMetaObject(void);
extern "C" void FUN_001e5650(int arg0);
extern "C" int DAT_00562c10[4];
extern "C" int FUN_001e5690(void);
extern "C" igMetaObject *g_igDataPumpInfo_metaObject[4];
extern "C" igMetaObject *igDataPumpInfo_GetMetaObject(void);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int DAT_00524950[4];
extern "C" int DAT_0052ba10[4];
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
                    StringChunk_ReleaseHeader(*a1, a1);
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
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" int igDataPumpInfo_GetVTable(void);
extern "C" void FUN_001e5810(void);
extern "C" char igInfo_GetPublishedMetaObject[];
extern "C" char igInfo_Register[];
extern "C" char g_igDataPumpInfo_callbackList[];
extern "C" char igDataPumpInfo_className[];
extern "C" void igDataPumpInfo_Register(void);
extern "C" void thunk_igDataPumpInfo_GetMetaObject(void);
extern "C" int DAT_0048dbb8[4];
extern "C" int DAT_0048dbc0[4];
extern "C" int DAT_0048dbc8[4];
extern "C" int DAT_0048dbd0[4];
extern "C" void igDataPumpInfo_InitFields(void);
extern "C" void FUN_001e5950(int arg0);
extern "C" igMetaObject *g_igDataPump_metaObject[4];
extern "C" igMetaObject *igDataPump_GetMetaObject(void);
struct Obj_1e59e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int FUN_0014ec50(...);
extern "C" int FUN_001c7600(...);
extern "C" int ObjectRef_Destruct_001363f0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int DAT_0052b950[4];
extern "C" int igDataPump_GetVTable(void);
extern "C" void FUN_001e5ab0(void);
extern "C" char g_igDataPump_callbackList[];
extern "C" char igDataPump_className[];
extern "C" void igDataPump_Register(void);
extern "C" void thunk_igDataPump_GetMetaObject(void);
extern "C" int FUN_002beca0(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int DAT_0048dbf0[4];
extern "C" int DAT_0048dc10[4];
extern "C" int DAT_0048dc30[4];
extern "C" int DAT_0048dc50[4];
extern "C" int DAT_00562c20[4];
extern "C" int DAT_00587198[4];
extern "C" void igDataPump_InitFields(void);
extern "C" igMetaObject *g_igBoolObject_metaObject[4];
extern "C" igMetaObject *igBoolObject_GetMetaObject(void);
struct O { int *vt; char post[12]; };
extern "C" int DAT_0052b9b0[4];
extern "C" int igBoolObject_GetVTable(void);
extern "C" void FUN_001e5ce0(void);
extern "C" char igBoolObject_className[];
extern "C" void igBoolObject_Register(void);
extern "C" void thunk_igBoolObject_GetMetaObject(void);
extern "C" int DAT_0048dc68[4];
extern "C" int DAT_0048dc70[4];
extern "C" int DAT_0048dc78[4];
extern "C" int DAT_0048dc80[4];
extern "C" int DAT_00562c50[4];
extern "C" void igBoolObject_InitFields(void);
typedef struct Vec3fList { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } Vec3fList;
extern "C" void FUN_001e5de0(Vec3fList *list, unsigned short *out, float base, float range);
extern "C" void FUN_001e6130(igQuaternionfList *list, short *quantized, float *minimum, float *range);
extern "C" int FUN_002eb010(int n);
extern "C" int StringPool_Construct(int p);
extern "C" int StringPool_Intern(int pool, int s);
extern "C" int DAT_00586f20[4];
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
class Src { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2);
typedef struct S0 { char pad24[24]; int f18; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
typedef struct S_temp_s0 { char pad4[4]; int f4; } S_temp_s0;
extern "C" void FUN_001e6410(S0 *arg0, void **arg1);
extern "C" int FUN_002fe290(int, int);
extern "C" int DAT_004e4aa0[4];
extern "C" void *DAT_00562c60[4];
extern "C" int DAT_00585cc8[4];
struct Value : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); int offset; };
struct Source { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Value *value(); virtual void select(int); };
struct Sink { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int type(); virtual void d21(); virtual void write(int, int); };
struct FieldDesc { int w0; int w4; int offset; };
struct ValueBinding { char pad[8]; int key; Sink *sink; char pad2[8]; Source *source; };
typedef void (*Notify)(int);
extern "C" int FUN_001e6490(ValueBinding *binding, int selection);
extern "C" igObject *igObjectSystem_FindMetaByNameDefault(int);
extern "C" void Gap__igDataPump__vfunc_17(igDataPump *pump);
extern "C" void Gap__igDataPump__vfunc_14(void);
extern "C" int FUN_001e6770(int *p);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int FUN_001e6780(void *arg0);
typedef struct L { char pad[8]; int count; int pad2; int *data; } L;
typedef struct S { char pad[8]; L *list; } S;
extern "C" int FUN_001e67a0(S *arg0, int arg1);
struct L_1e6820 { char pad[8]; int count; int pad2; int *items; };
struct D { char pad[8]; int f8; };
extern "C" int FUN_001e6820(struct D *arg0, struct L_1e6820 *arg1);
extern "C" int FUN_001e68a0(int arg0, int arg1);
extern "C" int FUN_001906d0(...);
extern "C" int List_Resize(...);
extern "C" int Matrix44_Copy(...);
typedef struct Mat { int w[16]; } Mat;
typedef struct Lst { int w0; int w4; int count; int cap; Mat *data; } Lst;
extern "C" int FUN_001e68e0(Lst *arg0, int arg1);
extern "C" int FUN_001904f0(...);
struct S_1e69e0 { char pad[8]; int f8; int f12; char *f16; };
extern "C" int FUN_001e69e0(struct S_1e69e0 *arg0, int arg1);
struct S1e { int a, b, cnt, d, base; };
extern "C" void FUN_001e6ae0(struct S1e *arg0);
extern "C" void FUN_001e6b00(void *arg0, int arg1);
extern "C" void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed);
extern "C" int Gap__Core__igObject__vfunc_11(...);
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void Gap__igMersenneTwisterRandomNumber__vfunc_13(void **arg0);
extern "C" int sscanf(...);
extern "C" int FUN_0018be80(...);
extern "C" int FUN_001e6d30(int arg0, int *arg1, int arg2);
extern "C" int FUN_001e6d80(int arg0, int *arg1, int arg2);
typedef struct FormattedObject : public igObject { int f8; } FormattedObject;
typedef struct Vector3f { float x, y, z; } Vector3f;
extern "C" igObject *FUN_002b9500(int);
extern "C" int fptodp(float);
extern "C" int FUN_0030b7e0(...);
extern "C" int DAT_004c22f0[16];

extern "C" int FUN_001e6de0(int *result, Vector3f *value, int *format);
struct QuadNamed : public igObject { int name; };
struct Quad { float x, y, z, w; };
struct Tag { };
extern "C" int FUN_001e6f10(int *result, Quad *quad, int *kind);
extern "C" int thunk_FUN_003065f0();
extern "C" int thunk_FUN_003066b0();
extern "C" int thunk_FUN_00306770();
extern "C" int thunk_FUN_00306910();
extern "C" int thunk_FUN_00306e50();
extern "C" int FUN_00306910(...);
extern "C" int DAT_004e4ac0[4];
extern "C" int DAT_004e4ad0[4];
extern "C" int FUN_001e70a0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int DAT_004e4ae8[4];
extern "C" int DAT_004e4b00[4];
extern "C" int FUN_001e71f0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int Gap__igMersenneTwisterRandomNumber__vfunc_22(void);
extern "C" unsigned int Gap__igMersenneTwisterRandomNumber__vfunc_24(igMersenneTwisterRandomNumber *self);
extern "C" int Gap__igDataPump__vfunc_22(void);
extern "C" int Gap__igBoolObject__vfunc_22(void);
extern "C" int Gap__igDataPumpInfo__vfunc_22(void);
extern "C" int Gap__igDataPumpList__vfunc_22(void);
extern "C" int Gap__igDataPumpManager__vfunc_22(void);
extern "C" int Gap__igFloatObject__vfunc_22(void);
extern "C" int Gap__igIntObject__vfunc_22(void);
extern "C" int Gap__igMatrixObject__vfunc_22(void);
extern "C" int Gap__igMatrixObjectList__vfunc_22(void);
extern "C" int Gap__igNonRefCountedMatrixObjectList__vfunc_22(void);
extern "C" int Gap__igMatrixStack__vfunc_22(void);
extern "C" int Gap__igLongStack__vfunc_22(void);
extern "C" int Gap__igNonRefCountedMatrixObjectList__vfunc_24(void);
extern "C" int Gap__igDataPumpList__vfunc_24(void);
extern "C" int Gap__igMatrixObjectList__vfunc_24(void);
extern "C" int List_Reserve(...);
extern "C" void Gap__igLongStack__vfunc_18(igDataList *arg0);
extern "C" void Gap__igMatrixStack__vfunc_18(igDataList *arg0);
extern "C" unsigned int FUN_001e6bc0(igMersenneTwisterRandomNumber *self);
extern "C" void FUN_001e5f00(Vec3fList *list, unsigned short *quantized, float *minimum, float *range);
extern "C" void FUN_001e5fe0(igQuaternionfList *list, short *quantized, float minimum, float range);

void DataPumpLibrary_MarkRegistered(void) {
    if (g_DataPumpLibrary_registered == 0) {
        g_DataPumpLibrary_registered = 1;
    }
}

int FUN_001e4010(void) {
    if (DAT_00562b60[0] == 0) {
        DAT_00562b60[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562b60[0];
}

igMetaObject *igLongStack_GetMetaObject(void)
{
    igMetaObject *g = g_igLongStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e40f0();
    return g_igLongStack_metaObject[0];
}

int igLongStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bdb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e40f0(void)
{
    igMetaObject_RunStaticInit(igLongStack_Register);
}

void igLongStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongStack_GetMetaObject,
        igLongStack_className,
        0x14, /* instance size */
        igLongStack_GetVTable,
        &igLongStack_InitFields_001e4180[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLongStack_GetMetaObject(void) {
    igLongStack_GetMetaObject();
}

void FUN_001e4180(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00562b60[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e48c8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c1c70();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562b68[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

int FUN_001e4240(void) {
    if (DAT_00562b70[0] == 0) {
        DAT_00562b70[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562b70[0];
}

igMetaObject *igRandomNumber_GetMetaObject(void)
{
    igMetaObject *g = g_igRandomNumber_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e42e0();
    return g_igRandomNumber_metaObject[0];
}

void FUN_001e42e0(void)
{
    igMetaObject_RunStaticInit(igRandomNumber_Register);
}

void igRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRandomNumber_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRandomNumber_GetMetaObject,
        igRandomNumber_className,
        8, /* instance size */
        0,
        &igRandomNumber_InitFields_001e4370[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRandomNumber_GetMetaObject(void) {
    igRandomNumber_GetMetaObject();
}

void FUN_001e4370(void) {
    *(int *)((char *)(DAT_00562b70[0]) + 60) = (int)(&thunk_igMersenneTwisterRandomNumber_GetMetaObject);
}

void thunk_igMersenneTwisterRandomNumber_GetMetaObject(void) {
    igMersenneTwisterRandomNumber_GetMetaObject();
}

igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4430();
    return g_igNonRefCountedObjectStack_metaObject[0];
}

int igNonRefCountedObjectStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524fe0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4430(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedObjectStack_Register);
}

void igNonRefCountedObjectStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedObjectStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igNonRefCountedObjectStack_GetMetaObject,
        igNonRefCountedObjectStack_className,
        0x14, /* instance size */
        igNonRefCountedObjectStack_GetVTable,
        &igNonRefCountedObjectStack_InitFields_001e44c0[0], /* Field adder. */
        0,                                                  /* extra callback-vector item (none) */
        0                                                   /* zero-terminated callback-vector item list (none) */
    );
}

void thunk_igNonRefCountedObjectStack_GetMetaObject(void) {
    igNonRefCountedObjectStack_GetMetaObject();
}

void FUN_001e44c0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00562b78[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e48c8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igObjectRefMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(char *)((char *)(temp_s0) + 66) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562b80[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

igMetaObject *igMersenneTwisterRandomNumber_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMersenneTwisterRandomNumber_metaObject[0] != 0) {
        ready = (g_igMersenneTwisterRandomNumber_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001e4620();
done:
    return g_igMersenneTwisterRandomNumber_metaObject[0];
}

int igMersenneTwisterRandomNumber_GetVTable(void) {
    struct Obj_1e45e0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b8e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4620(void)
{
    igMetaObject_RunStaticInit(igMersenneTwisterRandomNumber_Register);
}

void igMersenneTwisterRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMersenneTwisterRandomNumber_metaObject,
        igRandomNumber_Register,
        igRandomNumber_GetPublishedMetaObject,
        thunk_igMersenneTwisterRandomNumber_GetMetaObject,
        igMersenneTwisterRandomNumber_className,
        0x9CC, /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,
        &igMersenneTwisterRandomNumber_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_001e46a0(void) {
    return DAT_00562b70[0];
}

void igMersenneTwisterRandomNumber_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = DAT_00562b88[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048daf0[0], 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f52 = 0x270;
    igMetaObject_NameFields(temp_s0, &DAT_0048daf8[0], &DAT_0048db00[0], &DAT_0048db08[0], temp_s1);
}

int FUN_001e4740(void) {
    if (DAT_00562ba0[0] == 0) {
        DAT_00562ba0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562ba0[0];
}

igMetaObject *igMatrixStack_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4820();
    return g_igMatrixStack_metaObject[0];
}

int igMatrixStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bd50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4820(void)
{
    igMetaObject_RunStaticInit(igMatrixStack_Register);
}

void igMatrixStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrixStack_GetMetaObject,
        igMatrixStack_className,
        0x14, /* instance size */
        igMatrixStack_GetVTable,
        &igMatrixStack_InitFields_001e48b0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixStack_GetMetaObject(void) {
    igMatrixStack_GetMetaObject();
}

void FUN_001e48b0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00562ba0[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e48c8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_001888e0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562ba8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

int FUN_001e4970(void) {
    if (DAT_00562bb0[0] == 0) {
        DAT_00562bb0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562bb0[0];
}

igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4a50();
    return g_igNonRefCountedMatrixObjectList_metaObject[0];
}

int igNonRefCountedMatrixObjectList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bce0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4a50(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedMatrixObjectList_Register);
}

void igNonRefCountedMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedMatrixObjectList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,
        igNonRefCountedMatrixObjectList_className,
        0x14, /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedMatrixObjectList_GetMetaObject(void) {
    igNonRefCountedMatrixObjectList_GetMetaObject();
}

int FUN_001e4ae0(void) {
    if (DAT_00562bb8[0] == 0) {
        DAT_00562bb8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562bb8[0];
}

igMetaObject *igMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4bc0();
    return g_igMatrixObjectList_metaObject[0];
}

int igMatrixObjectList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052bc70[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_001e4bc0(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectList_Register);
}

void igMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMatrixObjectList_GetMetaObject,
        igMatrixObjectList_className,
        0x14, /* instance size */
        igMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igMatrixObjectList_GetMetaObject(void) {
    igMatrixObjectList_GetMetaObject();
}

void FUN_001e4c50(int arg0) {
    FUN_001e4d30();
    igMetaObject_CreateInstance(DAT_00562bc0[0], arg0);
}

igMetaObject *igMatrixObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4d30();
    return g_igMatrixObject_metaObject[0];
}

int igMatrixObject_GetVTable(void) {
    struct Obj_1e4ce0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bc10[0];
    igMatrix44f_SetIdentity(obj.pad + 4);
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4d30(void)
{
    igMetaObject_RunStaticInit(igMatrixObject_Register);
}

void igMatrixObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMatrixObject_GetMetaObject,
        igMatrixObject_className,
        0x48, /* instance size */
        igMatrixObject_GetVTable,
        &igMatrixObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixObject_GetMetaObject(void) {
    igMatrixObject_GetMetaObject();
}

void igMatrixObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bc0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db20[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db28[0], &DAT_0048db30[0], &DAT_0048db38[0], temp_s1);
}

igMetaObject *igIntObject_GetMetaObject(void)
{
    igMetaObject *g = g_igIntObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4ec0();
    return g_igIntObject_metaObject[0];
}

int igIntObject_GetVTable(void) {
    struct Obj_1e4e80 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bbb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4ec0(void)
{
    igMetaObject_RunStaticInit(igIntObject_Register);
}

void igIntObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIntObject_GetMetaObject,
        igIntObject_className,
        0xC, /* instance size */
        igIntObject_GetVTable,
        &igIntObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIntObject_GetMetaObject(void) {
    igIntObject_GetMetaObject();
}

void igIntObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db40[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db48[0], &DAT_0048db50[0], &DAT_0048db58[0], temp_s1);
}

igMetaObject *igFloatObject_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5050();
    return g_igFloatObject_metaObject[0];
}

int igFloatObject_GetVTable(void) {
    struct Obj_1e5010 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bb50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e5050(void)
{
    igMetaObject_RunStaticInit(igFloatObject_Register);
}

void igFloatObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFloatObject_GetMetaObject,
        igFloatObject_className,
        0xC, /* instance size */
        igFloatObject_GetVTable,
        &igFloatObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFloatObject_GetMetaObject(void) {
    igFloatObject_GetMetaObject();
}

void igFloatObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562be0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db68[0], &DAT_0048db70[0], &DAT_0048db78[0], temp_s1);
}

int FUN_001e5150(void) {
    if (DAT_00562bf0[0] == 0) {
        DAT_00562bf0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562bf0[0];
}

igMetaObject *igDataPumpManager_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5280();
    return g_igDataPumpManager_metaObject[0];
}

int igDataPumpManager_GetVTable(void) {
    Obj_1e51f0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052baf0[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052baf0[0];
    obj.release();
    return r;
}

void FUN_001e5280(void)
{
    igMetaObject_RunStaticInit(igDataPumpManager_Register);
}

void igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpManager_GetMetaObject,
        igDataPumpManager_className,
        0xC, /* instance size */
        igDataPumpManager_GetVTable,
        &igDataPumpManager_InitFields,
        0, /* extra callback item */
        g_igDataPumpManager_callbackList /* callback list */
    );
}

void thunk_igDataPumpManager_GetMetaObject(void) {
    igDataPumpManager_GetMetaObject();
}

void igDataPumpManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bf0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db88[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e53c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048db90[0], &DAT_0048db98[0], &DAT_0048dba0[0], temp_s2);
}

int FUN_001e53c0(void) {
    if (DAT_00562c00[0] == 0) {
        DAT_00562c00[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562c00[0];
}

igMetaObject *igDataPumpList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e54a0();
    return g_igDataPumpList_metaObject[0];
}

int igDataPumpList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ba80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e54a0(void)
{
    igMetaObject_RunStaticInit(igDataPumpList_Register);
}

void igDataPumpList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDataPumpList_GetMetaObject,
        igDataPumpList_className,
        0x14, /* instance size */
        igDataPumpList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDataPumpList_callbackList /* callback list */
    );
}

void thunk_igDataPumpList_GetMetaObject(void) {
    igDataPumpList_GetMetaObject();
}

int FUN_001e5530(void) {
    if (DAT_00562c08[0] == 0) {
        DAT_00562c08[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562c08[0];
}

igMetaObject *igDataPumpInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e55d0();
    return g_igDataPumpInterface_metaObject[0];
}

void FUN_001e55d0(void)
{
    igMetaObject_RunStaticInit(igDataPumpInterface_Register);
}

void igDataPumpInterface_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDataPumpInterface_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpInterface_GetMetaObject,
        igDataPumpInterface_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDataPumpInterface_GetMetaObject(void) {
    igDataPumpInterface_GetMetaObject();
}

void FUN_001e5650(int arg0) {
    FUN_001e5810();
    igMetaObject_CreateInstance(*(int *)0x562C10, arg0);
}

int FUN_001e5690(void) {
    if (DAT_00562c10[0] == 0) {
        DAT_00562c10[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562c10[0];
}

igMetaObject *igDataPumpInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5810();
    return g_igDataPumpInfo_metaObject[0];
}

int igDataPumpInfo_GetVTable(void) {
    Obj_1e5730 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_0052ba10[0];
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052ba10[0];
    obj.rel4();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}

void FUN_001e5810(void)
{
    igMetaObject_RunStaticInit(igDataPumpInfo_Register);
}

void igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igDataPumpInfo_GetMetaObject,
        igDataPumpInfo_className,
        0x18, /* instance size */
        igDataPumpInfo_GetVTable,
        &igDataPumpInfo_InitFields,
        0, /* extra callback item */
        g_igDataPumpInfo_callbackList /* callback list */
    );
}

void thunk_igDataPumpInfo_GetMetaObject(void) {
    igDataPumpInfo_GetMetaObject();
}

void igDataPumpInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dbb8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e53c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_0048dbc0[0], &DAT_0048dbc8[0], &DAT_0048dbd0[0], temp_s2);
}

void FUN_001e5950(int arg0) {
    FUN_001e5ab0();
    igMetaObject_CreateInstance(*(int *)0x562C20, arg0);
}

igMetaObject *igDataPump_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPump_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ab0();
    return g_igDataPump_metaObject[0];
}

int igDataPump_GetVTable(void) {
    struct Obj_1e59e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b950[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052b950[0];
    FUN_001c7600(&obj.w6, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    StringRef_Destruct_00130720(&obj.w4, -1);
    FUN_0014ec50(&obj.w3, -1);
    ObjectRef_Destruct_001363f0(&obj.w2, -1);
    return t;
}

void FUN_001e5ab0(void)
{
    igMetaObject_RunStaticInit(igDataPump_Register);
}

void igDataPump_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPump_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPump_GetMetaObject,
        igDataPump_className,
        0x1C, /* instance size */
        igDataPump_GetVTable,
        &igDataPump_InitFields,
        0, /* extra callback item */
        g_igDataPump_callbackList /* callback list */
    );
}

void thunk_igDataPump_GetMetaObject(void) {
    igDataPump_GetMetaObject();
}

void igDataPump_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c20[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dbf0[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_v0) + 56) = (int)((int) DAT_00587198[0]);
    *(char *)((char *)(temp_v0) + 52) = 1;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1) + 56) = FUN_002beca0();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_001e5530();
    igMetaObject_NameFields(temp_s0, &DAT_0048dc10[0], &DAT_0048dc30[0], &DAT_0048dc50[0], temp_s2);
}

igMetaObject *igBoolObject_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ce0();
    return g_igBoolObject_metaObject[0];
}

int igBoolObject_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_0052b9b0;
    return *(int *)((char *)&o.vt + *(int *)(DAT_00586dc8[0] + 916));
}

void FUN_001e5ce0(void)
{
    igMetaObject_RunStaticInit(igBoolObject_Register);
}

void igBoolObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoolObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoolObject_GetMetaObject,
        igBoolObject_className,
        0xC, /* instance size */
        igBoolObject_GetVTable,
        &igBoolObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoolObject_GetMetaObject(void) {
    igBoolObject_GetMetaObject();
}

void igBoolObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dc68[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048dc70[0], &DAT_0048dc78[0], &DAT_0048dc80[0], temp_s1);
}

/* matching construct: declaration-order sweep — v, scale, count, i order */
void FUN_001e5de0(Vec3fList *list, unsigned short *out, float base, float range) {
    float *v;
    float scale;
    int count;
    int i;
    float x;
    float y;
    float z;

    count = list->_count;
    scale = 65535 / range;
    for (i = 0; i < count; i++) {
        v = list->_data[i];
        x = v[0];
        y = v[1];
        z = v[2];
        *out++ = (unsigned int)(scale * (x - base));
        *out++ = (unsigned int)(scale * (y - base));
        *out++ = (unsigned int)(scale * (z - base));
    }
}

static inline void extend(float value, float *minimum, float *maximum) {
    if (value < *minimum) {
        *minimum = value;
    } else if (!(value <= *maximum)) {
        *maximum = value;
    }
}

void FUN_001e5f00(Vec3fList *list, unsigned short *quantized, float *minimum, float *range) {
    int i;
    int count;
    float maximum;
    const float *v;
    float y;
    float z;
    float x;

    count = list->_count;
    maximum = *minimum = list->_data[0][0];
    for (i = 0; i < count; i++) {
        v = list->_data[i];
        x = v[0];
        y = v[1];
        z = v[2];
        extend(x, minimum, &maximum);
        extend(y, minimum, &maximum);
        extend(z, minimum, &maximum);
    }
    *range = maximum - *minimum;
    FUN_001e5de0(list, quantized, *minimum, *range);
}

void FUN_001e5fe0(igQuaternionfList *list, short *quantized, float minimum, float range) {
    const float *q;
    float scale;
    int count;
    int i;
    float x;
    float y;
    float z;
    float w;

    count = list->_count;
    scale = 65535 / range;
    for (i = 0; i < count; i++) {
        q = (float *)list->_data + i * 4;
        x = q[0];
        y = q[1];
        z = q[2];
        w = q[3];
        *quantized++ = (unsigned int)(scale * (x - minimum));
        *quantized++ = (unsigned int)(scale * (y - minimum));
        *quantized++ = (unsigned int)(scale * (z - minimum));
        *quantized++ = (unsigned int)(scale * (w - minimum));
    }
}

void FUN_001e6130(igQuaternionfList *list, short *quantized, float *minimum, float *range) {
    int i;
    int count;
    float maximum;
    const float *q;
    float y;
    float z;
    float w;
    float x;

    count = list->_count;
    maximum = *minimum = *(float *)list->_data;
    for (i = 0; i < count; i++) {
        q = (float *)list->_data + i * 4;
        x = q[0];
        y = q[1];
        z = q[2];
        w = q[3];
        extend(x, minimum, &maximum);
        extend(y, minimum, &maximum);
        extend(z, minimum, &maximum);
        extend(w, minimum, &maximum);
    }
    *range = maximum - *minimum;
    FUN_001e5fe0(list, quantized, *minimum, *range);
}

void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2) {
    igObject *s0;
    igObject *old;
    igMetaField *fld;
    int name;
    int v;
    int newv;
    int oldv;
    s0 = (igObject *)*arg1;
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    old = (igObject *)arg0->_destObj;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destObj = (int)s0;
    fld = (igMetaField *)igMetaObject_FindFieldByName((*arg1)->vX(), arg2);
    if (fld != 0) {
        fld->_refCount = fld->_refCount + 1;
    }
    old = (igObject *)arg0->_destMeta;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destMeta = (int)fld;
    name = ((igMetaObject *)((igMetaField *)arg0->_destMeta)->_parentMetaObject)->_name;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = StringPool_Intern(DAT_00586f20[0], name);
    oldv = arg0->_destMetaClassName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaClassName = newv;
    name = ((igMetaField *)arg0->_destMeta)->_fieldName;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = StringPool_Intern(DAT_00586f20[0], name);
    oldv = arg0->_destMetaFieldName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaFieldName = newv;
}

void FUN_001e6410(S0 *arg0, void **arg1) {
    S_temp_a0 *temp_a0;
    S_temp_s0 *temp_s0;
    temp_s0 = (S_temp_s0 *)(*arg1);
    if (temp_s0 != 0) {
        temp_s0->f4 = (int)((int) (temp_s0->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)(arg0->f18);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(temp_s0);
}

int FUN_001e6490(ValueBinding *binding, int selection) {
    igSmartPointer<Value> value(binding->source->value(), kRetainReference);
    int sinkType = binding->sink->type();
    if (((FUN_002fe290(value->type(), sinkType) != 0) ^ 1) != 0) {
        return 0;
    }
    binding->source->select(selection);
    binding->sink->write(binding->key, (int)binding->source + value->offset);
    if (DAT_00562c60[0] == 0) {
        DAT_00562c60[0] = igMetaObject_FindFieldByName(DAT_00585cc8[0], &DAT_004e4aa0[0]);
    }
    Notify notify = *(Notify *)((char *)binding->sink + ((FieldDesc *)DAT_00562c60[0])->offset);
    if (notify != 0) {
        notify(binding->key);
    }
    return 1;
}

void Gap__igDataPump__vfunc_17(igDataPump *pump) {
    igSmartPointer<igObject> meta;
    meta = igObjectSystem_FindMetaByNameDefault(pump->_destMetaClassName);
    if (meta.get() != 0) {
        igObject *field = igMetaObject_FindFieldByName(meta.get(), pump->_destMetaFieldName);
        igObject *old;
        if (field != 0) {
            field->_refCount = field->_refCount + 1;
        }
        old = (igObject *)pump->_destMeta;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        pump->_destMeta = (int)field;
    }
}

void Gap__igDataPump__vfunc_14(void) {

}

int FUN_001e6770(int *p)
{
    return *(int *)((char *)p + 20);
}

int FUN_001e6780(void *arg0) {
    ObjectList_AppendRetained(*(int *)((char *)arg0 + 20));
    return 1;
}

int FUN_001e67a0(S *arg0, int arg1) {
    int i;
    int n;

    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        FUN_001e6490((ValueBinding *)arg0->list->data[i], arg1);
    }
    return 1;
}

int FUN_001e6820(struct D *arg0, struct L_1e6820 *arg1) {
    int i;
    int n;

    n = arg1->count;
    for (i = 0; i < n; i++) {
        ObjectList_AppendRetained(arg0->f8, arg1->items[i]);
    }
    return 1;
}

int FUN_001e68a0(int arg0, int arg1) {
    FUN_001e6820((struct D *)arg0, (struct L_1e6820 *)FUN_001e6770((int *)arg1));
    return 1;
}

static inline int count_of(const Lst *list) { return list->count; }

int FUN_001e68e0(Lst *arg0, int arg1) {
    int var_s0;
    int temp_v1;
    Mat *d;

    var_s0 = arg0->count;
    if (var_s0 == 0) {
        if (var_s0 < arg0->cap) {
            arg0->count = count_of(arg0) + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->data + var_s0, arg1);
    } else {
        temp_v1 = count_of(arg0);
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->cap) {
                arg0->count = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            d = arg0->data;
            Matrix44_Copy(d + var_s0, d + (var_s0 - 1));
        }
        FUN_001906d0(arg0->data + (arg0->count - 1), arg1);
    }
    return var_s0;
}

static inline int f8_of(const struct S_1e69e0 *list) { return list->f8; }

int FUN_001e69e0(struct S_1e69e0 *arg0, int arg1) {
    char *temp_a0;
    char *temp_a1;
    int temp_v1;
    int var_s0;

    var_s0 = f8_of(arg0);
    if (var_s0 == 0) {
        if (var_s0 < arg0->f12) {
            arg0->f8 = arg0->f8 + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->f16 + (var_s0 << 6), arg1);
    } else {
        temp_v1 = arg0->f8;
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->f12) {
                arg0->f8 = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            temp_a1 = arg0->f16;
            Matrix44_Copy(temp_a1 + (var_s0 << 6), temp_a1 + ((var_s0 - 1) << 6));
        }
        temp_a0 = arg0->f16 + ((arg0->f8 - 1) << 6);
        FUN_001904f0(temp_a0, temp_a0, arg1);
    }
    return var_s0;
}

void FUN_001e6ae0(struct S1e *arg0) {
    FUN_001906d0(arg0->base + (arg0->cnt - 1) * 64);
}

void FUN_001e6b00(void *arg0, int arg1) {
    int p;
    p = *(int *)((char *)(arg0) + 16) + ((*(int *)((char *)(arg0) + 8) - 1) << 6);
    FUN_001904f0(p, p, arg1);
}

void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed) {
    int i; for (i = 0; i < 624; i++) { self->_mt[i] = seed & 0xFFFF0000; seed = 69069 * seed + 1; self->_mt[i] |= (seed & 0xFFFF0000) >> 16; seed = 69069 * seed + 1; } self->_mti = 624;
}

void Gap__igMersenneTwisterRandomNumber__vfunc_13(void **arg0) {
    Gap__Core__igObject__vfunc_11();
    ((DW4VC_92_1 *)(arg0))->vX((int)(0x141E));
}

unsigned int FUN_001e6bc0(igMersenneTwisterRandomNumber *self) {
    static const unsigned int mag01[2] = {0x0, 0x9908b0df};
    unsigned int y;
    int kk;

    if (self->_mti >= 624) {
        for (kk = 0; kk < 624 - 397; kk++) {
            y = (self->_mt[kk] & 0x80000000) | (self->_mt[kk + 1] & 0x7fffffff);
            self->_mt[kk] = self->_mt[kk + 397] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < 624 - 1; kk++) {
            y = (self->_mt[kk] & 0x80000000) | (self->_mt[kk + 1] & 0x7fffffff);
            self->_mt[kk] = self->_mt[kk + (397 - 624)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (self->_mt[624 - 1] & 0x80000000) | (self->_mt[0] & 0x7fffffff);
        self->_mt[624 - 1] = self->_mt[397 - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        self->_mti = 0;
    }
    y = self->_mt[self->_mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);
    return y;
}

int FUN_001e6d30(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return sscanf(arg0, arg2, arg1, arg1 + 1, arg1 + 2) == 3;
    }
    return FUN_0018be80(arg0, arg1, 3, 4, 1) != 0;
}

int FUN_001e6d80(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return sscanf(arg0, arg2, arg1, arg1 + 1, arg1 + 2, arg1 + 3) == 4;
    }
    return FUN_0018be80(arg0, arg1, 4, 4, 1) != 0;
}

int FUN_001e6de0(int *result, Vector3f *value, int *format) {
    int name;
    int res;
    int pool;
    igSmartPointer<FormattedObject> formatted((FormattedObject *)FUN_002b9500(0), AdoptReference());
    int x = fptodp(value->x);
    int y = fptodp(value->y);
    FUN_0030b7e0(formatted.p, format, x, y, fptodp(value->z));
    name = formatted.p->f8;
    if (name == 0) {
        name = DAT_004c22f0[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            DAT_00586f20[0] = pool;
        }
        res = StringPool_Intern(DAT_00586f20[0], name);
    }
    *result = res;
    return 0;
}

int FUN_001e6f10(int *result, Quad *quad, int *kind) {
    int s3, s2, s1;
    int name;
    int res;
    int obj;
    Tag tag = Tag();
    igSmartPointer<QuadNamed> named((QuadNamed *)FUN_002b9500(0));
    s3 = fptodp(quad->x);
    s2 = fptodp(quad->y);
    s1 = fptodp(quad->z);
    FUN_0030b7e0(named.p, kind, s3, s2, s1, fptodp(quad->w));
    name = named.get()->name;
    if (name == 0) {
        name = DAT_004c22f0[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            obj = FUN_002eb010(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            DAT_00586f20[0] = obj;
        }
        res = StringPool_Intern(DAT_00586f20[0], name);
    }
    *result = res;
    return 0;
}

int thunk_FUN_003065f0()
{
    return FUN_003065f0();
}

int thunk_FUN_003066b0()
{
    return FUN_003066b0();
}

int thunk_FUN_00306770()
{
    return FUN_00306770();
}

int thunk_FUN_00306910()
{
    return FUN_00306910();
}

int thunk_FUN_00306e50()
{
    return FUN_00306e50();
}

int FUN_001e70a0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    void *sp6C;
    void *sp68;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;

    sp6C = (void *)(0);
    FUN_001e6de0((int *)&sp68, (Vector3f *)arg4, &DAT_004e4ac0[0]);
    if (FUN_00306910(arg0, arg1, arg2, &sp6C, sp68, arg5) != 0) {
        temp_s0 = FUN_001e6d30((int)sp6C, (int *)arg3, (int)&DAT_004e4ad0[0]) & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    return 0;
}

int FUN_001e71f0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    void *sp6C;
    void *sp68;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;

    sp6C = (void *)(0);
    FUN_001e6f10((int *)&sp68, (Quad *)arg4, &DAT_004e4ae8[0]);
    if (FUN_00306910(arg0, arg1, arg2, &sp6C, sp68, arg5) != 0) {
        temp_s0 = FUN_001e6d80((int)sp6C, (int *)arg3, (int)&DAT_004e4b00[0]) & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    return 0;
}

int Gap__igMersenneTwisterRandomNumber__vfunc_22(void) {
    return DAT_00562b88[0];
}

unsigned int Gap__igMersenneTwisterRandomNumber__vfunc_24(igMersenneTwisterRandomNumber *self) {
    return FUN_001e6bc0(self);
}

int Gap__igDataPump__vfunc_22(void) {
    return DAT_00562c20[0];
}

int Gap__igBoolObject__vfunc_22(void) {
    return DAT_00562c50[0];
}

int Gap__igDataPumpInfo__vfunc_22(void) {
    return DAT_00562c10[0];
}

int Gap__igDataPumpList__vfunc_22(void) {
    return DAT_00562c00[0];
}

int Gap__igDataPumpManager__vfunc_22(void) {
    return DAT_00562bf0[0];
}

int Gap__igFloatObject__vfunc_22(void) {
    return DAT_00562be0[0];
}

int Gap__igIntObject__vfunc_22(void) {
    return DAT_00562bd0[0];
}

int Gap__igMatrixObject__vfunc_22(void) {
    return DAT_00562bc0[0];
}

int Gap__igMatrixObjectList__vfunc_22(void) {
    return DAT_00562bb8[0];
}

int Gap__igNonRefCountedMatrixObjectList__vfunc_22(void) {
    return DAT_00562bb0[0];
}

int Gap__igMatrixStack__vfunc_22(void) {
    return DAT_00562ba0[0];
}

int Gap__igLongStack__vfunc_22(void) {
    return DAT_00562b60[0];
}

int Gap__igNonRefCountedMatrixObjectList__vfunc_24(void) {
    return DAT_00562bc0[0];
}

int Gap__igDataPumpList__vfunc_24(void) {
    return DAT_00562c20[0];
}

int Gap__igMatrixObjectList__vfunc_24(void) {
    return DAT_00562bc0[0];
}

void Gap__igLongStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void Gap__igMatrixStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0x40);
    }
}


#include "dw4/reflected.h"

class igObjectSlot33 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vfunc_33(int); };

class CopyableObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15();
    virtual void prepareCopy();
    virtual void s17(); virtual void s18();
    virtual CopyableObject *duplicate(int deep);
    unsigned int _refCount;
};

class VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void *vX(int); };
struct R { char pad[4]; int f4; };
struct M { char pad[8]; int f8; char pad2[41]; unsigned char f53; };
struct O { int p0; int p1; int f8; int f12; };

extern "C" {
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorByName(const char *);
void *igMetaObject_CreateInstance(void *, void *);
int igObject_ResetFields(int);
int igObject_VisitFields(...);
int igObject_IsAlikeExactly(int, int);
int igObject_IsAlikeDeep(int, int);
int igObject_IsAlikeShallow(int, int);
int Gap__Core__igObject__vfunc_10(...);
void Gap__Core__igObject__vfunc_09(void *);
int igRefMetaField_ReadRawFieldMem(...);
void igRefMetaField_ClearValue(igMetaField *, void *);
void *igRefMetaField_Construct(igRefMetaField *);
void *igRefMetaField_Init(igRefMetaField *);
int igRefMetaField_CopyConstruct(...);
int igRefMetaField_Destruct(...);
void FUN_003006a0(CopyableObject *dst, CopyableObject *src);
int FUN_00300770(...);
int FUN_00300490(...);
int FUN_00304430(...);
int FUN_00304680(...);
extern int DAT_004faef0[4];
extern int g_igObjectRefMetaField_vtable[4];

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1);
void igObjectRefMetaField_Assign(igObjectRefMetaField *field, void *object, igObject *value);
void *igObjectRefMetaField_Init(igObjectRefMetaField *);

void Gap__Core__igObjectRefMetaField__vfunc_12(int arg0);

void igObjectRefMetaField_InitDefaults(void **self);

void igObjectRefMetaField_Assign(igObjectRefMetaField *field,void *object,igObject *value);

void Gap__Core__igObjectRefMetaField__vfunc_24(int a0, int a1, int a2);

int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *);

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1);

void Gap__Core__igObjectRefMetaField__vfunc_51(igObjectRefMetaField *self, igObject **valueSlot);

void igObjectRefMetaField_ConstructValue(igObjectRefMetaField *field,void *object);

void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object);

void Gap__Core__igObjectRefMetaField__vfunc_34(igObjectRefMetaField *field,void *object);

void Gap__Core__igObjectRefMetaField__vfunc_28(void *arg0, int arg1);

void Gap__Core__igObjectRefMetaField__vfunc_30(char *arg0, int arg1);

void Gap__Core__igObjectRefMetaField__vfunc_37(int arg0, int arg1, int arg2);

void Gap__Core__igObjectRefMetaField__vfunc_36(igObjectRefMetaField *self, char *dst, char *src);

void Gap__Core__igObjectRefMetaField__vfunc_38(M *arg0, int arg1, int arg2);

void Gap__Core__igObjectRefMetaField__vfunc_39(igObjectRefMetaField *self, int instance);

void Gap__Core__igObjectRefMetaField__vfunc_41(struct O *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    FUN_00304430(&DAT_004faef0[0], arg3, arg0->f12, *(int *)(arg1 + arg0->f8));
    FUN_00304680();
    if (arg2 != 0) {
        temp_a0 = *(int *)(arg1 + arg0->f8);
        if (temp_a0 != 0) {
            FUN_00300490(temp_a0, arg2, arg3);
        }
    }
}

void Gap__Core__igObjectRefMetaField__vfunc_42(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3);

int Gap__Core__igObjectRefMetaField__vfunc_44(igObjectRefMetaField *arg0, int arg1, int arg2);

int Gap__Core__igObjectRefMetaField__vfunc_45(igObjectRefMetaField *self, int objectA, int objectB);

int Gap__Core__igObjectRefMetaField__vfunc_46(igObjectRefMetaField *self, int objectA, int objectB);

int Gap__Core__igObjectRefMetaField__vfunc_47(igObjectRefMetaField *self, int objectA, int objectB);

void *igObjectRefMetaField_Construct(igObjectRefMetaField *self);

void *igObjectRefMetaField_Init(igObjectRefMetaField *self);

void *FUN_00303c60(igObjectRefMetaField *arg0, void *arg1);

void Gap__Core__igObjectRefMetaField__vfunc_02(void);
}

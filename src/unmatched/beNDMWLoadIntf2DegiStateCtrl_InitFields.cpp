#include "dw4/reflected.h"
extern "C" {
int FUN_003c3cb0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
int igStringMetaField_SetDefaultText(...);
extern int DAT_004cb488[4];
extern int DAT_004cb490[4];
extern int DAT_004cb498[4];
extern int DAT_004cb4a0[4];
extern int DAT_00510cd8[4];
extern int DAT_00512a30[4];
extern void * DAT_0058b958[4];
extern int DAT_0058b960[4];
void beNDMWLoadIntf2DegiStateCtrl_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beNDMWLoadIntf2DegiStateCtrl_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(DAT_0058b958[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb488[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512a30[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b960[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) (temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) (int) temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = FUN_003c3cb0();
    temp_s0->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004cb490[0], &DAT_004cb498[0], &DAT_004cb4a0[0], temp_s2);
}

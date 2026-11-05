#include "dw4/reflected.h"
extern "C" {
int FUN_002ea4b0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObjectList_GetOrCreateMetaObject(...);
int igObject_Destroy(...);
extern int DAT_004c3d90[4];
extern int DAT_004c3df0[4];
extern int DAT_004c3e50[4];
extern int DAT_004c3eb0[4];
extern int DAT_00502570[4];
extern void * DAT_00588088[4];
extern int DAT_00588090[4];
void beSvPlatDataPS2_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beSvPlatDataPS2_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igEnumMetaField *temp_s0;
    igMetaObject *temp_s1;
    igEnumMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(DAT_00588088[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3d90[0], 0x16);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igEnumMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 5);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_00588090[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)temp_v0_2->_refCount - 1;
    if (((unsigned long long) ((long long)(int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xD); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x13); temp_s0->_getMetaEnumFunction = 2;
    igObjectRefMetaField *temp_s4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x15));
    temp_s4->_metaObject = igObjectList_GetOrCreateMetaObject();
    temp_s4->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c3df0[0], &DAT_004c3e50[0], &DAT_004c3eb0[0], temp_s2);
}

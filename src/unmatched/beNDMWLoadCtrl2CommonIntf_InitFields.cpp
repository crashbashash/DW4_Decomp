#include "dw4/reflected.h"
extern "C" {
int FUN_00232840(...);
int FUN_00342ce0(...);
int FUN_00357910(...);
int FUN_0036a230(...);
int FUN_003c5200(...);
int FUN_003c5520(...);
int FUN_003c61d0(...);
int FUN_003c66a0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
int igStringMetaField_SetDefaultText(...);
extern int DAT_004cb800[4];
extern int DAT_004cb840[4];
extern int DAT_004cb880[4];
extern int DAT_004cb8c0[4];
extern int DAT_00510cd8[4];
extern int DAT_00512c90[4];
extern void * DAT_0058bb00[4];
extern int DAT_0058bb08[4];
void beNDMWLoadCtrl2CommonIntf_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beNDMWLoadCtrl2CommonIntf_InitFields(void) {
    void **temp_v0;
    int temp_s3;
    int temp_s2;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (void *)(DAT_0058bb00[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb800[0], 0xE);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512c90[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058bb08[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    void *temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    void *temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    void *temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = FUN_0036a230();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    void *temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    void *temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = FUN_003c61d0();
    ((igRefMetaField *)temp_s0_5)->_construct = 1;
    void *temp_s0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s0_6)->_metaObject = FUN_003c66a0();
    ((igRefMetaField *)temp_s0_6)->_construct = 1;
    void *temp_s0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s0_7)->_metaObject = FUN_003c5520();
    ((igRefMetaField *)temp_s0_7)->_construct = 1;
    void *temp_s0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s0_8)->_metaObject = FUN_003c5200();
    ((igRefMetaField *)temp_s0_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004cb840[0], &DAT_004cb880[0], &DAT_004cb8c0[0], temp_s2);
}

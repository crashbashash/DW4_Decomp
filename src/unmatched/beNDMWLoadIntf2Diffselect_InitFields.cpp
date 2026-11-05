#include "dw4/reflected.h"
extern "C" {
int FUN_0034c8e0(...);
int FUN_003c6b40(...);
int FUN_003c4c20(...);
int FUN_003c6ee0(...);
int FUN_003c7700(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
int igStringMetaField_SetDefaultText(...);
extern int DAT_004cb1e0[4];
extern int DAT_004cb220[4];
extern int DAT_004cb260[4];
extern int DAT_004cb2a0[4];
extern int DAT_00510cd8[4];
extern int DAT_00512940[4];
extern void * DAT_0058b800[4];
extern int DAT_0058b808[4];
void beNDMWLoadIntf2Diffselect_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beNDMWLoadIntf2Diffselect_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(DAT_0058b800[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb1e0[0], 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512940[0]);
    ((igStringMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&DAT_0058b808[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igStringMetaField *)temp_v0_2)->_refCount = (int)((int) (((igStringMetaField *)temp_v0_2)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igStringMetaField *)temp_v0_2)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = FUN_003c7700();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = FUN_003c4c20();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = FUN_003c6b40();
    ((igObjectRefMetaField *)temp_s0_5)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004cb220[0], &DAT_004cb260[0], &DAT_004cb2a0[0], temp_s2);
}

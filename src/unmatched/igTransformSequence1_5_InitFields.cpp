#include "dw4/reflected.h"
extern "C" {
int FUN_0018a0a0(...);
int FUN_001a24f0(...);
int FUN_002ca680(...);
int FUN_002ebc00(...);
int FUN_00303460(...);
int FUN_0030e750(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
extern int DAT_0048afb0[4];
extern int DAT_0048afe0[4];
extern int DAT_0048b010[4];
extern int DAT_0048b040[4];
extern int DAT_004e1418[4];
extern void * DAT_005611d8[4];
extern int DAT_005611e8[4];
void igTransformSequence1_5_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void igTransformSequence1_5_InitFields(void) {
    int temp_s2;
    int temp_s3;
    int var_a1;
    igUnsignedCharArrayMetaField *t5;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igObjectRefMetaField *temp_s0_5;
    igMetaObject *temp_s1;
    igMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(DAT_005611d8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048afb0[0], 9);
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = FUN_002ca680();
    temp_s0->_construct = 1;
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e1418[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_00303460(temp_v0_2, 0);
    *(char *)((char *)(temp_v0_2) + 52) = 0;
    temp_v0_2->_externalEnumStorage = (int)(&DAT_005611e8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) (temp_v0_2->_refCount - 1));
    var_a1 = temp_s2 + 1;
    if ((temp_v0_2->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2, var_a1);
        var_a1 = temp_s2 + 1;
    }
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, var_a1));
    temp_s0_2->_metaObject = FUN_0018a0a0();
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = FUN_0018a0a0();
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_4->_metaObject = FUN_0018a0a0();
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4), 0xB);
    t5 = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5);
    t5->_num = 3;
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7), -1);
    temp_s0_5 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    temp_s0_5->_metaObject = FUN_001a24f0();
    igMetaObject_NameFields(temp_s1, &DAT_0048afe0[0], &DAT_0048b010[0], &DAT_0048b040[0], temp_s2);
}

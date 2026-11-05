/* 0x00137980 — igGeometryAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_0014b980();
int FUN_0014d7f0();
int FUN_0018a0a0();
int FUN_002ca450();
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void thunk_igGeometryAttr1_5_GetMetaObject(void); /* address-taken; signature not recovered */
extern int DAT_004865a0[4];
extern int DAT_004865d0[4];
extern int DAT_00486600[4];
extern int DAT_00486630[4];
extern int DAT_00486658[4];
extern void * DAT_0055f170[4];
int FUN_00149aa0();

void igGeometryAttr_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_v0;

    temp_s1 = (void *)(DAT_0055f170[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004865a0[0], 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b980();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014d7f0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    FUN_002dc7a0(temp_v0, &DAT_00486658[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002ca450();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0018a0a0();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0018a0a0();
    igMetaObject_NameFields(temp_s1, &DAT_004865d0[0], &DAT_00486600[0], &DAT_00486630[0], temp_s0);
    *(int *)((char *)(DAT_0055f170[0]) + 60) = (int)thunk_igGeometryAttr1_5_GetMetaObject;
}

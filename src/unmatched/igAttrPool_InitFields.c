#include "dw4/reflected.h"
int FUN_0013abd0();
int FUN_002c8e50();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486bf8[4];
extern int DAT_00486c08[4];
extern int DAT_00486c18[4];
extern int DAT_00486c28[4];
extern int DAT_0055f428[4];
void thunk_FUN_0013c110(void);

void igAttrPool_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1_3;

    temp_s0 = (void *)DAT_0055f428[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486bf8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c8e50();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002c8e50();
    ((igObjectRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00486c08[0], &DAT_00486c18[0], &DAT_00486c28[0], temp_s2);
    FUN_002fe480((int)thunk_FUN_0013c110);
}

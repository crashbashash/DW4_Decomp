#include "dw4/reflected.h"
int FUN_002b8d90();
int FUN_002ca2a0();
int FUN_002ca8f0();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf520[4];
extern int DAT_004bf550[4];
extern int DAT_004bf580[4];
extern int DAT_004bf5b0[4];
extern int DAT_00585830[4];
void igSymbolTable_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;

    temp_s1 = (void *)DAT_00585830[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004bf520[0], 9);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), -1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002ca2a0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002ca8f0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002b8d90();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002b8d90();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004bf550[0], &DAT_004bf580[0], &DAT_004bf5b0[0], temp_s0);
}

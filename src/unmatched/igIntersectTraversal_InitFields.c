#include "dw4/reflected.h"
int FUN_00186c40();
int FUN_00188260();
int FUN_0019cbe0();
int FUN_0019e6c0();
int FUN_001e4740();
int FUN_002ea4b0();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048be00[4];
extern int DAT_0048be20[4];
extern int DAT_0048be40[4];
extern int DAT_0048be60[4];
extern int DAT_00561930[4];
int thunk_FUN_001ce740();

void igIntersectTraversal_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;

    temp_s1 = (void *)DAT_00561930[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048be00[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0019e6c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 5);
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s1, 4 + temp_s0)))->_persistent = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00186c40();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00188260();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048be20[0], &DAT_0048be40[0], &DAT_0048be60[0], temp_s0);
    FUN_002fe480(&thunk_FUN_001ce740);
}

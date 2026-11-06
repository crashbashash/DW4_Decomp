#include "dw4/reflected.h"
int FUN_00188260();
int FUN_0019dfd0();
int FUN_0019f670();
int FUN_002e3810(int, float);
int FUN_0044ded0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0330[4];
extern int DAT_004d0350[4];
extern int DAT_004d0370[4];
extern int DAT_004d0390[4];
extern int DAT_0058c380[4];
void igMousePosObserver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c380[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0330[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044ded0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002e3810((int)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 0.0f);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d0350[0], &DAT_004d0370[0], &DAT_004d0390[0], temp_s0);
}

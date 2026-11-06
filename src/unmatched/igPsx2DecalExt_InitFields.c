#include "dw4/reflected.h"
int FUN_00150770();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048a0b8[4];
extern int DAT_0048a0c0[4];
extern int DAT_0048a0c8[4];
extern int DAT_0048a0d0[4];
extern int DAT_005605f8[4];
void igPsx2DecalExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005605f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048a0b8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048a0c0[0], &DAT_0048a0c8[0], &DAT_0048a0d0[0], temp_s2);
}

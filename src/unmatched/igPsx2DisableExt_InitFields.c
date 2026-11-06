#include "dw4/reflected.h"
int FUN_00150770();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048a090[4];
extern int DAT_0048a098[4];
extern int DAT_0048a0a0[4];
extern int DAT_0048a0a8[4];
extern int DAT_005605e8[4];
void igPsx2DisableExt_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005605e8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048a090[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048a098[0], &DAT_0048a0a0[0], &DAT_0048a0a8[0], temp_s2);
}

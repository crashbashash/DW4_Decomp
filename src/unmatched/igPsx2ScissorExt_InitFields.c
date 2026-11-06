#include "dw4/reflected.h"
int FUN_00150770();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489e10[4];
extern int DAT_00489e30[4];
extern int DAT_00489e50[4];
extern int DAT_00489e70[4];
extern int DAT_005604f8[4];
void igPsx2ScissorExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005604f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489e10[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0x1C0);
    igMetaObject_NameFields(temp_s0, &DAT_00489e30[0], &DAT_00489e50[0], &DAT_00489e70[0], temp_s2);
}

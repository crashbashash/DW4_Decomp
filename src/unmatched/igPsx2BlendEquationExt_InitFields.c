#include "dw4/reflected.h"
int FUN_00150770();
int FUN_002d4e40();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048a100[4];
extern int DAT_0048a120[4];
extern int DAT_0048a140[4];
extern int DAT_0048a160[4];
extern int DAT_00560628[4];
void igPsx2BlendEquationExt_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00560628[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048a100[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002d4e40(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), -0x80);
    igMetaObject_NameFields(temp_s0, &DAT_0048a120[0], &DAT_0048a140[0], &DAT_0048a160[0], temp_s2);
}

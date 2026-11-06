#include "dw4/reflected.h"
int FUN_0014a7c0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004884f0[4];
extern int DAT_004884f8[4];
extern int DAT_00488500[4];
extern int DAT_00488508[4];
extern int DAT_0055f9d0[4];
void igVertexArray2Helper_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f9d0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004884f0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a7c0();
    igMetaObject_NameFields(temp_s0, &DAT_004884f8[0], &DAT_00488500[0], &DAT_00488508[0], temp_s2);
}

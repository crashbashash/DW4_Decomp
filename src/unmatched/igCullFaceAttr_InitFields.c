#include "dw4/reflected.h"
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486768[4];
extern int DAT_00486770[4];
extern int DAT_00486778[4];
extern int DAT_00486780[4];
extern int DAT_00486788[4];
extern int DAT_0055f238[4];
int FUN_00149620();

void igCullFaceAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f238[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486768[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00486788[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149620);
    igMetaObject_NameFields(temp_s0, &DAT_00486770[0], &DAT_00486778[0], &DAT_00486780[0], temp_s2);
}

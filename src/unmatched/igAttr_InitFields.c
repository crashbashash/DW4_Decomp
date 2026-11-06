#include "dw4/reflected.h"
int FUN_0030a520();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486c50[4];
extern int DAT_00486c58[4];
extern int DAT_00486c60[4];
extern int DAT_00486c68[4];
extern int DAT_0055f468[4];
void igAttr_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f468[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486c50[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_0030a520(temp_v0, -1);
    ((igShortMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00486c58[0], &DAT_00486c60[0], &DAT_00486c68[0], temp_s2);
}

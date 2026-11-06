#include "dw4/reflected.h"
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486100[4];
extern int DAT_00486108[4];
extern int DAT_00486110[4];
extern int DAT_00486118[4];
extern int DAT_00486120[4];
extern int DAT_0055ef60[4];
int FUN_001495c0();

void igPolygonModeAttr_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ef60[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486100[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486120[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001495c0);
    igMetaObject_NameFields(temp_s0, &DAT_00486108[0], &DAT_00486110[0], &DAT_00486118[0], temp_s2);
}

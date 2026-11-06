#include "dw4/reflected.h"
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486128[4];
extern int DAT_00486130[4];
extern int DAT_00486138[4];
extern int DAT_00486140[4];
extern int DAT_00486148[4];
extern int DAT_0055ef70[4];
int FUN_00149800();

void igPixelPipelineModeAttr_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ef70[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486128[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486148[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149800);
    igMetaObject_NameFields(temp_s0, &DAT_00486130[0], &DAT_00486138[0], &DAT_00486140[0], temp_s2);
}

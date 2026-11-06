#include "dw4/reflected.h"
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485f10[4];
extern int DAT_00485f18[4];
extern int DAT_00485f20[4];
extern int DAT_00485f28[4];
extern int DAT_00485f30[4];
extern int DAT_0055ee90[4];
int FUN_00149680();

void igShadeModelAttr_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ee90[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485f10[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00485f30[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149680);
    igMetaObject_NameFields(temp_s0, &DAT_00485f18[0], &DAT_00485f20[0], &DAT_00485f28[0], temp_s2);
}

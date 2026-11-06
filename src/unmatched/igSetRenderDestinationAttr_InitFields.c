#include "dw4/reflected.h"
int FUN_001341f0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485f40[4];
extern int DAT_00485f48[4];
extern int DAT_00485f50[4];
extern int DAT_00485f58[4];
extern int DAT_0055eea0[4];
void igSetRenderDestinationAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055eea0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485f40[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001341f0();
    igMetaObject_NameFields(temp_s0, &DAT_00485f48[0], &DAT_00485f50[0], &DAT_00485f58[0], temp_s2);
}

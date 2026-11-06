#include "dw4/reflected.h"
int FUN_001e53c0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048db88[4];
extern int DAT_0048db90[4];
extern int DAT_0048db98[4];
extern int DAT_0048dba0[4];
extern int DAT_00562bf0[4];
void igDataPumpManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bf0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db88[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e53c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048db90[0], &DAT_0048db98[0], &DAT_0048dba0[0], temp_s2);
}

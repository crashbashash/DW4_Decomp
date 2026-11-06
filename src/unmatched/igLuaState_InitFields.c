#include "dw4/reflected.h"
int FUN_002c04a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498648[4];
extern int DAT_00498650[4];
extern int DAT_00498658[4];
extern int DAT_00498660[4];
extern int DAT_0056de10[4];
void igLuaState_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056de10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498648[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c04a0();
    igMetaObject_NameFields(temp_s0, &DAT_00498650[0], &DAT_00498658[0], &DAT_00498660[0], temp_s2);
}

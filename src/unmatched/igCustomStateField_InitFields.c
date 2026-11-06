#include "dw4/reflected.h"
int FUN_002beca0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489020[4];
extern int DAT_00489028[4];
extern int DAT_00489030[4];
extern int DAT_00489038[4];
extern int DAT_0055fe50[4];
void igCustomStateField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fe50[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489020[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002beca0();
    igMetaObject_NameFields(temp_s0, &DAT_00489028[0], &DAT_00489030[0], &DAT_00489038[0], temp_s2);
}

#include "dw4/reflected.h"
int FUN_002c4ce0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1b08[4];
extern int DAT_004c1b10[4];
extern int DAT_004c1b18[4];
extern int DAT_004c1b20[4];
extern void * DAT_00586be8[4];
extern void thunk_igElfFile_GetMetaObject(void);

void igProgramFile_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    ((igMetaObject *)(DAT_00586be8[0]))->_persistent = 0;
    temp_s0 = (void *)(DAT_00586be8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1b08[0], 2);
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2)))->_persistent = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    ((igObjectRefMetaField *)temp_s1)->_construct = 0;
    ((igObjectRefMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c1b10[0], &DAT_004c1b18[0], &DAT_004c1b20[0], temp_s2);
    ((igMetaObject *)(DAT_00586be8[0]))->_abstractProxy = (int)thunk_igElfFile_GetMetaObject;
}

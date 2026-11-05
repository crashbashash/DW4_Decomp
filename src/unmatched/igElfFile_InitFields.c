#include "dw4/reflected.h"
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1b30[4];
extern int DAT_004c1b60[4];
extern int DAT_004c1b90[4];
extern int DAT_004c1bc0[4];
extern void * DAT_00586c00[4];
void igElfFile_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    int temp_s1;

    ((igMetaObject *)DAT_00586c00[0])->_persistent = 0;
    temp_s0 = (void *)(DAT_00586c00[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1b30[0], 9);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igMetaField *)temp_v0)->_size = 0x34;
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igMetaField *)temp_v0_2)->_size = 4;
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3))->_persistent = 0;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igMetaField *)temp_v0_3)->_size = 4;
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5))->_persistent = 0;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igMetaField *)temp_v0_4)->_size = 4;
    ((igMetaField *)temp_v0_4)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7))->_persistent = 0;
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igMetaField *)temp_v0_5)->_size = 4;
    ((igMetaField *)temp_v0_5)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c1b60[0], &DAT_004c1b90[0], &DAT_004c1bc0[0], temp_s1);
}

#include "dw4/reflected.h"
int FUN_001460b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void thunk_FUN_00146470(void);
extern int DAT_00487130[4];
extern int DAT_00487138[4];
extern int DAT_00487140[4];
extern int DAT_00487148[4];
extern void * DAT_0055f5e8[4];
void igInterfaceManager_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055f5e8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487130[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001460b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487138[0], &DAT_00487140[0], &DAT_00487148[0], temp_s2);
    *(int *)((char *)(DAT_0055f5e8[0]) + 60) = (int)(thunk_FUN_00146470);
}

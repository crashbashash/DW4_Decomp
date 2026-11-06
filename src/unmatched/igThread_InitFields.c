#include "dw4/reflected.h"
int FUN_002dc7a0();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_002b7dc0(void);
void thunk_igPsx2Thread_GetMetaObject(void);
extern int DAT_004bf420[4];
extern int DAT_004bf450[4];
extern int DAT_004bf480[4];
extern int DAT_004bf4b0[4];
extern int DAT_004bf4d8[4];
extern int DAT_004bf4e0[4];
extern int DAT_004bf4e8[4];
extern int DAT_004bf4f0[4];
extern void * DAT_005857c8[4];
int FUN_002b7e20();
int FUN_002b7e80();
int FUN_002b7ee0();

void igThread_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_s1 = (void *)(DAT_005857c8[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004bf420[0], 0xA);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    FUN_002dc7a0(temp_v0, &DAT_004bf4d8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_002b7dc0);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_004bf4e0[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_002b7ee0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    FUN_002dc7a0(temp_v0_3, &DAT_004bf4e8[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(&FUN_002b7e80);
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    FUN_002dc7a0(temp_v0_4, &DAT_004bf4f0[0]);
    ((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (int)(&FUN_002b7e20);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6), 0x1000);
    igMetaObject_NameFields(temp_s1, &DAT_004bf450[0], &DAT_004bf480[0], &DAT_004bf4b0[0], temp_s0);
    *(int *)((char *)(DAT_005857c8[0]) + 60) = (int)thunk_igPsx2Thread_GetMetaObject;
}

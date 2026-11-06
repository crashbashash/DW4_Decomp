#include "dw4/reflected.h"
int FUN_002dc7a0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_002c7720(void);
extern int DAT_004c1290[4];
extern int DAT_004c12a0[4];
extern int DAT_004c12b0[4];
extern int DAT_004c12c0[4];
extern int DAT_004c12d0[4];
extern int DAT_004c12d8[4];
extern int DAT_00586710[4];
int FUN_002c7780();

void igDirEntry_InitFields(void) {
    int temp_s2;
    void *temp_v0_3;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586710[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1290[0], 4);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002ea4b0(temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_004c12d0[0]);
    ((igEnumMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_002c7780);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0_3, &DAT_004c12d8[0]);
    ((igEnumMetaField *)temp_v0_3)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_002c7720);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c12a0[0], &DAT_004c12b0[0], &DAT_004c12c0[0], temp_s2);
}

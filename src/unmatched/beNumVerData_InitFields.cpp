#include "dw4/reflected.h"
extern "C" {
int FUN_002ea4b0(void *, int);
int FUN_0034dcd0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c49d8[4];
extern int DAT_004c49e0[4];
extern int DAT_004c49e8[4];
extern int DAT_004c49f0[4];
extern int DAT_00588690[4];
void beNumVerData_InitFields(void);
}
void beNumVerData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588690[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c49d8[0], 2);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034dcd0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c49e0[0], &DAT_004c49e8[0], &DAT_004c49f0[0], temp_s2);
}

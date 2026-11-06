#include "dw4/reflected.h"
extern "C" {
int FUN_002c4ce0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6f80[4];
extern int DAT_004c6f88[4];
extern int DAT_004c6f90[4];
extern int DAT_004c6f98[4];
extern int DAT_00589780[4];
void beFileChkObj_InitFields(void);
}
void beFileChkObj_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00589780[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6f80[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6f88[0], &DAT_004c6f90[0], &DAT_004c6f98[0], temp_s2);
}

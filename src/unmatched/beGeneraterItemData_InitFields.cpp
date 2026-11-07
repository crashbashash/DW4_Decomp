#include "dw4/reflected.h"
extern "C" {
int FUN_00360780(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6ae0[4];
extern int DAT_004c6ae8[4];
extern int DAT_004c6af0[4];
extern int DAT_004c6af8[4];
extern int DAT_00589590[4];
void beGeneraterItemData_InitFields(void);
}
void beGeneraterItemData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589590[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6ae0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00360780();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6ae8[0], &DAT_004c6af0[0], &DAT_004c6af8[0], temp_s2);
}

#include "dw4/reflected.h"
extern "C" {
int FUN_0019f670(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7880[4];
extern int DAT_004c7890[4];
extern int DAT_004c78a0[4];
extern int DAT_004c78b0[4];
extern int DAT_00589be8[4];
void beCameraDemoData_InitFields(void);
}
void beCameraDemoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589be8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7880[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s0, &DAT_004c7890[0], &DAT_004c78a0[0], &DAT_004c78b0[0], temp_s2);
}

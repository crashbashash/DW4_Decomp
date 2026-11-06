#include "dw4/reflected.h"
extern "C" {
int FUN_00346120(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3bb0[4];
extern int DAT_004c3bb8[4];
extern int DAT_004c3bc0[4];
extern int DAT_004c3bc8[4];
extern int DAT_00587fb8[4];
void beSeInfoData_InitFields(void);
}
void beSeInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587fb8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3bb0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00346120();
    igMetaObject_NameFields(temp_s0, &DAT_004c3bb8[0], &DAT_004c3bc0[0], &DAT_004c3bc8[0], temp_s2);
}

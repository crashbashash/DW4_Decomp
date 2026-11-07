#include "dw4/reflected.h"
extern "C" {
int FUN_0018a0a0(void);
int igIntList_GetOrCreateMetaObject(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3540[4];
extern int DAT_004c3550[4];
extern int DAT_004c3560[4];
extern int DAT_004c3570[4];
extern int DAT_00587ce8[4];
void beTargetObj_InitFields(void);
}
void beTargetObj_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587ce8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3540[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0018a0a0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3550[0], &DAT_004c3560[0], &DAT_004c3570[0], temp_s2);
}

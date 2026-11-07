#include "dw4/reflected.h"
extern "C" {
int FUN_0034c8e0(void);
int FUN_00357910(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5f50[4];
extern int DAT_004c5f70[4];
extern int DAT_004c5f90[4];
extern int DAT_004c5fb0[4];
extern int DAT_00589090[4];
void beMemory_InitFields(void);
}
void beMemory_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589090[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5f50[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c5f70[0], &DAT_004c5f90[0], &DAT_004c5fb0[0], temp_s2);
}

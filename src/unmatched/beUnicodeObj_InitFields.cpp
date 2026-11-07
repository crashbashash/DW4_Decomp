#include "dw4/reflected.h"
extern "C" {
int FUN_002b6330(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6c78[4];
extern int DAT_004c6c80[4];
extern int DAT_004c6c88[4];
extern int DAT_004c6c90[4];
extern int DAT_00589640[4];
void beUnicodeObj_InitFields(void);
}
void beUnicodeObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589640[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6c78[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002b6330();
    igMetaObject_NameFields(temp_s0, &DAT_004c6c80[0], &DAT_004c6c88[0], &DAT_004c6c90[0], temp_s2);
}

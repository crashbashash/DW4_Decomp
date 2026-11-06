#include "dw4/reflected.h"
extern "C" {
int FUN_002cc2c0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4388[4];
extern int DAT_004c4390[4];
extern int DAT_004c4398[4];
extern int DAT_004c43a0[4];
extern int DAT_005883b0[4];
void beSaveDataDeliver_InitFields(void);
}
void beSaveDataDeliver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005883b0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4388[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4390[0], &DAT_004c4398[0], &DAT_004c43a0[0], temp_s2);
}

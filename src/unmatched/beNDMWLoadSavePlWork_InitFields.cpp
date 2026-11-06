#include "dw4/reflected.h"
extern "C" {
int FUN_002d3890(void *, int);
int FUN_003c63a0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cba60[4];
extern int DAT_004cbaa0[4];
extern int DAT_004cbae0[4];
extern int DAT_004cbb20[4];
extern int DAT_0058bc18[4];
void beNDMWLoadSavePlWork_InitFields(void);
}
void beNDMWLoadSavePlWork_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058bc18[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cba60[0], 0xE);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c63a0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cbaa0[0], &DAT_004cbae0[0], &DAT_004cbb20[0], temp_s2);
}

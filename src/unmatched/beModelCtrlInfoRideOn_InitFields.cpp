#include "dw4/reflected.h"
extern "C" {
int FUN_0034fd40(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5230[4];
extern int DAT_004c5240[4];
extern int DAT_004c5250[4];
extern int DAT_004c5260[4];
extern int DAT_00588aa8[4];
void beModelCtrlInfoRideOn_InitFields(void);
}
void beModelCtrlInfoRideOn_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00588aa8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5230[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034fd40();
    igMetaObject_NameFields(temp_s0, &DAT_004c5240[0], &DAT_004c5250[0], &DAT_004c5260[0], temp_s2);
}

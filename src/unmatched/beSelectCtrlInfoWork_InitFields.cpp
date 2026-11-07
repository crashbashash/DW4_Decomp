#include "dw4/reflected.h"
extern "C" {
int FUN_002cb110(void);
int FUN_002d3890(void *, int);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3ac0[4];
extern int DAT_004c3ae0[4];
extern int DAT_004c3b00[4];
extern int DAT_004c3b20[4];
extern int DAT_00587f60[4];
void beSelectCtrlInfoWork_InitFields(void);
}
void beSelectCtrlInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587f60[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3ac0[0], 5);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    igMetaObject_NameFields(temp_s0, &DAT_004c3ae0[0], &DAT_004c3b00[0], &DAT_004c3b20[0], temp_s2);
}

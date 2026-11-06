#include "dw4/reflected.h"
extern "C" {
int FUN_0018e470(void *, int *);
int FUN_00196190(void);
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6790[4];
extern int DAT_004c67c0[4];
extern int DAT_004c67f0[4];
extern int DAT_004c6820[4];
extern int DAT_00589400[4];
void beHitLandDelivInfoRam_InitFields(void);
}
void beHitLandDelivInfoRam_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_s1;
    int vc[3];
    int vb[3];
    int va[3];
    int temp_s2;

    temp_s0 = (void *)DAT_00589400[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6790[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 3.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 4.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 4.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    va[0] = 0;
    va[1] = 0;
    va[2] = 0;
    FUN_0018e470(temp_a0, va);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    vb[0] = 0;
    vb[1] = 0;
    vb[2] = 0;
    FUN_0018e470(temp_a0_2, vb);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    vc[0] = 0;
    vc[1] = 0;
    vc[2] = 0;
    FUN_0018e470(temp_a0_3, vc);
    igMetaObject_NameFields(temp_s0, &DAT_004c67c0[0], &DAT_004c67f0[0], &DAT_004c6820[0], temp_s2);
}

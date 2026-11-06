#include "dw4/reflected.h"
int FUN_0014c980();
int FUN_002ebc00();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486160[4];
extern int DAT_00486180[4];
extern int DAT_004861a0[4];
extern int DAT_004861c0[4];
extern int DAT_0055ef80[4];
void igParticleAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ef80[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486160[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014c980();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    FUN_002ebc00(temp_v0, -1);
    ((igLongMetaField *)temp_v0)->_persistent = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00486180[0], &DAT_004861a0[0], &DAT_004861c0[0], temp_s2);
}

#include "dw4/reflected.h"
int FUN_00194dd0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d670[4];
extern int DAT_0048d680[4];
extern int DAT_0048d690[4];
extern int DAT_0048d6a0[4];
extern int DAT_00562430[4];
void igAnimationTrack_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00562430[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d670[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00194dd0();
    igMetaObject_NameFields(temp_s0, &DAT_0048d680[0], &DAT_0048d690[0], &DAT_0048d6a0[0], temp_s2);
}

#include "dw4/reflected.h"
int FUN_0023a080();
int FUN_002be610();
int FUN_00303460();
int igCollisionGroup_GetMetaObject();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498450[4];
extern int DAT_00498458[4];
extern int DAT_00498460[4];
extern int DAT_00498468[4];
extern int DAT_0056dd28[4];
void igCollisionGridHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dd28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498450[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0023a080();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    igMetaObject_NameFields(temp_s0, &DAT_00498458[0], &DAT_00498460[0], &DAT_00498468[0], temp_s2);
}

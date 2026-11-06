#include "dw4/reflected.h"
int FUN_0023a080();
int FUN_002be610();
int FUN_002ea4b0();
int FUN_00303460();
int igStringMetaField_SetDefaultText();
int igCollisionGrid_GetMetaObject();
int igCollisionGroup_GetMetaObject();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498300[4];
extern int DAT_00498320[4];
extern int DAT_00498340[4];
extern int DAT_00498360[4];
extern int DAT_0056dc88[4];
void igCreateCollisionDatabase_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    int temp_s2;

    temp_s0 = (void *)DAT_0056dc88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498300[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1, igCollisionGrid_GetMetaObject());
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    FUN_00303460(temp_s1_2, igCollisionGroup_GetMetaObject());
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0023a080();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498320[0], &DAT_00498340[0], &DAT_00498360[0], temp_s2);
}

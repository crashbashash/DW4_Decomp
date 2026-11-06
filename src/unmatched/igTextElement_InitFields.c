#include "dw4/reflected.h"
int FUN_00137850();
int igStringMetaField_SetDefaultText();
int FUN_004507f0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004cff28[4];
extern int DAT_004cff38[4];
extern int DAT_004cff48[4];
extern int DAT_004cff58[4];
extern int DAT_0051dd88[4];
extern int DAT_0058c1d0[4];
void igTextElement_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c1d0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff28[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_004507f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00137850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), &DAT_0051dd88[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004cff38[0], &DAT_004cff48[0], &DAT_004cff58[0], temp_s2);
}

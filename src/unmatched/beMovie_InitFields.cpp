#include "dw4/reflected.h"
extern "C" {
int igStringMetaField_SetDefaultText(void *, int);
int FUN_00336c10(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4b98[4];
extern int DAT_004c4ba0[4];
extern int DAT_004c4ba8[4];
extern int DAT_004c4bb0[4];
extern int DAT_00588788[4];
void beMovie_InitFields(void);
}
void beMovie_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00588788[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4b98[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00336c10();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c4ba0[0], &DAT_004c4ba8[0], &DAT_004c4bb0[0], temp_s2);
}

#include "dw4/reflected.h"
extern "C" {
int FUN_0035bb70(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6350[4];
extern int DAT_004c6358[4];
extern int DAT_004c6360[4];
extern int DAT_004c6368[4];
extern int DAT_00589238[4];
void beLightCtrlInfo_InitFields(void);
}
void beLightCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589238[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6350[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035bb70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6358[0], &DAT_004c6360[0], &DAT_004c6368[0], temp_s2);
}

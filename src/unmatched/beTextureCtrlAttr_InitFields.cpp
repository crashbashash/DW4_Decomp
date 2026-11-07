#include "dw4/reflected.h"
extern "C" {
int FUN_001a5d70(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3498[4];
extern int DAT_004c34a0[4];
extern int DAT_004c34a8[4];
extern int DAT_004c34b0[4];
extern int DAT_00587c98[4];
void beTextureCtrlAttr_InitFields(void);
}
void beTextureCtrlAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587c98[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3498[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a5d70();
    igMetaObject_NameFields(temp_s0, &DAT_004c34a0[0], &DAT_004c34a8[0], &DAT_004c34b0[0], temp_s2);
}

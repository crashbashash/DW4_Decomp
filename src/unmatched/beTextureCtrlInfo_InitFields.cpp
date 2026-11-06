#include "dw4/reflected.h"
extern "C" {
int FUN_002be100(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3470[4];
extern int DAT_004c3478[4];
extern int DAT_004c3480[4];
extern int DAT_004c3488[4];
extern int DAT_00587c80[4];
void beTextureCtrlInfo_InitFields(void);
}
void beTextureCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587c80[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3470[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3478[0], &DAT_004c3480[0], &DAT_004c3488[0], temp_s2);
}

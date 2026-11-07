#include "dw4/reflected.h"
extern "C" {
int FUN_002be100(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c37f0[4];
extern int DAT_004c3800[4];
extern int DAT_004c3810[4];
extern int DAT_004c3820[4];
extern int DAT_00587e40[4];
void beSoundInfo_InitFields(void);
}
void beSoundInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587e40[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c37f0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    igMetaObject_NameFields(temp_s0, &DAT_004c3800[0], &DAT_004c3810[0], &DAT_004c3820[0], temp_s2);
}

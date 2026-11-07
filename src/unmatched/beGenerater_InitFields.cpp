#include "dw4/reflected.h"
extern "C" {
int FUN_0035b770(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6b98[4];
extern int DAT_004c6ba0[4];
extern int DAT_004c6ba8[4];
extern int DAT_004c6bb0[4];
extern int DAT_005895d0[4];
void beGenerater_InitFields(void);
}
void beGenerater_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005895d0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6b98[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c6ba0[0], &DAT_004c6ba8[0], &DAT_004c6bb0[0], temp_s2);
}

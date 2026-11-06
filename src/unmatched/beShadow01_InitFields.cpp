#include "dw4/reflected.h"
extern "C" {
int FUN_003449b0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3a48[4];
extern int DAT_004c3a50[4];
extern int DAT_004c3a58[4];
extern int DAT_004c3a60[4];
extern int DAT_00587f10[4];
void beShadow01_InitFields(void);
}
void beShadow01_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587f10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3a48[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003449b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3a50[0], &DAT_004c3a58[0], &DAT_004c3a60[0], temp_s2);
}

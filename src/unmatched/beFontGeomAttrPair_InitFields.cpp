#include "dw4/reflected.h"
extern "C" {
int FUN_0013a4d0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6e28[4];
extern int DAT_004c6e38[4];
extern int DAT_004c6e48[4];
extern int DAT_004c6e58[4];
extern int DAT_005896d8[4];
void beFontGeomAttrPair_InitFields(void);
}
void beFontGeomAttrPair_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005896d8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6e28[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013a4d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6e38[0], &DAT_004c6e48[0], &DAT_004c6e58[0], temp_s2);
}

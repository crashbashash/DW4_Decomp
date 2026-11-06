#include "dw4/reflected.h"
extern "C" {
int FUN_0035f9d0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6988[4];
extern int DAT_004c6990[4];
extern int DAT_004c6998[4];
extern int DAT_004c69a0[4];
extern int DAT_005894d8[4];
void beGeneraterInfo_InitFields(void);
}
void beGeneraterInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005894d8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6988[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035f9d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6990[0], &DAT_004c6998[0], &DAT_004c69a0[0], temp_s2);
}

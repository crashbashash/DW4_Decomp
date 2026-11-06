/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int beBaseInfoRamList_GetOrCreateMetaObject(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c68a0[4];
extern int DAT_004c68d0[4];
extern int DAT_004c6900[4];
extern int DAT_004c6930[4];
extern int DAT_00589478[4];
void beGeneraterInfoWork_InitFields(void);
}
void beGeneraterInfoWork_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00589478[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c68a0[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c68d0[0], &DAT_004c6900[0], &DAT_004c6930[0], temp_s2);
}

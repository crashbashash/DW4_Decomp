/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_0035ded0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6670[4];
extern int DAT_004c6678[4];
extern int DAT_004c6680[4];
extern int DAT_004c6688[4];
extern int DAT_00589380[4];
void beHitLandModelTraversal_InitFields(void);
}
void beHitLandModelTraversal_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00589380[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6670[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035ded0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6678[0], &DAT_004c6680[0], &DAT_004c6688[0], temp_s2);
}

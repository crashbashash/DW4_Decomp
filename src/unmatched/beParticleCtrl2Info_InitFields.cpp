/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00196930(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4630[4];
extern int DAT_004c4640[4];
extern int DAT_004c4650[4];
extern int DAT_004c4660[4];
extern int DAT_005884e0[4];
void beParticleCtrl2Info_InitFields(void);
}
void beParticleCtrl2Info_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_005884e0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4630[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00196930();
    igMetaObject_NameFields(temp_s0, &DAT_004c4640[0], &DAT_004c4650[0], &DAT_004c4660[0], temp_s2);
}

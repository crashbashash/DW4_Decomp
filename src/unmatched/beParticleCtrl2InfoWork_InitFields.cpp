#include "dw4/reflected.h"
extern "C" {
int FUN_0034fd40(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4608[4];
extern int DAT_004c4610[4];
extern int DAT_004c4618[4];
extern int DAT_004c4620[4];
extern int DAT_005884c8[4];
void beParticleCtrl2InfoWork_InitFields(void);
}
void beParticleCtrl2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005884c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4608[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034fd40();
    igMetaObject_NameFields(temp_s0, &DAT_004c4610[0], &DAT_004c4618[0], &DAT_004c4620[0], temp_s2);
}

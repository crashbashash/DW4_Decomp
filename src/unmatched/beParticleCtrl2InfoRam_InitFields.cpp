/* 0x0034bf80 — beParticleCtrl2InfoRam_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00196190(void);
int FUN_0034c080(void);
int FUN_0036e5c0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c45c0[4];
extern int DAT_004c45d0[4];
extern int DAT_004c45e0[4];
extern int DAT_004c45f0[4];
extern int DAT_005884a8[4];
void beParticleCtrl2InfoRam_InitFields(void);
}
void beParticleCtrl2InfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_005884a8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c45c0[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0036e5c0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0034c080();
    igMetaObject_NameFields(temp_s0, &DAT_004c45d0[0], &DAT_004c45e0[0], &DAT_004c45f0[0], temp_s2);
}

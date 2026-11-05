/* 0x003bda80 — beNDMWPanelWazaInfoRam_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003bdb50(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca460[4];
extern int DAT_004ca468[4];
extern int DAT_004ca470[4];
extern int DAT_004ca478[4];
extern int DAT_0058b1f0[4];
void beNDMWPanelWazaInfoRam_InitFields(void);
}
void beNDMWPanelWazaInfoRam_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058b1f0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca460[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003bdb50();
    igMetaObject_NameFields(temp_s0, &DAT_004ca468[0], &DAT_004ca470[0], &DAT_004ca478[0], temp_s2);
}

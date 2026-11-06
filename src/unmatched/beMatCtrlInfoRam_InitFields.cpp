/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003594c0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6000[4];
extern int DAT_004c6008[4];
extern int DAT_004c6010[4];
extern int DAT_004c6018[4];
extern int DAT_005890d8[4];
void beMatCtrlInfoRam_InitFields(void);
}
void beMatCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005890d8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6000[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003594c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6008[0], &DAT_004c6010[0], &DAT_004c6018[0], temp_s2);
}

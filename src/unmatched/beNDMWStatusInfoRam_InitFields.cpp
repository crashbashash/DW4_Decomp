/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003b5f00(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9840[4];
extern int DAT_004c9848[4];
extern int DAT_004c9850[4];
extern int DAT_004c9858[4];
extern int DAT_0058ac38[4];
void beNDMWStatusInfoRam_InitFields(void);
}
void beNDMWStatusInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ac38[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9840[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003b5f00();
    igMetaObject_NameFields(temp_s0, &DAT_004c9848[0], &DAT_004c9850[0], &DAT_004c9858[0], temp_s2);
}

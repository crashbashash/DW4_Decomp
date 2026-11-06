/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003b1dd0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca0d8[4];
extern int DAT_004ca0e8[4];
extern int DAT_004ca0f8[4];
extern int DAT_004ca108[4];
extern int DAT_0058b028[4];
void beNDMWStatus_InitFields(void);
}
void beNDMWStatus_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058b028[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca0d8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003b1dd0();
    igMetaObject_NameFields(temp_s0, &DAT_004ca0e8[0], &DAT_004ca0f8[0], &DAT_004ca108[0], temp_s2);
}

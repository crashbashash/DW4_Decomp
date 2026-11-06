#include "dw4/reflected.h"
int FUN_0044cdf0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004cfff0[4];
extern int DAT_004cfff8[4];
extern int DAT_004d0000[4];
extern int DAT_004d0008[4];
extern int DAT_0058c230[4];
void igRadioGroupSelectedObserver_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c230[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cfff0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cfff8[0], &DAT_004d0000[0], &DAT_004d0008[0], temp_s2);
}

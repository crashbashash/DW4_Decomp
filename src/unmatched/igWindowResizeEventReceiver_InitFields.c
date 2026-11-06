#include "dw4/reflected.h"
int FUN_00232840();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004981f8[4];
extern int DAT_00498200[4];
extern int DAT_00498208[4];
extern int DAT_00498210[4];
extern int DAT_0056dc00[4];
void igWindowResizeEventReceiver_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0056dc00[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004981f8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498200[0], &DAT_00498208[0], &DAT_00498210[0], temp_s2);
}

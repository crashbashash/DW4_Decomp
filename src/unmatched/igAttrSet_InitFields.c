#include "dw4/reflected.h"
int FUN_0013af00();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ce18[4];
extern int DAT_0048ce20[4];
extern int DAT_0048ce28[4];
extern int DAT_0048ce30[4];
extern int DAT_00562078[4];
void igAttrSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562078[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ce18[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &DAT_0048ce20[0], &DAT_0048ce28[0], &DAT_0048ce30[0], temp_s2);
}

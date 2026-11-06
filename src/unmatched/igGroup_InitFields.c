#include "dw4/reflected.h"
int FUN_0019cbe0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048bfe0[4];
extern int DAT_0048bfe8[4];
extern int DAT_0048bff0[4];
extern int DAT_0048bff8[4];
extern int DAT_005619f8[4];
void igGroup_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005619f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048bfe0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cbe0();
    ((igMetaField *)temp_s1)->_resetMethod = 3;
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &DAT_0048bfe8[0], &DAT_0048bff0[0], &DAT_0048bff8[0], temp_s2);
}

#include "dw4/reflected.h"
int FUN_002ca8f0();
int FUN_002cace0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf630[4];
extern int DAT_004bf640[4];
extern int DAT_004bf650[4];
extern int DAT_004bf660[4];
extern int DAT_005858b0[4];
void igStringTable_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_005858b0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf630[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cace0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002ca8f0();
    igMetaObject_NameFields(temp_s0, &DAT_004bf640[0], &DAT_004bf650[0], &DAT_004bf660[0], temp_s2);
}

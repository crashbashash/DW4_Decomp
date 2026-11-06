#include "dw4/reflected.h"
int FUN_002c57c0();
int FUN_002ea4b0();
int FUN_0030eda0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1950[4];
extern int DAT_004c1980[4];
extern int DAT_004c19b0[4];
extern int DAT_004c19e0[4];
extern int DAT_00586b20[4];
void igStackMemoryPool_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00586b20[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1950[0], 0xA);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c57c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c1980[0], &DAT_004c19b0[0], &DAT_004c19e0[0], temp_s2);
}

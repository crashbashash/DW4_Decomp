#include "dw4/reflected.h"
int FUN_002ca2a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0390[4];
extern int DAT_004c03a0[4];
extern int DAT_004c03b0[4];
extern int DAT_004c03c0[4];
extern int DAT_00585fa0[4];
void igMemoryDictionary_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00585fa0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0390[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002ca2a0();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c03a0[0], &DAT_004c03b0[0], &DAT_004c03c0[0], temp_s2);
}

/* The thunk address is a function declaration (an extern int object is gp-relative); one temp. */
#include "dw4/reflected.h"
int FUN_00152800();
int FUN_002c9170();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489d30[4];
extern int DAT_00489d50[4];
extern int DAT_00489d70[4];
extern int DAT_00489d90[4];
extern void * DAT_00560480[4];
int thunk_igVertexArray1_1_GetMetaObject();

void igPsx2VertexArray1_1_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)(DAT_00560480[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489d30[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c9170();
    ((igObjectRefMetaField *)temp_s1)->_persistent = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c9170();
    ((igObjectRefMetaField *)temp_s1)->_persistent = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00152800();
    ((igObjectRefMetaField *)temp_s1)->_persistent = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002ea4b0(temp_s1, -1);
    ((igIntMetaField *)temp_s1)->_persistent = 0;
    ((igLongMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)))->_persistent = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igIntArrayMetaField *)temp_s1)->_num = 0x10;
    ((igIntArrayMetaField *)temp_s1)->_persistent = 0;
    ((igIntMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00489d50[0], &DAT_00489d70[0], &DAT_00489d90[0], temp_s2);
    ((igMetaObject *)(DAT_00560480[0]))->_writeProxy = (int)(&thunk_igVertexArray1_1_GetMetaObject);
}

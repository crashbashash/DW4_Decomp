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
    void *f5;
    void *f1;
    void *f2;
    int temp_s2;
    void *f4;
    void *f3;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00560480[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489d30[0], 7);
    f1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)f1)->_metaObject = FUN_002c9170();
    ((igObjectRefMetaField *)f1)->_persistent = 0;
    f2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)f2)->_metaObject = FUN_002c9170();
    ((igObjectRefMetaField *)f2)->_persistent = 0;
    f3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)f3)->_metaObject = FUN_00152800();
    ((igObjectRefMetaField *)f3)->_persistent = 0;
    f4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002ea4b0(f4, -1);
    ((igIntMetaField *)f4)->_persistent = 0;
    ((igLongMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)))->_persistent = 0;
    f5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igIntArrayMetaField *)f5)->_num = 0x10;
    ((igIntArrayMetaField *)f5)->_persistent = 0;
    ((igIntMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00489d50[0], &DAT_00489d70[0], &DAT_00489d90[0], temp_s2);
    ((igMetaObject *)(DAT_00560480[0]))->_writeProxy = (int)(&thunk_igVertexArray1_1_GetMetaObject);
}

#include "dw4/reflected.h"
int FUN_00145d40();
int igUnsignedIntMetaField_GetDefaultDescriptor();
int FUN_002b7f80();
int FUN_002cfe50();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486d10[4];
extern int DAT_00486d40[4];
extern int DAT_00486d70[4];
extern int DAT_00486da0[4];
extern void * DAT_0055f550[4];
int thunk_igAudioContext_GetMetaObject();

void igPsx2AudioContext_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055f550[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486d10[0], 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cfe50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002b7f80();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00145d40();
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 2);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0x30);
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00145d40();
    igMetaObject_NameFields(temp_s0, &DAT_00486d40[0], &DAT_00486d70[0], &DAT_00486da0[0], temp_s2);
    *(int *)((char *)(DAT_0055f550[0]) + 64) = (int)thunk_igAudioContext_GetMetaObject;
}

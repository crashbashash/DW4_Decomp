#include "dw4/reflected.h"
int igUnsignedCharMetaField_GetDefaultDescriptor();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void thunk_FUN_0014bde0(void);
extern int DAT_00488810[4];
extern int DAT_00488820[4];
extern int DAT_00488830[4];
extern int DAT_00488840[4];
extern void * DAT_0055fb10[4];
void igPrimLengthArray_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055fb10[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488810[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x20);
    igMetaObject_NameFields(temp_s0, &DAT_00488820[0], &DAT_00488830[0], &DAT_00488840[0], temp_s2);
    *(int *)((char *)(DAT_0055fb10[0]) + 60) = (int)(thunk_FUN_0014bde0);
}

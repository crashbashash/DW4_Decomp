#include "dw4/reflected.h"
int FUN_002c04a0(void);
int FUN_002dc7a0(void *, int *);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int igUnsignedCharMetaField_GetDefaultDescriptor(void);
int FUN_001493e0(void);
int thunk_igPsx2IndexArray_GetMetaObject(void);
extern int DAT_00488d40[4];
extern int DAT_00488d60[4];
extern int DAT_00488d80[4];
extern int DAT_00488da0[4];
extern int DAT_00488db8[4];
extern void * DAT_0055fd28[4];
void igIndexArray_InitFields(void);
void igIndexArray_InitFields(void) {
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055fd28[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488d40[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0, &DAT_00488db8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001493e0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002c04a0();
    ((igMetaField *)temp_s1_2)->_resetMethod = 3;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)temp_s1_2)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1_2)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00488d60[0], &DAT_00488d80[0], &DAT_00488da0[0], temp_s2);
    ((igMetaObject *)DAT_0055fd28[0])->_abstractProxy = (int)(&thunk_igPsx2IndexArray_GetMetaObject);
}

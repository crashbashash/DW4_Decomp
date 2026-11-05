/* 0x00335cc0 - igCriMovieData_InitFields. the draft's int stores at odd offset +38 are char stores. Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c28d0[4];
extern int DAT_004c28f0[4];
extern int DAT_004c2910[4];
extern int DAT_004c2930[4];
extern int DAT_00587760[4];
void igCriMovieData_InitFields(void);
}
void igCriMovieData_InitFields(void) {
    void *temp_s0;
    int temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s0 = (void *)DAT_00587760[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c28d0[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igMetaField *)temp_v0)->_size = 4;
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igMetaField *)temp_v0_2)->_size = 4;
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3))->_persistent = 0;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igMetaField *)temp_v0_3)->_size = 4;
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c28f0[0], &DAT_004c2910[0], &DAT_004c2930[0], temp_s1);
}

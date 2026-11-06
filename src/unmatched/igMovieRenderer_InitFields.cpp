/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00336c10(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c2b68[4];
extern int DAT_004c2b70[4];
extern int DAT_004c2b78[4];
extern int DAT_004c2b80[4];
extern int DAT_00587860[4];
void igMovieRenderer_InitFields(void);
}
void igMovieRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587860[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2b68[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00336c10();
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c2b70[0], &DAT_004c2b78[0], &DAT_004c2b80[0], temp_s2);
}

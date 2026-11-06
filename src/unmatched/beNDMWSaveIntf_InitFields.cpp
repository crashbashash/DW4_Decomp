/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00342ce0(void);
int FUN_0034c8e0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca350[4];
extern int DAT_004ca360[4];
extern int DAT_004ca370[4];
extern int DAT_004ca380[4];
extern int DAT_0058b160[4];
void beNDMWSaveIntf_InitFields(void);
}
void beNDMWSaveIntf_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_0058b160[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca350[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004ca360[0], &DAT_004ca370[0], &DAT_004ca380[0], temp_s2);
}

#include "dw4/reflected.h"
extern "C" {
int FUN_002b9120(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8238[4];
extern int DAT_004c8240[4];
extern int DAT_004c8248[4];
extern int DAT_004c8250[4];
extern int DAT_0058a030[4];
void be_InitFields(void);
}
void be_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058a030[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8238[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c8240[0], &DAT_004c8248[0], &DAT_004c8250[0], temp_s2);
}

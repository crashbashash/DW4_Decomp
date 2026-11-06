#include "dw4/reflected.h"
int FUN_00150770();
int FUN_002dc7a0();
int FUN_0030e750();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489fe0[4];
extern int DAT_0048a000[4];
extern int DAT_0048a020[4];
extern int DAT_0048a040[4];
extern int DAT_0048a060[4];
extern int DAT_0048a068[4];
extern int DAT_0048a070[4];
extern int DAT_0048a078[4];
extern int DAT_0048a080[4];
extern int DAT_00560588[4];
int FUN_001535d0();
int FUN_00153630();
int FUN_00153690();

void igPsx2MultiTextureExt_InitFields(void) {
    void *f;
    void *m;
    int base;

    m = (void *)DAT_00560588[0];
    base = igMetaObject_GetFieldCount(m);
    igMetaObject_CreateFields(m, &DAT_00489fe0[0], 8);
    f = igMetaObject_GetFieldAt(m, base);
    ((igObjectRefMetaField *)f)->_metaObject = FUN_00150770();
    ((igObjectRefMetaField *)f)->_refCounted = 0;
    f = igMetaObject_GetFieldAt(m, base + 1);
    FUN_002dc7a0(f, &DAT_0048a060[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153690);
    f = igMetaObject_GetFieldAt(m, base + 3);
    FUN_002dc7a0(f, &DAT_0048a068[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153630);
    f = igMetaObject_GetFieldAt(m, base + 4);
    FUN_002dc7a0(f, &DAT_0048a070[0]);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    f = igMetaObject_GetFieldAt(m, base + 5);
    FUN_002dc7a0(f, &DAT_0048a078[0]);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_001535d0);
    f = igMetaObject_GetFieldAt(m, base + 6);
    FUN_002dc7a0(f, &DAT_0048a080[0]);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    FUN_0030e750(igMetaObject_GetFieldAt(m, base + 7), 0x80);
    igMetaObject_NameFields(m, &DAT_0048a000[0], &DAT_0048a020[0], &DAT_0048a040[0], base);
}

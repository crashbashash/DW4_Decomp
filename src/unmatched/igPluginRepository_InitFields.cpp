#include "dw4/reflected.h"
extern "C" {
int igMetaObject_GetFieldCount(igMetaObject *);
void igMetaObject_CreateFields(igMetaObject *, void *, int);
igMetaField *igMetaObject_GetFieldAt(igMetaObject *, int);
void igMetaObject_NameFields(igMetaObject *, void *, void *, void *, int);
void FUN_002bc8d0(void);
extern int DAT_004bfa58[4];
extern int DAT_004bfa60[4];
extern int DAT_004bfa68[4];
extern int DAT_004bfa70[4];
extern igMetaObject *DAT_00585af0[4];
void igPluginRepository_InitFields(void);
}
void igPluginRepository_InitFields(void) {
    igMetaObject *meta = DAT_00585af0[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaObject_CreateFields(meta, DAT_004bfa58, 2);
    field = igMetaObject_GetFieldAt(meta, base + 1);
    *(int *)((char *)field + 52) = (int)FUN_002bc8d0;
    igMetaObject_NameFields(meta, DAT_004bfa60, DAT_004bfa68, DAT_004bfa70, base);
}

/* 0x002bf1a0 igMetaEnum_Register: registers class igMetaEnum with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMetaEnum_GetVTable[];
extern char thunk_igMetaEnum_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaEnum_callbackList[];
extern char igMetaEnum_className[];
extern char g_igMetaEnum_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMetaEnum_InitFields();

void igMetaEnum_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaEnum_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMetaEnum_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igMetaEnum_className,       /* class name */
        0x14,                                  /* instance size */
        igMetaEnum_GetVTable,                  /* vtable getter */
        &igMetaEnum_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        g_igMetaEnum_callbackList     /* callback list */
    );
}

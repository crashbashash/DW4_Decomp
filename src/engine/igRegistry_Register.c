/* 0x002bb210 igRegistry_Register: registers class igRegistry with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRegistry_GetVTable[];
extern char thunk_igRegistry_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRegistry_callbackList[];
extern char igRegistry_className[];
extern char g_igRegistry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRegistry_InitFields();

void igRegistry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRegistry_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRegistry_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igRegistry_className,       /* class name */
        0x18,                                  /* instance size */
        igRegistry_GetVTable,                  /* vtable getter */
        &igRegistry_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        g_igRegistry_callbackList     /* callback list */
    );
}

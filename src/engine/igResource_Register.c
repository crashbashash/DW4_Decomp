/* 0x002bad50 igResource_Register: registers class igResource with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igResource_GetVTable[];
extern char thunk_igResource_GetMetaObject[];
extern char igObject_Register[];
extern char g_igResource_callbackList[];
extern char igResource_className[];
extern char g_igResource_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igResource_InitFields();

void igResource_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igResource_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igResource_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igResource_className,       /* class name */
        0x4C,                                  /* instance size */
        igResource_GetVTable,                  /* vtable getter */
        &igResource_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        g_igResource_callbackList     /* callback list */
    );
}

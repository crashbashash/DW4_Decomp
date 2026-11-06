/* 0x002bc5d0 igPluginHelper_Register: registers class igPluginHelper with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igPluginHelper_GetVTable[];
extern char thunk_igPluginHelper_GetMetaObject[];
extern char igObject_Register[];
extern char g_igPluginHelper_callbackList[];
extern char igPluginHelper_className[];
extern char g_igPluginHelper_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPluginHelper_InitFields();

void igPluginHelper_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPluginHelper_metaObject,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igPluginHelper_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igPluginHelper_className,   /* class name */
        0x18,                                  /* instance size */
        igPluginHelper_GetVTable,              /* vtable getter */
        &igPluginHelper_InitFields,            /* field adder */
        0,                                     /* extra callback item */
        g_igPluginHelper_callbackList  /* callback list */
    );
}

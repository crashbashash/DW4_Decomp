/* 0x002bb680 igRegistryValue_Register: registers class igRegistryValue with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRegistryValue_GetVTable[];
extern char thunk_igRegistryValue_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRegistryValue_callbackList[];
extern char igRegistryValue_className[];
extern char g_igRegistryValue_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRegistryValue_InitFields();

void igRegistryValue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRegistryValue_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRegistryValue_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igRegistryValue_className,  /* class name */
        0x14,                                  /* instance size */
        igRegistryValue_GetVTable,             /* vtable getter */
        &igRegistryValue_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igRegistryValue_callbackList  /* callback list */
    );
}

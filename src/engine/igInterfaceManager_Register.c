/* 0x00145f70 igInterfaceManager_Register: registers class igInterfaceManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInterfaceManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInterfaceManager_callbackList[];
extern char igInterfaceManager_className[];
extern char g_igInterfaceManager_metaObject[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igInterfaceManager_InitFields();

void igInterfaceManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        1,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInterfaceManager_metaObject, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igInterfaceManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igInterfaceManager_className,  /* class name */
        0xC,                                      /* instance size */
        0,                                        /* vtable getter */
        &igInterfaceManager_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igInterfaceManager_callbackList  /* callback list */
    );
}

/* igDefaultInterfaceManager_Register: static-init registration of igDefaultInterfaceManager,
 * derived from igInterfaceManager (instance size 0x4C; fields added by
 * igDefaultInterfaceManager_InitFields). The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
 * GpFlag_SetOnce_00145ce0 is a set-once latch (it only sets a gp byte flag). thunk_FUN_00146470 is
 * the class's own get-or-register MetaObject accessor stub (a jump to the accessor body at
 * 0x00146470). */
extern char igInterfaceManager_Register[];
void thunk_FUN_00146470(void);
extern char igDefaultInterfaceManager_GetVTable[];
extern char igInterfaceManager_GetPublishedMetaObject[];
extern char igDefaultInterfaceManager_className[];
extern char g_igDefaultInterfaceManager_metaObject[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igDefaultInterfaceManager_InitFields();

void igDefaultInterfaceManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultInterfaceManager_metaObject,    /* published MetaObject slot */
        igInterfaceManager_Register,                        /* base class registrar (igInterfaceManager) */
        igInterfaceManager_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_00146470,                                       /* own MetaObject accessor (stored at +0x54) */
        igDefaultInterfaceManager_className,     /* class name */
        0x4C,                                               /* instance size */
        igDefaultInterfaceManager_GetVTable,                /* vtable getter */
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0,                                                  /* extra callback item */
        0                                                   /* callback list */
    );
}

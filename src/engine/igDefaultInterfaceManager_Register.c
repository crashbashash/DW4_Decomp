/* 0x00146570 igDefaultInterfaceManager_Register: static-init registration of igDefaultInterfaceManager,
 * derived from igInterfaceManager (instance size 0x4C; fields added by igDefaultInterfaceManager_InitFields).
 * The igMetaObject_RegisterClass arguments are laid out per docs/engine/reflection-metadata.md
 * section 1 (finding #358); names from data/reflection.json.
 * GpFlag_SetOnce_00145ce0 is a set-once latch (it only sets a gp byte flag). thunk_FUN_00146470 is the class's own
 * get-or-register MetaObject accessor stub (a jump to the accessor body at 0x00146470). */
extern char igInterfaceManager_Register[];
void thunk_FUN_00146470(void);  /* code at 0x1460a0, passed by address (was DAT_1460a0; docs/engine/function-inventory.md) */
extern char igDefaultInterfaceManager_GetVTable[];
extern char igInterfaceManager_GetPublishedMetaObject_001465e0[];
extern char s_igDefaultInterfaceManager_className_004d6570[];
extern char g_igDefaultInterfaceManager_metaObject_0055f610[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igDefaultInterfaceManager_InitFields();

void igDefaultInterfaceManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultInterfaceManager_metaObject_0055f610,    /* published MetaObject slot */
        igInterfaceManager_Register,                        /* base class registrar (igInterfaceManager) */
        igInterfaceManager_GetPublishedMetaObject_001465e0, /* base class MetaObject accessor */
        thunk_FUN_00146470,                                       /* own MetaObject accessor (stored at +0x54) */
        s_igDefaultInterfaceManager_className_004d6570,     /* class name */
        0x4C,                                               /* instance size */
        igDefaultInterfaceManager_GetVTable,                /* vtable getter */
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0,                                                  /* extra callback item */
        0                                                   /* callback list */
    );
}

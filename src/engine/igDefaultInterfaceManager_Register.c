/* Static-init registration of igDefaultInterfaceManager, derived from igInterfaceManager (instance
 * size 0x4C). WindowInputLibrary_MarkRegistered is a set-once latch (it only sets a gp byte flag).
 * thunk_FUN_00146470 is the class's own get-or-register MetaObject accessor stub. */
extern char igInterfaceManager_Register[];
void thunk_FUN_00146470(void);
extern char igDefaultInterfaceManager_GetVTable[];
extern char igInterfaceManager_GetPublishedMetaObject[];
extern char igDefaultInterfaceManager_className[];
extern char g_igDefaultInterfaceManager_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDefaultInterfaceManager_InitFields();

void igDefaultInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultInterfaceManager_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_FUN_00146470,
        igDefaultInterfaceManager_className,
        0x4C, /* instance size */
        igDefaultInterfaceManager_GetVTable,
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

/* 0x00226bf0 igLockBase_Register: registers class igLockBase with the object system, derived from igInterfaced.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaced_GetPublishedMetaObject[];
extern char thunk_igLockBase_GetMetaObject[];
extern char igInterfaced_Register[];
extern char igLockBase_className[];
extern char g_igLockBase_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igLockBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLockBase_metaObject,             /* published MetaObject slot */
        igInterfaced_Register,                        /* base class registrar */
        igInterfaced_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLockBase_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igLockBase_className,              /* class name */
        0x20,                                         /* instance size */
        0,                                            /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}

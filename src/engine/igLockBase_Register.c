/* 0x00226bf0 igLockBase_Register: registers class igLockBase with the object system, derived from igInterfaced.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaced_GetPublishedMetaObject_002265d0[];
extern char thunk_igLockBase_GetMetaObject[];
extern char igInterfaced_Register[];
extern char s_igLockBase_className_004e7b38[];
extern char g_igLockBase_metaObject_0056d8f8[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igLockBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLockBase_metaObject_0056d8f8,             /* published MetaObject slot */
        igInterfaced_Register,                        /* base class registrar */
        igInterfaced_GetPublishedMetaObject_002265d0, /* base class MetaObject accessor */
        thunk_igLockBase_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igLockBase_className_004e7b38,              /* class name */
        0x20,                                         /* instance size */
        0,                                            /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}

/* 0x00228c70 igInterface_Register: registers class igInterface with the object system, derived from igInterfaced.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaced_GetPublishedMetaObject_002265d0[];
extern char igInterfaced_Register[];
extern char igInterface_GetVTable[];
extern char thunk_igInterface_GetMetaObject[];
extern char s_igInterface_className_004e7e18[];
extern char g_igInterface_metaObject_0056da28[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInterface_metaObject_0056da28,            /* published MetaObject slot */
        igInterfaced_Register,                        /* base class registrar */
        igInterfaced_GetPublishedMetaObject_002265d0, /* base class MetaObject accessor */
        thunk_igInterface_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igInterface_className_004e7e18,             /* class name */
        0x20,                                         /* instance size */
        igInterface_GetVTable,                        /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}

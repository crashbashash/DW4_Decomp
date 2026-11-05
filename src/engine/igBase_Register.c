/* 0x002292e0 igBase_Register: registers class igBase with the object system, derived from igInterfaced.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaced_GetPublishedMetaObject_002265d0[];
extern char igInterfaced_Register[];
extern char thunk_igBase_GetMetaObject[];
extern char s_igBase_className_004e7e98[];
extern char g_igBase_metaObject_0056da60[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBase_metaObject_0056da60,                 /* published MetaObject slot */
        igInterfaced_Register,                        /* base class registrar */
        igInterfaced_GetPublishedMetaObject_002265d0, /* base class MetaObject accessor */
        thunk_igBase_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        s_igBase_className_004e7e98,                  /* class name */
        0x20,                                         /* instance size */
        0,                                            /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}

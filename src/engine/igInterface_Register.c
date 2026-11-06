/* 0x00228c70 igInterface_Register: registers class igInterface with the object system, derived from igInterfaced.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaced_GetPublishedMetaObject[];
extern char igInterfaced_Register[];
extern char igInterface_GetVTable[];
extern char thunk_igInterface_GetMetaObject[];
extern char igInterface_className[];
extern char g_igInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInterface_metaObject,            /* published MetaObject slot */
        igInterfaced_Register,                        /* base class registrar */
        igInterfaced_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igInterface_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igInterface_className,             /* class name */
        0x20,                                         /* instance size */
        igInterface_GetVTable,                        /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}

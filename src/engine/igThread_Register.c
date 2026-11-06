/* 0x002b8030 igThread_Register: registers class igThread with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igThread_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igThread_className[];
extern char g_igThread_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igThread_InitFields();

void igThread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igThread_metaObject,                /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igThread_GetMetaObject,                  /* own MetaObject accessor (stored at +0x54) */
        igThread_className,                 /* class name */
        0x30,                                          /* instance size */
        0,                                             /* vtable getter */
        &igThread_InitFields,                          /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

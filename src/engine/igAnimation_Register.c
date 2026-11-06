/* 0x001a92a0 igAnimation_Register: registers class igAnimation with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igAnimation_GetVTable[];
extern char thunk_igAnimation_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimation_callbackList[];
extern char igAnimation_className[];
extern char g_igAnimation_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimation_InitFields();

void igAnimation_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimation_metaObject,             /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimation_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igAnimation_className,              /* class name */
        0x40,                                          /* instance size */
        igAnimation_GetVTable,                         /* vtable getter */
        &igAnimation_InitFields,                       /* field adder */
        0,                                             /* extra callback item */
        g_igAnimation_callbackList            /* callback list */
    );
}

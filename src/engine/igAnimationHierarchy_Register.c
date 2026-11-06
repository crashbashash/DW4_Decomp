/* 0x001a71b0 igAnimationHierarchy_Register: registers class igAnimationHierarchy with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igAnimationHierarchy_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igAnimationHierarchy_className[];
extern char g_igAnimationHierarchy_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationHierarchy_InitFields();

void igAnimationHierarchy_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationHierarchy_metaObject,    /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimationHierarchy_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igAnimationHierarchy_className,     /* class name */
        0x10,                                          /* instance size */
        0,                                             /* vtable getter */
        &igAnimationHierarchy_InitFields,              /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

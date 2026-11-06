/* 0x00195590 igTransformSequence_Register: registers class igTransformSequence with the object system, derived from igTransformSource.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransformSource_Register[];
extern char thunk_igTransformSequence_GetMetaObject[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char g_igTransformSequence_callbackList[];
extern char igTransformSequence_className[];
extern char g_igTransformSequence_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransformSequence_InitFields();

void igTransformSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformSequence_metaObject,         /* published MetaObject slot */
        igTransformSource_Register,                        /* base class registrar */
        igTransformSource_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTransformSequence_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igTransformSequence_className,          /* class name */
        0x38,                                              /* instance size */
        0,                                                 /* vtable getter */
        &igTransformSequence_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        g_igTransformSequence_callbackList        /* callback list */
    );
}

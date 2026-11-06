/* 0x00195c10 igTransformRecorder_Register: registers class igTransformRecorder with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igTransformRecorder_GetVTable[];
extern char thunk_igTransformRecorder_GetMetaObject[];
extern char igGroup_Register[];
extern char igTransformRecorder_className[];
extern char g_igTransformRecorder_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransformRecorder_InitFields();

void igTransformRecorder_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformRecorder_metaObject, /* published MetaObject slot */
        igGroup_Register,                          /* base class registrar */
        igGroup_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igTransformRecorder_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igTransformRecorder_className,  /* class name */
        0xA0,                                      /* instance size */
        igTransformRecorder_GetVTable,             /* vtable getter */
        &igTransformRecorder_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}

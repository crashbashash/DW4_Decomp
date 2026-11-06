/* 0x001a84a0 igAnimationCombinerList_Register: registers class igAnimationCombinerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerList_GetVTable[];
extern char thunk_igAnimationCombinerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerList_callbackList[];
extern char igAnimationCombinerList_className[];
extern char g_igAnimationCombinerList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationCombinerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                         /* base class registrar */
        igObjectList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igAnimationCombinerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationCombinerList_className,  /* class name */
        0x14,                                          /* instance size */
        igAnimationCombinerList_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igAnimationCombinerList_callbackList  /* callback list */
    );
}

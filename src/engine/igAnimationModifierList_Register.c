/* 0x001a73c0 igAnimationModifierList_Register: registers class igAnimationModifierList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationModifierList_GetVTable[];
extern char thunk_igAnimationModifierList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationModifierList_callbackList[];
extern char igAnimationModifierList_className[];
extern char g_igAnimationModifierList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationModifierList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationModifierList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                         /* base class registrar */
        igObjectList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igAnimationModifierList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationModifierList_className,  /* class name */
        0x14,                                          /* instance size */
        igAnimationModifierList_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igAnimationModifierList_callbackList  /* callback list */
    );
}

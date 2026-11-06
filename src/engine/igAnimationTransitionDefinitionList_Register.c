/* 0x001a9510 igAnimationTransitionDefinitionList_Register: registers class igAnimationTransitionDefinitionList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTransitionDefinitionList_GetVTable[];
extern char thunk_igAnimationTransitionDefinitionList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTransitionDefinitionList_callbackList[];
extern char igAnimationTransitionDefinitionList_className[];
extern char g_igAnimationTransitionDefinitionList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationTransitionDefinitionList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTransitionDefinitionList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,                       /* base class MetaObject accessor */
        thunk_igAnimationTransitionDefinitionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationTransitionDefinitionList_className,  /* class name */
        0x14,                                                      /* instance size */
        igAnimationTransitionDefinitionList_GetVTable,             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igAnimationTransitionDefinitionList_callbackList  /* callback list */
    );
}

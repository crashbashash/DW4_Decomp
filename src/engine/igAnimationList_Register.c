/* 0x001a9070 igAnimationList_Register: registers class igAnimationList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationList_GetVTable[];
extern char thunk_igAnimationList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationList_callbackList[];
extern char igAnimationList_className[];
extern char g_igAnimationList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igAnimationList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationList_className,  /* class name */
        0x14,                                  /* instance size */
        igAnimationList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igAnimationList_callbackList  /* callback list */
    );
}

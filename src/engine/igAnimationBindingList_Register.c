/* 0x001a8bb0 igAnimationBindingList_Register: registers class igAnimationBindingList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationBindingList_GetVTable[];
extern char thunk_igAnimationBindingList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationBindingList_callbackList_0048d458[];
extern char s_igAnimationBindingList_className_004e4060[];
extern char g_igAnimationBindingList_metaObject_00562330[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationBindingList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationBindingList_metaObject_00562330, /* published MetaObject slot */
        igObjectList_Register,                        /* base class registrar */
        igObjectList_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igAnimationBindingList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationBindingList_className_004e4060,  /* class name */
        0x14,                                         /* instance size */
        igAnimationBindingList_GetVTable,             /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igAnimationBindingList_callbackList_0048d458  /* callback list */
    );
}

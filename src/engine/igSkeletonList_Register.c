/* 0x001984d0 igSkeletonList_Register: registers class igSkeletonList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igSkeletonList_GetVTable[];
extern char thunk_igSkeletonList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkeletonList_callbackList[];
extern char igSkeletonList_className[];
extern char g_igSkeletonList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSkeletonList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkeletonList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igSkeletonList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igSkeletonList_className,  /* class name */
        0x14,                                 /* instance size */
        igSkeletonList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igSkeletonList_callbackList  /* callback list */
    );
}

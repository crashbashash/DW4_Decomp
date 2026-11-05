/* 0x001988e0 igSkeletonBoneInfoList_Register: registers class igSkeletonBoneInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igSkeletonBoneInfoList_GetVTable[];
extern char thunk_igSkeletonBoneInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkeletonBoneInfoList_callbackList_0048b5d0[];
extern char s_igSkeletonBoneInfoList_className_004e1ae0[];
extern char g_igSkeletonBoneInfoList_metaObject_005614d0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igSkeletonBoneInfoList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkeletonBoneInfoList_metaObject_005614d0, /* published MetaObject slot */
        igObjectList_Register,                        /* base class registrar */
        igObjectList_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igSkeletonBoneInfoList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igSkeletonBoneInfoList_className_004e1ae0,  /* class name */
        0x14,                                         /* instance size */
        igSkeletonBoneInfoList_GetVTable,             /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igSkeletonBoneInfoList_callbackList_0048b5d0  /* callback list */
    );
}

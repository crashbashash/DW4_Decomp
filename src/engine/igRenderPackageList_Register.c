/* 0x001978b0 igRenderPackageList_Register: registers class igRenderPackageList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igRenderPackageList_GetVTable[];
extern char thunk_igRenderPackageList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igRenderPackageList_callbackList[];
extern char igRenderPackageList_className[];
extern char g_igRenderPackageList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igRenderPackageList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderPackageList_metaObject,                 /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igRenderPackageList_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        igRenderPackageList_className,                  /* class name */
        0x14,                                                      /* instance size */
        igRenderPackageList_GetVTable,                             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igRenderPackageList_callbackList                /* callback list */
    );
}

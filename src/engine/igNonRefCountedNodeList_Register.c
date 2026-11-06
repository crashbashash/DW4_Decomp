/* 0x0019c9b0 igNonRefCountedNodeList_Register: registers class igNonRefCountedNodeList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedNodeList_GetVTable[];
extern char thunk_igNonRefCountedNodeList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedNodeList_callbackList[];
extern char igNonRefCountedNodeList_className[];
extern char g_igNonRefCountedNodeList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedNodeList_metaObject,             /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedNodeList_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedNodeList_className,              /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedNodeList_GetVTable,                         /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedNodeList_callbackList            /* callback list */
    );
}

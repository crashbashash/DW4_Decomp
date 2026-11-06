/* 0x0044b970 igNonRefCountedViewList_Register: registers class igNonRefCountedViewList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char igNonRefCountedViewList_GetVTable[];
extern char thunk_igNonRefCountedViewList_GetMetaObject[];
extern char g_igNonRefCountedViewList_callbackList[];
extern char igNonRefCountedViewList_className[];
extern char g_igNonRefCountedViewList_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igNonRefCountedViewList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedViewList_metaObject,             /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedViewList_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedViewList_className,              /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedViewList_GetVTable,                         /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedViewList_callbackList            /* callback list */
    );
}

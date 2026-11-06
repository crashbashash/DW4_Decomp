/* 0x0013ae30 igNonRefCountedAttrList_Register: registers class igNonRefCountedAttrList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedAttrList_GetVTable[];
extern char thunk_igNonRefCountedAttrList_GetMetaObject[];
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedAttrList_callbackList[];
extern char igNonRefCountedAttrList_className[];
extern char g_igNonRefCountedAttrList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igNonRefCountedAttrList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedAttrList_metaObject,             /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedAttrList_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedAttrList_className,              /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedAttrList_GetVTable,                         /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedAttrList_callbackList            /* callback list */
    );
}

/* 0x00195df0 igNonRefCountedTransformList_Register: registers class igNonRefCountedTransformList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedTransformList_GetVTable[];
extern char thunk_igNonRefCountedTransformList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedTransformList_callbackList[];
extern char igNonRefCountedTransformList_className[];
extern char g_igNonRefCountedTransformList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igNonRefCountedTransformList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedTransformList_metaObject,        /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedTransformList_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedTransformList_className,         /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedTransformList_GetVTable,                    /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedTransformList_callbackList       /* callback list */
    );
}

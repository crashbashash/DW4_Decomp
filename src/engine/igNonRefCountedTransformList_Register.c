/* 0x00195df0 igNonRefCountedTransformList_Register: registers class igNonRefCountedTransformList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0[];
extern char igNonRefCountedTransformList_GetVTable[];
extern char thunk_igNonRefCountedTransformList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedTransformList_callbackList_0048b160[];
extern char s_igNonRefCountedTransformList_className_004e1550[];
extern char g_igNonRefCountedTransformList_metaObject_00561298[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igNonRefCountedTransformList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedTransformList_metaObject_00561298,        /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0, /* base class MetaObject accessor */
        thunk_igNonRefCountedTransformList_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igNonRefCountedTransformList_className_004e1550,         /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedTransformList_GetVTable,                    /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedTransformList_callbackList_0048b160       /* callback list */
    );
}

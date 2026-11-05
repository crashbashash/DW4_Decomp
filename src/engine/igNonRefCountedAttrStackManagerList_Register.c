/* 0x001a52b0 igNonRefCountedAttrStackManagerList_Register: registers class igNonRefCountedAttrStackManagerList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0[];
extern char igNonRefCountedAttrStackManagerList_GetVTable[];
extern char thunk_igNonRefCountedAttrStackManagerList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedAttrStackManagerList_callbackList_0048cc00[];
extern char s_igNonRefCountedAttrStackManagerList_className_004e3480[];
extern char g_igNonRefCountedAttrStackManagerList_metaObject_00561f90[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igNonRefCountedAttrStackManagerList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedAttrStackManagerList_metaObject_00561f90, /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0, /* base class MetaObject accessor */
        thunk_igNonRefCountedAttrStackManagerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igNonRefCountedAttrStackManagerList_className_004e3480,  /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedAttrStackManagerList_GetVTable,             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedAttrStackManagerList_callbackList_0048cc00  /* callback list */
    );
}

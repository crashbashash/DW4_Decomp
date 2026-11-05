/* 0x001e4a60 igNonRefCountedMatrixObjectList_Register: registers class igNonRefCountedMatrixObjectList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0[];
extern char igNonRefCountedMatrixObjectList_GetVTable[];
extern char thunk_igNonRefCountedMatrixObjectList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedMatrixObjectList_callbackList_0048db10[];
extern char s_igNonRefCountedMatrixObjectList_className_004e4940[];
extern char g_igNonRefCountedMatrixObjectList_metaObject_00562bb0[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();

void igNonRefCountedMatrixObjectList_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedMatrixObjectList_metaObject_00562bb0,     /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0, /* base class MetaObject accessor */
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igNonRefCountedMatrixObjectList_className_004e4940,      /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,                 /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList_0048db10    /* callback list */
    );
}

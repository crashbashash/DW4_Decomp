/* 0x001e4a60 igNonRefCountedMatrixObjectList_Register: registers class igNonRefCountedMatrixObjectList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedMatrixObjectList_GetVTable[];
extern char thunk_igNonRefCountedMatrixObjectList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedMatrixObjectList_callbackList[];
extern char igNonRefCountedMatrixObjectList_className[];
extern char g_igNonRefCountedMatrixObjectList_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedMatrixObjectList_metaObject,     /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedMatrixObjectList_className,      /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,                 /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList    /* callback list */
    );
}

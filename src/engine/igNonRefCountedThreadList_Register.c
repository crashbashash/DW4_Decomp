/* 0x002b8310 igNonRefCountedThreadList_Register: registers class igNonRefCountedThreadList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedThreadList_GetVTable[];
extern char thunk_igNonRefCountedThreadList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedThreadList_callbackList[];
extern char igNonRefCountedThreadList_className[];
extern char g_igNonRefCountedThreadList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igNonRefCountedThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNonRefCountedThreadList_metaObject,           /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNonRefCountedThreadList_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igNonRefCountedThreadList_className,            /* class name */
        0x14,                                                      /* instance size */
        igNonRefCountedThreadList_GetVTable,                       /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igNonRefCountedThreadList_callbackList          /* callback list */
    );
}

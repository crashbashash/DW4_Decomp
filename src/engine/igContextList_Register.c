/* 0x002cbae0 igContextList_Register: registers class igContextList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char igContextList_GetVTable[];
extern char thunk_igContextList_GetMetaObject[];
extern char g_igContextList_callbackList[];
extern char igContextList_className[];
extern char g_igContextList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextList_metaObject,                       /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igContextList_GetMetaObject,                         /* own MetaObject accessor (stored at +0x54) */
        igContextList_className,                        /* class name */
        0x14,                                                      /* instance size */
        igContextList_GetVTable,                                   /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igContextList_callbackList                      /* callback list */
    );
}

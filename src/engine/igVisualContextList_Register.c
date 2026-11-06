/* 0x00149f80 igVisualContextList_Register: registers class igVisualContextList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igVisualContextList_GetVTable[];
extern char thunk_igVisualContextList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igVisualContextList_callbackList[];
extern char igVisualContextList_className[];
extern char g_igVisualContextList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igVisualContextList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualContextList_metaObject,                 /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVisualContextList_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        igVisualContextList_className,                  /* class name */
        0x14,                                                      /* instance size */
        igVisualContextList_GetVTable,                             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igVisualContextList_callbackList                /* callback list */
    );
}

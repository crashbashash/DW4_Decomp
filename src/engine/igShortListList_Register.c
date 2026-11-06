/* 0x002c9d00 igShortListList_Register: registers class igShortListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igShortListList_GetVTable[];
extern char thunk_igShortListList_GetMetaObject[];
extern char g_igShortListList_callbackList[];
extern char igShortListList_className[];
extern char g_igShortListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igShortListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShortListList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igShortListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igShortListList_className,  /* class name */
        0x14,                                  /* instance size */
        igShortListList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igShortListList_callbackList  /* callback list */
    );
}

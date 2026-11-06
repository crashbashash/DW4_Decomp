/* 0x002c0ae0 igMemoryFileEntryList_Register: registers class igMemoryFileEntryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMemoryFileEntryList_GetVTable[];
extern char thunk_igMemoryFileEntryList_GetMetaObject[];
extern char g_igMemoryFileEntryList_callbackList[];
extern char igMemoryFileEntryList_className[];
extern char g_igMemoryFileEntryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryFileEntryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryFileEntryList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                       /* base class registrar */
        igObjectList_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igMemoryFileEntryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMemoryFileEntryList_className,  /* class name */
        0x14,                                        /* instance size */
        igMemoryFileEntryList_GetVTable,             /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igMemoryFileEntryList_callbackList  /* callback list */
    );
}

/* 0x002c7240 igDirectoryList_Register: registers class igDirectoryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDirectoryList_GetVTable[];
extern char thunk_igDirectoryList_GetMetaObject[];
extern char g_igDirectoryList_callbackList_004c10e8[];
extern char s_igDirectoryList_className_004f8140[];
extern char g_igDirectoryList_metaObject_00586660[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDirectoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDirectoryList_metaObject_00586660, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igDirectoryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDirectoryList_className_004f8140,  /* class name */
        0x14,                                  /* instance size */
        igDirectoryList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igDirectoryList_callbackList_004c10e8  /* callback list */
    );
}

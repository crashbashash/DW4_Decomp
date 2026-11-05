/* 0x002c24a0 igLibraryList_Register: registers class igLibraryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igLibraryList_GetVTable[];
extern char thunk_igLibraryList_GetMetaObject[];
extern char g_igLibraryList_callbackList_004c0598[];
extern char s_igLibraryList_className_004f6f50[];
extern char g_igLibraryList_metaObject_005860b8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLibraryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLibraryList_metaObject_005860b8, /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLibraryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igLibraryList_className_004f6f50,  /* class name */
        0x14,                                /* instance size */
        igLibraryList_GetVTable,             /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igLibraryList_callbackList_004c0598  /* callback list */
    );
}

/* 0x002c52e0 igExternalIndexedEntry_Register: registers class igExternalIndexedEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalIndexedEntry_GetVTable[];
extern char thunk_igExternalIndexedEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igExternalIndexedEntry_callbackList[];
extern char igExternalIndexedEntry_className[];
extern char g_igExternalIndexedEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igExternalIndexedEntry_InitFields();

void igExternalIndexedEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalIndexedEntry_metaObject, /* published MetaObject slot */
        igDirEntry_Register,                          /* base class registrar */
        igDirEntry_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igExternalIndexedEntry_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igExternalIndexedEntry_className,  /* class name */
        0x34,                                         /* instance size */
        igExternalIndexedEntry_GetVTable,             /* vtable getter */
        &igExternalIndexedEntry_InitFields,           /* field adder */
        0,                                            /* extra callback item */
        g_igExternalIndexedEntry_callbackList  /* callback list */
    );
}

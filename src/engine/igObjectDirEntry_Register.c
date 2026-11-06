/* 0x002bda20 igObjectDirEntry_Register: registers class igObjectDirEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectDirEntry_GetVTable[];
extern char thunk_igObjectDirEntry_GetMetaObject[];
extern char igDirEntry_GetPublishedMetaObject[];
extern char igDirEntry_Register[];
extern char g_igObjectDirEntry_callbackList[];
extern char igObjectDirEntry_className[];
extern char g_igObjectDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectDirEntry_InitFields();

void igObjectDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectDirEntry_metaObject,     /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igObjectDirEntry_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igObjectDirEntry_className,      /* class name */
        0x34,                                       /* instance size */
        igObjectDirEntry_GetVTable,                 /* vtable getter */
        &igObjectDirEntry_InitFields,               /* field adder */
        0,                                          /* extra callback item */
        g_igObjectDirEntry_callbackList    /* callback list */
    );
}

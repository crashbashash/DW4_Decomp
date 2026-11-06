/* 0x002c7910 igDirEntry_Register: registers class igDirEntry with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char igDirEntry_GetVTable[];
extern char thunk_igDirEntry_GetMetaObject[];
extern char igDirEntry_className[];
extern char g_igDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDirEntry_InitFields();

void igDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDirEntry_metaObject,              /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDirEntry_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igDirEntry_className,               /* class name */
        0x1C,                                          /* instance size */
        igDirEntry_GetVTable,                          /* vtable getter */
        &igDirEntry_InitFields,                        /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

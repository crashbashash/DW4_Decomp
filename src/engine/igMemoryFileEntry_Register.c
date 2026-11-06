/* 0x002c0c90 igMemoryFileEntry_Register: registers class igMemoryFileEntry with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char igMemoryFileEntry_GetVTable[];
extern char thunk_igMemoryFileEntry_GetMetaObject[];
extern char igMemoryFileEntry_className[];
extern char g_igMemoryFileEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryFileEntry_InitFields();

void igMemoryFileEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryFileEntry_metaObject,       /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMemoryFileEntry_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igMemoryFileEntry_className,        /* class name */
        0x14,                                          /* instance size */
        igMemoryFileEntry_GetVTable,                   /* vtable getter */
        &igMemoryFileEntry_InitFields,                 /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

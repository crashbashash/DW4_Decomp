/* 0x002c50b0 igExternalInfoEntry_Register: registers class igExternalInfoEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalInfoEntry_GetVTable[];
extern char thunk_igExternalInfoEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char igExternalInfoEntry_className[];
extern char g_igExternalInfoEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igExternalInfoEntry_InitFields();

void igExternalInfoEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalInfoEntry_metaObject,  /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igExternalInfoEntry_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igExternalInfoEntry_className,   /* class name */
        0x28,                                       /* instance size */
        igExternalInfoEntry_GetVTable,              /* vtable getter */
        &igExternalInfoEntry_InitFields,            /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}

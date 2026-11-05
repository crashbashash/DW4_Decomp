/* 0x002c50b0 igExternalInfoEntry_Register: registers class igExternalInfoEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject_002bdab0[];
extern char igExternalInfoEntry_GetVTable[];
extern char thunk_igExternalInfoEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char s_igExternalInfoEntry_className_004f77e0[];
extern char g_igExternalInfoEntry_metaObject_005863f8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igExternalInfoEntry_InitFields();

void igExternalInfoEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalInfoEntry_metaObject_005863f8,  /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject_002bdab0, /* base class MetaObject accessor */
        thunk_igExternalInfoEntry_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igExternalInfoEntry_className_004f77e0,   /* class name */
        0x28,                                       /* instance size */
        igExternalInfoEntry_GetVTable,              /* vtable getter */
        &igExternalInfoEntry_InitFields,            /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}

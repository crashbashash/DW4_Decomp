/* 0x002d0120 igPsx2Folder_Register: registers class igPsx2Folder with the object system, derived from igFolder.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFolder_Register[];
extern char thunk_igPsx2Folder_GetMetaObject[];
extern char igPsx2Folder_GetVTable[];
extern char igFolder_GetPublishedMetaObject_002d0190[];
extern char s_igPsx2Folder_className_004f8ff8[];
extern char g_igPsx2Folder_metaObject_00586d68[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPsx2Folder_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Folder_metaObject_00586d68,       /* published MetaObject slot */
        igFolder_Register,                        /* base class registrar */
        igFolder_GetPublishedMetaObject_002d0190, /* base class MetaObject accessor */
        thunk_igPsx2Folder_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2Folder_className_004f8ff8,        /* class name */
        0xC,                                      /* instance size */
        igPsx2Folder_GetVTable,                   /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        0                                         /* callback list */
    );
}

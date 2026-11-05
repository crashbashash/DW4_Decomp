/* 0x002ced80 igElfFile_Register: registers class igElfFile with the object system, derived from igProgramFile.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igProgramFile_Register[];
extern char thunk_igElfFile_GetMetaObject[];
extern char igElfFile_GetVTable[];
extern char igProgramFile_GetPublishedMetaObject_002cedf0[];
extern char s_igElfFile_className_004f8ce0[];
extern char g_igElfFile_metaObject_00586c00[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igElfFile_InitFields();

void igElfFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igElfFile_metaObject_00586c00,               /* published MetaObject slot */
        igProgramFile_Register,                        /* base class registrar */
        igProgramFile_GetPublishedMetaObject_002cedf0, /* base class MetaObject accessor */
        thunk_igElfFile_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        s_igElfFile_className_004f8ce0,                /* class name */
        0x64,                                          /* instance size */
        igElfFile_GetVTable,                           /* vtable getter */
        &igElfFile_InitFields,                         /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

/* 0x002d02c0 igPsx2File_Register: registers class igPsx2File with the object system, derived from igFile.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFile_GetPublishedMetaObject_002c0930[];
extern char igFile_Register[];
extern char thunk_igPsx2File_GetMetaObject[];
extern char igPsx2File_GetVTable[];
extern char thunk_FUN_0032c0c0[];
extern char s_igPsx2File_className_004f9008[];
extern char g_igPsx2File_metaObject_00586d70[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2File_InitFields();

void igPsx2File_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2File_metaObject_00586d70,       /* published MetaObject slot */
        igFile_Register,                        /* base class registrar */
        igFile_GetPublishedMetaObject_002c0930, /* base class MetaObject accessor */
        thunk_igPsx2File_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2File_className_004f9008,        /* class name */
        0x4C,                                   /* instance size */
        igPsx2File_GetVTable,                   /* vtable getter */
        &igPsx2File_InitFields,                 /* field adder */
        thunk_FUN_0032c0c0,                     /* extra callback item */
        0                                       /* callback list */
    );
}

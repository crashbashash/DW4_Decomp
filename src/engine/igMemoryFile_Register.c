/* 0x002c08a0 igMemoryFile_Register: registers class igMemoryFile with the object system, derived from igFile.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryFile_GetVTable[];
extern char thunk_igMemoryFile_GetMetaObject[];
extern char igFile_GetPublishedMetaObject_002c0930[];
extern char thunk_FUN_002ef9a0[];
extern char igFile_Register[];
extern char s_igMemoryFile_className_004f6ce8[];
extern char g_igMemoryFile_metaObject_00585f18[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryFile_InitFields();

void igMemoryFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryFile_metaObject_00585f18,     /* published MetaObject slot */
        igFile_Register,                        /* base class registrar */
        igFile_GetPublishedMetaObject_002c0930, /* base class MetaObject accessor */
        thunk_igMemoryFile_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryFile_className_004f6ce8,      /* class name */
        0x3C,                                   /* instance size */
        igMemoryFile_GetVTable,                 /* vtable getter */
        &igMemoryFile_InitFields,               /* field adder */
        thunk_FUN_002ef9a0,                     /* extra callback item */
        0                                       /* callback list */
    );
}

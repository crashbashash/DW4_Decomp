/* 0x002c0eb0 igMemoryDirEntry_Register: registers class igMemoryDirEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject_002bdab0[];
extern char igMemoryDirEntry_GetVTable[];
extern char thunk_igMemoryDirEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igMemoryDirEntry_callbackList_004c02f8[];
extern char s_igMemoryDirEntry_className_004f6d70[];
extern char g_igMemoryDirEntry_metaObject_00585f60[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryDirEntry_InitFields();

void igMemoryDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryDirEntry_metaObject_00585f60,     /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject_002bdab0, /* base class MetaObject accessor */
        thunk_igMemoryDirEntry_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryDirEntry_className_004f6d70,      /* class name */
        0x38,                                       /* instance size */
        igMemoryDirEntry_GetVTable,                 /* vtable getter */
        &igMemoryDirEntry_InitFields,               /* field adder */
        0,                                          /* extra callback item */
        g_igMemoryDirEntry_callbackList_004c02f8    /* callback list */
    );
}

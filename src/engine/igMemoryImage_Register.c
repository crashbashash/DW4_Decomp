/* 0x0014de20 igMemoryImage_Register: registers class igMemoryImage with the object system, derived from igImage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igMemoryImage_GetMetaObject[];
extern char igImage_GetPublishedMetaObject[];
extern char igImage_Register[];
extern char igMemoryImage_className[];
extern char g_igMemoryImage_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igMemoryImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryImage_metaObject,     /* published MetaObject slot */
        igImage_Register,                        /* base class registrar */
        igImage_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMemoryImage_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igMemoryImage_className,      /* class name */
        0x5C,                                    /* instance size */
        0,                                       /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}

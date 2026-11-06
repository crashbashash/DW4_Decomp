/* 0x0014df00 igFileImage_Register: registers class igFileImage with the object system, derived from igImage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igImage_GetPublishedMetaObject[];
extern char thunk_igFileImage_GetMetaObject[];
extern char igImage_Register[];
extern char igFileImage_className[];
extern char g_igFileImage_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igFileImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFileImage_metaObject,       /* published MetaObject slot */
        igImage_Register,                        /* base class registrar */
        igImage_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFileImage_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igFileImage_className,        /* class name */
        0x5C,                                    /* instance size */
        0,                                       /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}

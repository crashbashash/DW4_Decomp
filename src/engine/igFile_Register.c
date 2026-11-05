/* 0x002c4d90 igFile_Register: registers class igFile with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igNamedObject_Register[];
extern char thunk_igFile_GetMetaObject[];
extern char s_igFile_className_004f7718[];
extern char g_igFile_metaObject_005863b0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFile_InitFields();

void igFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFile_metaObject_005863b0,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igFile_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igFile_className_004f7718,                   /* class name */
        0x2C,                                          /* instance size */
        0,                                             /* vtable getter */
        &igFile_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}

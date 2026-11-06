/* 0x001544a0 igPsx2Clut_Register: registers class igPsx2Clut with the object system, derived from igClut.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igClut_Register[];
extern char thunk_igPsx2Clut_GetMetaObject[];
extern char igPsx2Clut_GetVTable[];
extern char igClut_GetPublishedMetaObject[];
extern char igPsx2Clut_className[];
extern char g_igPsx2Clut_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2Clut_InitFields();

void igPsx2Clut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Clut_metaObject,       /* published MetaObject slot */
        igClut_Register,                        /* base class registrar */
        igClut_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Clut_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2Clut_className,        /* class name */
        0x28,                                   /* instance size */
        igPsx2Clut_GetVTable,                   /* vtable getter */
        &igPsx2Clut_InitFields,                 /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}

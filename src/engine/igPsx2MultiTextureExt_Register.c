/* 0x00153830 igPsx2MultiTextureExt_Register: registers class igPsx2MultiTextureExt with the object system, derived from igMultiTextureExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMultiTextureExt_Register[];
extern char thunk_igPsx2MultiTextureExt_GetMetaObject[];
extern char igPsx2MultiTextureExt_GetVTable[];
extern char igMultiTextureExt_GetPublishedMetaObject[];
extern char g_igPsx2MultiTextureExt_callbackList[];
extern char igPsx2MultiTextureExt_className[];
extern char g_igPsx2MultiTextureExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2MultiTextureExt_InitFields();

void igPsx2MultiTextureExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2MultiTextureExt_metaObject,       /* published MetaObject slot */
        igMultiTextureExt_Register,                        /* base class registrar */
        igMultiTextureExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2MultiTextureExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2MultiTextureExt_className,        /* class name */
        0x34,                                              /* instance size */
        igPsx2MultiTextureExt_GetVTable,                   /* vtable getter */
        &igPsx2MultiTextureExt_InitFields,                 /* field adder */
        0,                                                 /* extra callback item */
        g_igPsx2MultiTextureExt_callbackList      /* callback list */
    );
}

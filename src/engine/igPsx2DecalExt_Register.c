/* 0x001542c0 igPsx2DecalExt_Register: registers class igPsx2DecalExt with the object system, derived from igDecalExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDecalExt_Register[];
extern char thunk_igPsx2DecalExt_GetMetaObject[];
extern char igPsx2DecalExt_GetVTable[];
extern char igDecalExt_GetPublishedMetaObject[];
extern char g_igPsx2DecalExt_callbackList[];
extern char igPsx2DecalExt_className[];
extern char g_igPsx2DecalExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2DecalExt_InitFields();

void igPsx2DecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2DecalExt_metaObject,       /* published MetaObject slot */
        igDecalExt_Register,                        /* base class registrar */
        igDecalExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2DecalExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2DecalExt_className,        /* class name */
        0x20,                                       /* instance size */
        igPsx2DecalExt_GetVTable,                   /* vtable getter */
        &igPsx2DecalExt_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igPsx2DecalExt_callbackList      /* callback list */
    );
}

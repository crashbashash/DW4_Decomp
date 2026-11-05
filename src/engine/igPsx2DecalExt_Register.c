/* 0x001542c0 igPsx2DecalExt_Register: registers class igPsx2DecalExt with the object system, derived from igDecalExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDecalExt_Register[];
extern char thunk_igPsx2DecalExt_GetMetaObject[];
extern char igPsx2DecalExt_GetVTable[];
extern char igDecalExt_GetPublishedMetaObject_00154340[];
extern char g_igPsx2DecalExt_callbackList_0048a0b0[];
extern char s_igPsx2DecalExt_className_004de638[];
extern char g_igPsx2DecalExt_metaObject_005605f8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2DecalExt_InitFields();

void igPsx2DecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2DecalExt_metaObject_005605f8,       /* published MetaObject slot */
        igDecalExt_Register,                        /* base class registrar */
        igDecalExt_GetPublishedMetaObject_00154340, /* base class MetaObject accessor */
        thunk_igPsx2DecalExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2DecalExt_className_004de638,        /* class name */
        0x20,                                       /* instance size */
        igPsx2DecalExt_GetVTable,                   /* vtable getter */
        &igPsx2DecalExt_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igPsx2DecalExt_callbackList_0048a0b0      /* callback list */
    );
}

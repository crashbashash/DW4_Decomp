/* 0x00153270 igPsx2PointSpriteExt_Register: registers class igPsx2PointSpriteExt with the object system, derived from igPointSpriteExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igPointSpriteExt_Register[];
extern char thunk_igPsx2PointSpriteExt_GetMetaObject[];
extern char igPsx2PointSpriteExt_GetVTable[];
extern char igPointSpriteExt_GetPublishedMetaObject[];
extern char g_igPsx2PointSpriteExt_callbackList[];
extern char igPsx2PointSpriteExt_className[];
extern char g_igPsx2PointSpriteExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2PointSpriteExt_InitFields();

void igPsx2PointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2PointSpriteExt_metaObject,       /* published MetaObject slot */
        igPointSpriteExt_Register,                        /* base class registrar */
        igPointSpriteExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2PointSpriteExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2PointSpriteExt_className,        /* class name */
        0x18C,                                            /* instance size */
        igPsx2PointSpriteExt_GetVTable,                   /* vtable getter */
        &igPsx2PointSpriteExt_InitFields,                 /* field adder */
        0,                                                /* extra callback item */
        g_igPsx2PointSpriteExt_callbackList      /* callback list */
    );
}

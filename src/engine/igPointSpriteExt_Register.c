/* 0x0014c680 igPointSpriteExt_Register: registers class igPointSpriteExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContextExt_GetPublishedMetaObject[];
extern char igPointSpriteExt_GetVTable[];
extern char thunk_igPointSpriteExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char g_igPointSpriteExt_callbackList[];
extern char igPointSpriteExt_className[];
extern char g_igPointSpriteExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPointSpriteExt_InitFields();

void igPointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPointSpriteExt_metaObject,       /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPointSpriteExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPointSpriteExt_className,        /* class name */
        0x188,                                        /* instance size */
        igPointSpriteExt_GetVTable,                   /* vtable getter */
        &igPointSpriteExt_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPointSpriteExt_callbackList      /* callback list */
    );
}

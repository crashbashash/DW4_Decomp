/* 0x00152d20 igPsx2UserUCodeExt_Register: registers class igPsx2UserUCodeExt with the object system, derived from igUserUCodeExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUserUCodeExt_Register[];
extern char thunk_igPsx2UserUCodeExt_GetMetaObject[];
extern char igPsx2UserUCodeExt_GetVTable[];
extern char igUserUCodeExt_GetPublishedMetaObject_00152da0[];
extern char g_igPsx2UserUCodeExt_callbackList_00489db0[];
extern char s_igPsx2UserUCodeExt_className_004de010[];
extern char g_igPsx2UserUCodeExt_metaObject_005604d0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2UserUCodeExt_InitFields();

void igPsx2UserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2UserUCodeExt_metaObject_005604d0,       /* published MetaObject slot */
        igUserUCodeExt_Register,                        /* base class registrar */
        igUserUCodeExt_GetPublishedMetaObject_00152da0, /* base class MetaObject accessor */
        thunk_igPsx2UserUCodeExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2UserUCodeExt_className_004de010,        /* class name */
        0x24,                                           /* instance size */
        igPsx2UserUCodeExt_GetVTable,                   /* vtable getter */
        &igPsx2UserUCodeExt_InitFields,                 /* field adder */
        0,                                              /* extra callback item */
        g_igPsx2UserUCodeExt_callbackList_00489db0      /* callback list */
    );
}

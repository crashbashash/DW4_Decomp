/* 0x00153c90 igPsx2ImageConvert_Register: registers class igPsx2ImageConvert with the object system, derived from igImageConvert.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igImageConvert_Register[];
extern char thunk_igPsx2ImageConvert_GetMetaObject[];
extern char igPsx2ImageConvert_GetVTable[];
extern char igImageConvert_GetPublishedMetaObject_00153d00[];
extern char s_igPsx2ImageConvert_className_004de5f0[];
extern char g_igPsx2ImageConvert_metaObject_005605d8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2ImageConvert_InitFields_00153d10[4];
void igPsx2ImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ImageConvert_metaObject_005605d8,       /* published MetaObject slot */
        igImageConvert_Register,                        /* base class registrar */
        igImageConvert_GetPublishedMetaObject_00153d00, /* base class MetaObject accessor */
        thunk_igPsx2ImageConvert_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2ImageConvert_className_004de5f0,        /* class name */
        8,                                              /* instance size */
        igPsx2ImageConvert_GetVTable,                   /* vtable getter */
        &igPsx2ImageConvert_InitFields_00153d10[0],     /* field adder (post_init in data/reflection.json) */
        0,                                              /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                               /* zero-terminated callback-vector item list (none) */
    );
}

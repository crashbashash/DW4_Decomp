/* 0x00153c90 igPsx2ImageConvert_Register: registers class igPsx2ImageConvert with the object system, derived from igImageConvert.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igImageConvert_Register[];
extern char thunk_igPsx2ImageConvert_GetMetaObject[];
extern char igPsx2ImageConvert_GetVTable[];
extern char igImageConvert_GetPublishedMetaObject[];
extern char igPsx2ImageConvert_className[];
extern char g_igPsx2ImageConvert_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2ImageConvert_InitFields_00153d10[4];
void igPsx2ImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ImageConvert_metaObject,       /* published MetaObject slot */
        igImageConvert_Register,                        /* base class registrar */
        igImageConvert_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2ImageConvert_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2ImageConvert_className,        /* class name */
        8,                                              /* instance size */
        igPsx2ImageConvert_GetVTable,                   /* vtable getter */
        &igPsx2ImageConvert_InitFields_00153d10[0],     /* field adder (post_init in data/reflection.json) */
        0,                                              /* extra callback-vector item (none) */
        0                                               /* zero-terminated callback-vector item list (none) */
    );
}

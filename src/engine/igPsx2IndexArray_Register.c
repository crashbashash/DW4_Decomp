/* 0x00153b50 igPsx2IndexArray_Register: registers class igPsx2IndexArray with the object system, derived from igIndexArray.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIndexArray_Register[];
extern char thunk_igPsx2IndexArray_GetMetaObject[];
extern char igPsx2IndexArray_GetVTable[];
extern char igIndexArray_GetPublishedMetaObject_00153bc0[];
extern char s_igPsx2IndexArray_className_004de5d0[];
extern char g_igPsx2IndexArray_metaObject_005605d0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2IndexArray_InitFields_00153bd0[4];
void igPsx2IndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2IndexArray_metaObject_005605d0,       /* published MetaObject slot */
        igIndexArray_Register,                        /* base class registrar */
        igIndexArray_GetPublishedMetaObject_00153bc0, /* base class MetaObject accessor */
        thunk_igPsx2IndexArray_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2IndexArray_className_004de5d0,        /* class name */
        0x1C,                                         /* instance size */
        igPsx2IndexArray_GetVTable,                   /* vtable getter */
        &igPsx2IndexArray_InitFields_00153bd0[0],     /* field adder (post_init in data/reflection.json) */
        0,                                            /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                             /* zero-terminated callback-vector item list (none) */
    );
}

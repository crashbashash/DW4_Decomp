/* 0x00153e70 igPsx2Image_Register: registers class igPsx2Image with the object system, derived from igMemoryImage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryImage_Register[];
extern char thunk_igPsx2Image_GetMetaObject[];
extern char igPsx2Image_GetVTable[];
extern char igMemoryImage_GetPublishedMetaObject[];
extern char igPsx2Image_className[];
extern char g_igPsx2Image_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2Image_InitFields_00153ef0[4];
void igPsx2Image_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Image_metaObject,             /* published MetaObject slot */
        igMemoryImage_Register,                        /* base class registrar */
        igMemoryImage_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2Image_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igPsx2Image_className,              /* class name */
        0x5C,                                          /* instance size */
        igPsx2Image_GetVTable,                         /* vtable getter */
        &igPsx2Image_InitFields_00153ef0[0],           /* field adder (post_init in data/reflection.json) */
        0,                                             /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                              /* zero-terminated callback-vector item list (none) */
    );
}

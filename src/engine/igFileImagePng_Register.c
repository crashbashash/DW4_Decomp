/* 0x00150580 igFileImagePng_Register: registers class igFileImagePng with the object system, derived from igFileImage.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFileImage_Register[];
extern char igFileImagePng_GetVTable[];
extern char thunk_igFileImagePng_GetMetaObject[];
extern char igFileImage_GetPublishedMetaObject[];
extern char g_igFileImagePng_callbackList[];
extern char igFileImagePng_className[];
extern char g_igFileImagePng_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igFileImagePng_InitFields();

void igFileImagePng_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFileImagePng_metaObject,        /* published MetaObject slot */
        igFileImage_Register,                        /* base class registrar */
        igFileImage_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFileImagePng_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igFileImagePng_className,         /* class name */
        0x60,                                        /* instance size */
        igFileImagePng_GetVTable,                    /* vtable getter */
        &igFileImagePng_InitFields,                  /* field adder */
        0,                                           /* extra callback item */
        g_igFileImagePng_callbackList       /* callback list */
    );
}

/* 0x0045dd30 igLogoRenderer_Register: registers class igLogoRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igLogoRenderer_GetVTable[];
extern char thunk_igLogoRenderer_GetMetaObject[];
extern char g_igLogoRenderer_callbackList[];
extern char igLogoRenderer_className[];
extern char g_igLogoRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igLogoRenderer_InitFields();

void igLogoRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLogoRenderer_metaObject,       /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLogoRenderer_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igLogoRenderer_className,        /* class name */
        0x28,                                       /* instance size */
        igLogoRenderer_GetVTable,                   /* vtable getter */
        &igLogoRenderer_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igLogoRenderer_callbackList      /* callback list */
    );
}

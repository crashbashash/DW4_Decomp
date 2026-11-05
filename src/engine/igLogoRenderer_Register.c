/* 0x0045dd30 igLogoRenderer_Register: registers class igLogoRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igRenderer_Register[];
extern char igLogoRenderer_GetVTable[];
extern char thunk_igLogoRenderer_GetMetaObject[];
extern char g_igLogoRenderer_callbackList_004d18d0[];
extern char s_igLogoRenderer_className_0051f988[];
extern char g_igLogoRenderer_metaObject_0058cdf0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igLogoRenderer_InitFields();

void igLogoRenderer_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLogoRenderer_metaObject_0058cdf0,       /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010, /* base class MetaObject accessor */
        thunk_igLogoRenderer_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igLogoRenderer_className_0051f988,        /* class name */
        0x28,                                       /* instance size */
        igLogoRenderer_GetVTable,                   /* vtable getter */
        &igLogoRenderer_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igLogoRenderer_callbackList_004d18d0      /* callback list */
    );
}

/* 0x00451820 igDefaultAspect_Register: registers class igDefaultAspect with the object system, derived from igGuiComponentAspect.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGuiComponentAspect_GetPublishedMetaObject[];
extern char igGuiComponentAspect_Register[];
extern char igDefaultAspect_GetVTable[];
extern char thunk_igDefaultAspect_GetMetaObject[];
extern char g_igDefaultAspect_callbackList[];
extern char igDefaultAspect_className[];
extern char g_igDefaultAspect_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igDefaultAspect_InitFields();

void igDefaultAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDefaultAspect_metaObject,                /* published MetaObject slot */
        igGuiComponentAspect_Register,                        /* base class registrar */
        igGuiComponentAspect_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDefaultAspect_GetMetaObject,                  /* own MetaObject accessor (stored at +0x54) */
        igDefaultAspect_className,                 /* class name */
        0x2C,                                                 /* instance size */
        igDefaultAspect_GetVTable,                            /* vtable getter */
        &igDefaultAspect_InitFields,                          /* field adder */
        0,                                                    /* extra callback item */
        g_igDefaultAspect_callbackList               /* callback list */
    );
}

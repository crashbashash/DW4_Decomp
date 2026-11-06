/* 0x0044fc60 igGuiComponentAspect_Register: registers class igGuiComponentAspect with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char thunk_igGuiComponentAspect_GetMetaObject[];
extern char g_igGuiComponentAspect_callbackList[];
extern char igGuiComponentAspect_className[];
extern char g_igGuiComponentAspect_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponentAspect_InitFields();

void igGuiComponentAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentAspect_metaObject, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igGuiComponentAspect_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGuiComponentAspect_className,  /* class name */
        0x28,                                       /* instance size */
        0,                                          /* vtable getter */
        &igGuiComponentAspect_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igGuiComponentAspect_callbackList  /* callback list */
    );
}

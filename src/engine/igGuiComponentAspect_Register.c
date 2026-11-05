/* 0x0044fc60 igGuiComponentAspect_Register: registers class igGuiComponentAspect with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char thunk_igGuiComponentAspect_GetMetaObject[];
extern char g_igGuiComponentAspect_callbackList_004d0530[];
extern char s_igGuiComponentAspect_className_0051e3c0[];
extern char g_igGuiComponentAspect_metaObject_0058c480[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiComponentAspect_InitFields();

void igGuiComponentAspect_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentAspect_metaObject_0058c480, /* published MetaObject slot */
        igView_Register,                            /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,     /* base class MetaObject accessor */
        thunk_igGuiComponentAspect_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponentAspect_className_0051e3c0,  /* class name */
        0x28,                                       /* instance size */
        0,                                          /* vtable getter */
        &igGuiComponentAspect_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igGuiComponentAspect_callbackList_004d0530  /* callback list */
    );
}

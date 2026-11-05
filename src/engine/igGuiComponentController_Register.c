/* 0x0044fb30 igGuiComponentController_Register: registers class igGuiComponentController with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igGuiComponentController_GetVTable[];
extern char thunk_igGuiComponentController_GetMetaObject[];
extern char s_igGuiComponentController_className_0051e3a0[];
extern char g_igGuiComponentController_metaObject_0058c478[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igGuiComponentController_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentController_metaObject_0058c478, /* published MetaObject slot */
        igView_Register,                                /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,         /* base class MetaObject accessor */
        thunk_igGuiComponentController_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponentController_className_0051e3a0,  /* class name */
        0xC,                                            /* instance size */
        igGuiComponentController_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}

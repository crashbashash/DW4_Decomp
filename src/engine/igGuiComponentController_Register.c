/* 0x0044fb30 igGuiComponentController_Register: registers class igGuiComponentController with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igGuiComponentController_GetVTable[];
extern char thunk_igGuiComponentController_GetMetaObject[];
extern char igGuiComponentController_className[];
extern char g_igGuiComponentController_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igGuiComponentController_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentController_metaObject, /* published MetaObject slot */
        igView_Register,                                /* base class registrar */
        igView_GetPublishedMetaObject,         /* base class MetaObject accessor */
        thunk_igGuiComponentController_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGuiComponentController_className,  /* class name */
        0xC,                                            /* instance size */
        igGuiComponentController_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}

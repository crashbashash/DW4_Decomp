/* 0x0044f8e0 igGuiComponentModel_Register: registers class igGuiComponentModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igGuiComponentModel_GetVTable[];
extern char thunk_igGuiComponentModel_GetMetaObject[];
extern char g_igGuiComponentModel_callbackList[];
extern char igGuiComponentModel_className[];
extern char g_igGuiComponentModel_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiComponentModel_InitFields();

void igGuiComponentModel_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentModel_metaObject, /* published MetaObject slot */
        igModel_Register,                          /* base class registrar */
        igModel_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igGuiComponentModel_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGuiComponentModel_className,  /* class name */
        0x24,                                      /* instance size */
        igGuiComponentModel_GetVTable,             /* vtable getter */
        &igGuiComponentModel_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igGuiComponentModel_callbackList  /* callback list */
    );
}

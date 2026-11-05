/* 0x0044f8e0 igGuiComponentModel_Register: registers class igGuiComponentModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject_0044d340[];
extern char igModel_Register[];
extern char igGuiComponentModel_GetVTable[];
extern char thunk_igGuiComponentModel_GetMetaObject[];
extern char g_igGuiComponentModel_callbackList_004d04a8[];
extern char s_igGuiComponentModel_className_0051e330[];
extern char g_igGuiComponentModel_metaObject_0058c438[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiComponentModel_InitFields();

void igGuiComponentModel_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentModel_metaObject_0058c438, /* published MetaObject slot */
        igModel_Register,                          /* base class registrar */
        igModel_GetPublishedMetaObject_0044d340,   /* base class MetaObject accessor */
        thunk_igGuiComponentModel_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponentModel_className_0051e330,  /* class name */
        0x24,                                      /* instance size */
        igGuiComponentModel_GetVTable,             /* vtable getter */
        &igGuiComponentModel_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igGuiComponentModel_callbackList_004d04a8  /* callback list */
    );
}

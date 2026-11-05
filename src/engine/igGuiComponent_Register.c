/* 0x00450400 igGuiComponent_Register: registers class igGuiComponent with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igGuiComponent_GetVTable[];
extern char thunk_igGuiComponent_GetMetaObject[];
extern char g_igGuiComponent_callbackList_004d0580[];
extern char s_igGuiComponent_className_0051e418[];
extern char g_igGuiComponent_metaObject_0058c4a8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiComponent_InitFields();

void igGuiComponent_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponent_metaObject_0058c4a8,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igGuiComponent_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponent_className_0051e418,   /* class name */
        0x24,                                  /* instance size */
        igGuiComponent_GetVTable,              /* vtable getter */
        &igGuiComponent_InitFields,            /* field adder */
        0,                                     /* extra callback item */
        g_igGuiComponent_callbackList_004d0580  /* callback list */
    );
}

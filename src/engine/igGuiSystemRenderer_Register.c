/* 0x0044e820 igGuiSystemRenderer_Register: registers class igGuiSystemRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igRenderer_Register[];
extern char igGuiSystemRenderer_GetVTable[];
extern char thunk_igGuiSystemRenderer_GetMetaObject[];
extern char g_igGuiSystemRenderer_callbackList_004d0260[];
extern char s_igGuiSystemRenderer_className_0051e050[];
extern char g_igGuiSystemRenderer_metaObject_0058c338[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiSystemRenderer_InitFields();

void igGuiSystemRenderer_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiSystemRenderer_metaObject_0058c338,  /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010, /* base class MetaObject accessor */
        thunk_igGuiSystemRenderer_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igGuiSystemRenderer_className_0051e050,   /* class name */
        0x1C,                                       /* instance size */
        igGuiSystemRenderer_GetVTable,              /* vtable getter */
        &igGuiSystemRenderer_InitFields,            /* field adder */
        0,                                          /* extra callback item */
        g_igGuiSystemRenderer_callbackList_004d0260  /* callback list */
    );
}

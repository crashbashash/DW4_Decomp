/* 0x0044e820 igGuiSystemRenderer_Register: registers class igGuiSystemRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igGuiSystemRenderer_GetVTable[];
extern char thunk_igGuiSystemRenderer_GetMetaObject[];
extern char g_igGuiSystemRenderer_callbackList[];
extern char igGuiSystemRenderer_className[];
extern char g_igGuiSystemRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystemRenderer_InitFields();

void igGuiSystemRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiSystemRenderer_metaObject,  /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGuiSystemRenderer_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igGuiSystemRenderer_className,   /* class name */
        0x1C,                                       /* instance size */
        igGuiSystemRenderer_GetVTable,              /* vtable getter */
        &igGuiSystemRenderer_InitFields,            /* field adder */
        0,                                          /* extra callback item */
        g_igGuiSystemRenderer_callbackList  /* callback list */
    );
}

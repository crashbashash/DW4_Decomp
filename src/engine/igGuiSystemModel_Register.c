/* 0x0044f380 igGuiSystemModel_Register: registers class igGuiSystemModel with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igGuiSystemModel_GetVTable[];
extern char thunk_igGuiSystemModel_GetMetaObject[];
extern char g_igGuiSystemModel_callbackList[];
extern char igGuiSystemModel_className[];
extern char g_igGuiSystemModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystemModel_InitFields();

void igGuiSystemModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiSystemModel_metaObject,  /* published MetaObject slot */
        igModel_Register,                        /* base class registrar */
        igModel_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGuiSystemModel_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igGuiSystemModel_className,   /* class name */
        0xB8,                                    /* instance size */
        igGuiSystemModel_GetVTable,              /* vtable getter */
        &igGuiSystemModel_InitFields,            /* field adder */
        0,                                       /* extra callback item */
        g_igGuiSystemModel_callbackList  /* callback list */
    );
}

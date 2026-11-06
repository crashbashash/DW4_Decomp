/* 0x0044f660 igGuiComponentNode_Register: registers class igGuiComponentNode with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igGuiComponentNode_GetVTable[];
extern char thunk_igGuiComponentNode_GetMetaObject[];
extern char g_igGuiComponentNode_callbackList[];
extern char igGuiComponentNode_className[];
extern char g_igGuiComponentNode_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponentNode_InitFields();

void igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentNode_metaObject, /* published MetaObject slot */
        igGroup_Register,                         /* base class registrar */
        igGroup_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igGuiComponentNode_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGuiComponentNode_className,  /* class name */
        0x24,                                     /* instance size */
        igGuiComponentNode_GetVTable,             /* vtable getter */
        &igGuiComponentNode_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igGuiComponentNode_callbackList  /* callback list */
    );
}

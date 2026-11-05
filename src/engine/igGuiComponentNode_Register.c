/* 0x0044f660 igGuiComponentNode_Register: registers class igGuiComponentNode with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igGroup_Register[];
extern char igGuiComponentNode_GetVTable[];
extern char thunk_igGuiComponentNode_GetMetaObject[];
extern char g_igGuiComponentNode_callbackList_004d0480[];
extern char s_igGuiComponentNode_className_0051e300[];
extern char g_igGuiComponentNode_metaObject_0058c428[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiComponentNode_InitFields();

void igGuiComponentNode_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentNode_metaObject_0058c428, /* published MetaObject slot */
        igGroup_Register,                         /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0,  /* base class MetaObject accessor */
        thunk_igGuiComponentNode_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponentNode_className_0051e300,  /* class name */
        0x24,                                     /* instance size */
        igGuiComponentNode_GetVTable,             /* vtable getter */
        &igGuiComponentNode_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igGuiComponentNode_callbackList_004d0480  /* callback list */
    );
}

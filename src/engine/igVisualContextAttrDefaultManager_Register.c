/* 0x001301d0 igVisualContextAttrDefaultManager_Register: registers class igVisualContextAttrDefaultManager with the object system, derived from igAttrDefaultManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualContextAttrDefaultManager_GetVTable[];
extern char thunk_igVisualContextAttrDefaultManager_GetMetaObject[];
extern char igAttrDefaultManager_GetPublishedMetaObject[];
extern char igAttrDefaultManager_Register[];
extern char g_igVisualContextAttrDefaultManager_callbackList[];
extern char igVisualContextAttrDefaultManager_className[];
extern char g_igVisualContextAttrDefaultManager_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igVisualContextAttrDefaultManager_InitFields();

void igVisualContextAttrDefaultManager_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualContextAttrDefaultManager_metaObject, /* published MetaObject slot */
        igAttrDefaultManager_Register,                           /* base class registrar */
        igAttrDefaultManager_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igVisualContextAttrDefaultManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVisualContextAttrDefaultManager_className,  /* class name */
        0xC,                                                     /* instance size */
        igVisualContextAttrDefaultManager_GetVTable,             /* vtable getter */
        &igVisualContextAttrDefaultManager_InitFields,           /* field adder */
        0,                                                       /* extra callback item */
        g_igVisualContextAttrDefaultManager_callbackList  /* callback list */
    );
}

/* 0x0013a050 igBlendFunctionAttr_Register: registers class igBlendFunctionAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendFunctionAttr_GetVTable[];
extern char thunk_igBlendFunctionAttr_GetMetaObject[];
extern char g_igBlendFunctionAttr_callbackList[];
extern char igBlendFunctionAttr_className[];
extern char g_igBlendFunctionAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igBlendFunctionAttr_InitFields();

void igBlendFunctionAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendFunctionAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendFunctionAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igBlendFunctionAttr_className,          /* class name */
        0x34,                                              /* instance size */
        igBlendFunctionAttr_GetVTable,                     /* vtable getter */
        &igBlendFunctionAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        g_igBlendFunctionAttr_callbackList        /* callback list */
    );
}

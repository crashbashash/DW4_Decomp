/* 0x00132d00 igTextureAttr_Register: registers class igTextureAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureAttr_GetVTable[];
extern char thunk_igTextureAttr_GetMetaObject[];
extern char g_igTextureAttr_callbackList[];
extern char igTextureAttr_className[];
extern char g_igTextureAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureAttr_InitFields();

void igTextureAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureAttr_metaObject,               /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureAttr_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        igTextureAttr_className,                /* class name */
        0x48,                                              /* instance size */
        igTextureAttr_GetVTable,                           /* vtable getter */
        &igTextureAttr_InitFields,                         /* field adder */
        0,                                                 /* extra callback item */
        g_igTextureAttr_callbackList              /* callback list */
    );
}

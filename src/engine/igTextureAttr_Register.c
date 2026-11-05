/* 0x00132d00 igTextureAttr_Register: registers class igTextureAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureAttr_GetVTable[];
extern char thunk_igTextureAttr_GetMetaObject[];
extern char g_igTextureAttr_callbackList_00485cd0[];
extern char s_igTextureAttr_className_004d4da8[];
extern char g_igTextureAttr_metaObject_0055eda0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureAttr_InitFields();

void igTextureAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureAttr_metaObject_0055eda0,               /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureAttr_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        s_igTextureAttr_className_004d4da8,                /* class name */
        0x48,                                              /* instance size */
        igTextureAttr_GetVTable,                           /* vtable getter */
        &igTextureAttr_InitFields,                         /* field adder */
        0,                                                 /* extra callback item */
        g_igTextureAttr_callbackList_00485cd0              /* callback list */
    );
}

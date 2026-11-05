/* 0x00131250 igTextureUnloadAttr_Register: registers class igTextureUnloadAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureUnloadAttr_GetVTable[];
extern char thunk_igTextureUnloadAttr_GetMetaObject[];
extern char g_igTextureUnloadAttr_callbackList_00485ab0[];
extern char s_igTextureUnloadAttr_className_004d4bd0[];
extern char g_igTextureUnloadAttr_metaObject_0055ec90[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureUnloadAttr_InitFields();

void igTextureUnloadAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureUnloadAttr_metaObject_0055ec90,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureUnloadAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igTextureUnloadAttr_className_004d4bd0,          /* class name */
        0x14,                                              /* instance size */
        igTextureUnloadAttr_GetVTable,                     /* vtable getter */
        &igTextureUnloadAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        g_igTextureUnloadAttr_callbackList_00485ab0        /* callback list */
    );
}

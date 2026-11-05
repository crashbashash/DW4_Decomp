/* 0x00132430 igTextureCubeAttr_Register: registers class igTextureCubeAttr with the object system, derived from igTextureAttr.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTextureCubeAttr_GetVTable[];
extern char thunk_igTextureCubeAttr_GetMetaObject[];
extern char igTextureAttr_GetPublishedMetaObject_001324c0[];
extern char igTextureAttr_Register[];
extern char g_igTextureCubeAttr_callbackList_00485c10[];
extern char s_igTextureCubeAttr_className_004d4d20[];
extern char g_igTextureCubeAttr_metaObject_0055ed48[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureCubeAttr_InitFields();

void igTextureCubeAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureCubeAttr_metaObject_0055ed48,       /* published MetaObject slot */
        igTextureAttr_Register,                        /* base class registrar */
        igTextureAttr_GetPublishedMetaObject_001324c0, /* base class MetaObject accessor */
        thunk_igTextureCubeAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igTextureCubeAttr_className_004d4d20,        /* class name */
        0x68,                                          /* instance size */
        igTextureCubeAttr_GetVTable,                   /* vtable getter */
        &igTextureCubeAttr_InitFields,                 /* field adder */
        0,                                             /* extra callback item */
        g_igTextureCubeAttr_callbackList_00485c10      /* callback list */
    );
}

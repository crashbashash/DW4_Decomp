/* 0x00132430 igTextureCubeAttr_Register: registers class igTextureCubeAttr with the object system, derived from igTextureAttr.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTextureCubeAttr_GetVTable[];
extern char thunk_igTextureCubeAttr_GetMetaObject[];
extern char igTextureAttr_GetPublishedMetaObject[];
extern char igTextureAttr_Register[];
extern char g_igTextureCubeAttr_callbackList[];
extern char igTextureCubeAttr_className[];
extern char g_igTextureCubeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureCubeAttr_InitFields();

void igTextureCubeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureCubeAttr_metaObject,       /* published MetaObject slot */
        igTextureAttr_Register,                        /* base class registrar */
        igTextureAttr_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureCubeAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igTextureCubeAttr_className,        /* class name */
        0x68,                                          /* instance size */
        igTextureCubeAttr_GetVTable,                   /* vtable getter */
        &igTextureCubeAttr_InitFields,                 /* field adder */
        0,                                             /* extra callback item */
        g_igTextureCubeAttr_callbackList      /* callback list */
    );
}

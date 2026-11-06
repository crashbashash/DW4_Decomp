/* 0x001a4c60 igBlendMatrixSelect_Register: registers class igBlendMatrixSelect with the object system, derived from igAttrSet.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttrSet_GetPublishedMetaObject[];
extern char igBlendMatrixSelect_GetVTable[];
extern char thunk_igBlendMatrixSelect_GetMetaObject[];
extern char igAttrSet_Register[];
extern char g_igBlendMatrixSelect_callbackList[];
extern char igBlendMatrixSelect_className[];
extern char g_igBlendMatrixSelect_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendMatrixSelect_InitFields();

void igBlendMatrixSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatrixSelect_metaObject, /* published MetaObject slot */
        igAttrSet_Register,                        /* base class registrar */
        igAttrSet_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendMatrixSelect_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igBlendMatrixSelect_className,  /* class name */
        0xAC,                                      /* instance size */
        igBlendMatrixSelect_GetVTable,             /* vtable getter */
        &igBlendMatrixSelect_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igBlendMatrixSelect_callbackList  /* callback list */
    );
}

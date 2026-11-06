/* 0x001994e0 igShaderFactory_Register: registers class igShaderFactory with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igShaderFactory_GetVTable[];
extern char thunk_igShaderFactory_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igShaderFactory_callbackList[];
extern char igShaderFactory_className[];
extern char g_igShaderFactory_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igShaderFactory_InitFields();

void igShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderFactory_metaObject,         /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igShaderFactory_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igShaderFactory_className,          /* class name */
        0x18,                                          /* instance size */
        igShaderFactory_GetVTable,                     /* vtable getter */
        &igShaderFactory_InitFields,                   /* field adder */
        0,                                             /* extra callback item */
        g_igShaderFactory_callbackList        /* callback list */
    );
}

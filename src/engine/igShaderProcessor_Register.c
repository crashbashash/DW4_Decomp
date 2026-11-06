/* 0x00198c40 igShaderProcessor_Register: registers class igShaderProcessor with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igShaderProcessor_GetVTable[];
extern char thunk_igShaderProcessor_GetMetaObject[];
extern char igObject_Register[];
extern char igShaderProcessor_className[];
extern char g_igShaderProcessor_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igShaderProcessor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderProcessor_metaObject, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igShaderProcessor_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igShaderProcessor_className,  /* class name */
        8,                                       /* instance size */
        igShaderProcessor_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}

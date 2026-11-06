/* 0x00194aa0 igTransientShaderData_Register: registers class igTransientShaderData with the object system, derived from igShaderData.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransientShaderData_GetVTable[];
extern char thunk_igTransientShaderData_GetMetaObject[];
extern char igShaderData_GetPublishedMetaObject[];
extern char igShaderData_Register[];
extern char g_igTransientShaderData_callbackList[];
extern char igTransientShaderData_className[];
extern char g_igTransientShaderData_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransientShaderData_InitFields();

void igTransientShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransientShaderData_metaObject,  /* published MetaObject slot */
        igShaderData_Register,                        /* base class registrar */
        igShaderData_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTransientShaderData_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igTransientShaderData_className,   /* class name */
        0x18,                                         /* instance size */
        igTransientShaderData_GetVTable,              /* vtable getter */
        &igTransientShaderData_InitFields,            /* field adder */
        0,                                            /* extra callback item */
        g_igTransientShaderData_callbackList  /* callback list */
    );
}

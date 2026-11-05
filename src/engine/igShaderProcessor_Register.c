/* 0x00198c40 igShaderProcessor_Register: registers class igShaderProcessor with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igShaderProcessor_GetVTable[];
extern char thunk_igShaderProcessor_GetMetaObject[];
extern char igObject_Register[];
extern char s_igShaderProcessor_className_004e1b40[];
extern char g_igShaderProcessor_metaObject_005614f8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igShaderProcessor_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderProcessor_metaObject_005614f8, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igShaderProcessor_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igShaderProcessor_className_004e1b40,  /* class name */
        8,                                       /* instance size */
        igShaderProcessor_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}

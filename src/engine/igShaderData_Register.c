/* 0x00199770 igShaderData_Register: registers class igShaderData with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igShaderData_GetVTable[];
extern char thunk_igShaderData_GetMetaObject[];
extern char igObject_Register[];
extern char g_igShaderData_callbackList[];
extern char igShaderData_className[];
extern char g_igShaderData_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igShaderData_InitFields();

void igShaderData_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderData_metaObject,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igShaderData_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igShaderData_className,     /* class name */
        0x18,                                  /* instance size */
        igShaderData_GetVTable,                /* vtable getter */
        &igShaderData_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        g_igShaderData_callbackList   /* callback list */
    );
}

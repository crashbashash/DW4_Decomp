/* 0x0019ebd0 igInterpretedShaderData_Register: registers class igInterpretedShaderData with the object system, derived from igTransientShaderData.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransientShaderData_Register[];
extern char igInterpretedShaderData_GetVTable[];
extern char thunk_igInterpretedShaderData_GetMetaObject[];
extern char igTransientShaderData_GetPublishedMetaObject_0019ec60[];
extern char g_igInterpretedShaderData_callbackList_0048bed0[];
extern char s_igInterpretedShaderData_className_004e2590[];
extern char g_igInterpretedShaderData_metaObject_00561990[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igInterpretedShaderData_InitFields();

void igInterpretedShaderData_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInterpretedShaderData_metaObject_00561990,         /* published MetaObject slot */
        igTransientShaderData_Register,                        /* base class registrar */
        igTransientShaderData_GetPublishedMetaObject_0019ec60, /* base class MetaObject accessor */
        thunk_igInterpretedShaderData_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igInterpretedShaderData_className_004e2590,          /* class name */
        0x20,                                                  /* instance size */
        igInterpretedShaderData_GetVTable,                     /* vtable getter */
        &igInterpretedShaderData_InitFields,                   /* field adder */
        0,                                                     /* extra callback item */
        g_igInterpretedShaderData_callbackList_0048bed0        /* callback list */
    );
}

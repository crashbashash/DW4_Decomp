/* 0x00194aa0 igTransientShaderData_Register: registers class igTransientShaderData with the object system, derived from igShaderData.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransientShaderData_GetVTable[];
extern char thunk_igTransientShaderData_GetMetaObject[];
extern char igShaderData_GetPublishedMetaObject_00194b30[];
extern char igShaderData_Register[];
extern char g_igTransientShaderData_callbackList_0048af90[];
extern char s_igTransientShaderData_className_004e1280[];
extern char g_igTransientShaderData_metaObject_005611a8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igTransientShaderData_InitFields();

void igTransientShaderData_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransientShaderData_metaObject_005611a8,  /* published MetaObject slot */
        igShaderData_Register,                        /* base class registrar */
        igShaderData_GetPublishedMetaObject_00194b30, /* base class MetaObject accessor */
        thunk_igTransientShaderData_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igTransientShaderData_className_004e1280,   /* class name */
        0x18,                                         /* instance size */
        igTransientShaderData_GetVTable,              /* vtable getter */
        &igTransientShaderData_InitFields,            /* field adder */
        0,                                            /* extra callback item */
        g_igTransientShaderData_callbackList_0048af90  /* callback list */
    );
}

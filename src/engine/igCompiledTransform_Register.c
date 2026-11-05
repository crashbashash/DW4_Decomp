/* 0x001a3710 igCompiledTransform_Register: registers class igCompiledTransform with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompiledTransform_GetVTable[];
extern char thunk_igCompiledTransform_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCompiledTransform_callbackList_0048c6c8[];
extern char s_igCompiledTransform_className_004e2e80[];
extern char g_igCompiledTransform_metaObject_00561d30[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igCompiledTransform_InitFields();

void igCompiledTransform_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompiledTransform_metaObject_00561d30, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igCompiledTransform_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCompiledTransform_className_004e2e80,  /* class name */
        0x24,                                      /* instance size */
        igCompiledTransform_GetVTable,             /* vtable getter */
        &igCompiledTransform_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igCompiledTransform_callbackList_0048c6c8  /* callback list */
    );
}

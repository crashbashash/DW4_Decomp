/* 0x001994e0 igShaderFactory_Register: registers class igShaderFactory with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igShaderFactory_GetVTable[];
extern char thunk_igShaderFactory_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igShaderFactory_callbackList_0048b670[];
extern char s_igShaderFactory_className_004e1c20[];
extern char g_igShaderFactory_metaObject_00561528[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igShaderFactory_InitFields();

void igShaderFactory_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderFactory_metaObject_00561528,         /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igShaderFactory_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igShaderFactory_className_004e1c20,          /* class name */
        0x18,                                          /* instance size */
        igShaderFactory_GetVTable,                     /* vtable getter */
        &igShaderFactory_InitFields,                   /* field adder */
        0,                                             /* extra callback item */
        g_igShaderFactory_callbackList_0048b670        /* callback list */
    );
}

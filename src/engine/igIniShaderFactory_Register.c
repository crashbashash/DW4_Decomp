/* 0x0019efc0 igIniShaderFactory_Register: registers class igIniShaderFactory with the object system, derived from igShaderFactory.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igShaderFactory_Register[];
extern char igIniShaderFactory_GetVTable[];
extern char thunk_igIniShaderFactory_GetMetaObject[];
extern char igShaderFactory_GetPublishedMetaObject_0019f050[];
extern char g_igIniShaderFactory_callbackList_0048bf00[];
extern char s_igIniShaderFactory_className_004e25d0[];
extern char g_igIniShaderFactory_metaObject_005619a8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igIniShaderFactory_InitFields();

void igIniShaderFactory_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIniShaderFactory_metaObject_005619a8,        /* published MetaObject slot */
        igShaderFactory_Register,                        /* base class registrar */
        igShaderFactory_GetPublishedMetaObject_0019f050, /* base class MetaObject accessor */
        thunk_igIniShaderFactory_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igIniShaderFactory_className_004e25d0,         /* class name */
        0x3C,                                            /* instance size */
        igIniShaderFactory_GetVTable,                    /* vtable getter */
        &igIniShaderFactory_InitFields,                  /* field adder */
        0,                                               /* extra callback item */
        g_igIniShaderFactory_callbackList_0048bf00       /* callback list */
    );
}

/* 0x0019b810 igProjectiveShadowShader_Register: registers class igProjectiveShadowShader with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igProjectiveShadowShader_GetVTable[];
extern char thunk_igProjectiveShadowShader_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igProjectiveShadowShader_callbackList[];
extern char igProjectiveShadowShader_className[];
extern char g_igProjectiveShadowShader_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igProjectiveShadowShader_InitFields();

void igProjectiveShadowShader_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProjectiveShadowShader_metaObject, /* published MetaObject slot */
        igGroup_Register,                               /* base class registrar */
        igGroup_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igProjectiveShadowShader_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igProjectiveShadowShader_className,  /* class name */
        0xF0,                                           /* instance size */
        igProjectiveShadowShader_GetVTable,             /* vtable getter */
        &igProjectiveShadowShader_InitFields,           /* field adder */
        0,                                              /* extra callback item */
        g_igProjectiveShadowShader_callbackList  /* callback list */
    );
}

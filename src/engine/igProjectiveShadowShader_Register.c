/* 0x0019b810 igProjectiveShadowShader_Register: registers class igProjectiveShadowShader with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igProjectiveShadowShader_GetVTable[];
extern char thunk_igProjectiveShadowShader_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igProjectiveShadowShader_callbackList_0048b800[];
extern char s_igProjectiveShadowShader_className_004e2090[];
extern char g_igProjectiveShadowShader_metaObject_00561620[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igProjectiveShadowShader_InitFields();

void igProjectiveShadowShader_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProjectiveShadowShader_metaObject_00561620, /* published MetaObject slot */
        igGroup_Register,                               /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0,        /* base class MetaObject accessor */
        thunk_igProjectiveShadowShader_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igProjectiveShadowShader_className_004e2090,  /* class name */
        0xF0,                                           /* instance size */
        igProjectiveShadowShader_GetVTable,             /* vtable getter */
        &igProjectiveShadowShader_InitFields,           /* field adder */
        0,                                              /* extra callback item */
        g_igProjectiveShadowShader_callbackList_0048b800  /* callback list */
    );
}

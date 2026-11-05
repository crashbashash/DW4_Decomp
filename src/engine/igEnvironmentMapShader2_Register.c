/* 0x001a15b0 igEnvironmentMapShader2_Register: registers class igEnvironmentMapShader2 with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igGroup_Register[];
extern char thunk_igEnvironmentMapShader2_GetMetaObject[];
extern char g_igEnvironmentMapShader2_callbackList_0048c120[];
extern char s_igEnvironmentMapShader2_className_004e27f0[];
extern char g_igEnvironmentMapShader2_metaObject_00561a98[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igEnvironmentMapShader2_InitFields();

void igEnvironmentMapShader2_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnvironmentMapShader2_metaObject_00561a98, /* published MetaObject slot */
        igGroup_Register,                              /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0,       /* base class MetaObject accessor */
        thunk_igEnvironmentMapShader2_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEnvironmentMapShader2_className_004e27f0,  /* class name */
        0x70,                                          /* instance size */
        0,                                             /* vtable getter */
        &igEnvironmentMapShader2_InitFields,           /* field adder */
        0,                                             /* extra callback item */
        g_igEnvironmentMapShader2_callbackList_0048c120  /* callback list */
    );
}

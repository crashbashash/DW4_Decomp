/* 0x001ab550 igPsx2EnvironmentMapShader_Register: registers class igPsx2EnvironmentMapShader with the object system, derived from igEnvironmentMapShader2.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEnvironmentMapShader2_Register[];
extern char thunk_igPsx2EnvironmentMapShader_GetMetaObject[];
extern char igPsx2EnvironmentMapShader_GetVTable[];
extern char igEnvironmentMapShader2_GetPublishedMetaObject[];
extern char g_igPsx2EnvironmentMapShader_callbackList[];
extern char igPsx2EnvironmentMapShader_className[];
extern char g_igPsx2EnvironmentMapShader_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igPsx2EnvironmentMapShader_InitFields();

void igPsx2EnvironmentMapShader_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2EnvironmentMapShader_metaObject,        /* published MetaObject slot */
        igEnvironmentMapShader2_Register,                        /* base class registrar */
        igEnvironmentMapShader2_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2EnvironmentMapShader_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igPsx2EnvironmentMapShader_className,         /* class name */
        0x7C,                                                    /* instance size */
        igPsx2EnvironmentMapShader_GetVTable,                    /* vtable getter */
        &igPsx2EnvironmentMapShader_InitFields,                  /* field adder */
        0,                                                       /* extra callback item */
        g_igPsx2EnvironmentMapShader_callbackList       /* callback list */
    );
}

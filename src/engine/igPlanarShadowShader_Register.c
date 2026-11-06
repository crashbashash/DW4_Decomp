/* 0x0019c400 igPlanarShadowShader_Register: registers class igPlanarShadowShader with the object system, derived from igAttrSet.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igPlanarShadowShader_GetVTable[];
extern char thunk_igPlanarShadowShader_GetMetaObject[];
extern char igAttrSet_GetPublishedMetaObject[];
extern char igAttrSet_Register[];
extern char g_igPlanarShadowShader_callbackList[];
extern char igPlanarShadowShader_className[];
extern char g_igPlanarShadowShader_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igPlanarShadowShader_InitFields();

void igPlanarShadowShader_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPlanarShadowShader_metaObject, /* published MetaObject slot */
        igAttrSet_Register,                         /* base class registrar */
        igAttrSet_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igPlanarShadowShader_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igPlanarShadowShader_className,  /* class name */
        0x70,                                       /* instance size */
        igPlanarShadowShader_GetVTable,             /* vtable getter */
        &igPlanarShadowShader_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igPlanarShadowShader_callbackList  /* callback list */
    );
}

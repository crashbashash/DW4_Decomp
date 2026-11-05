/* 0x0019c400 igPlanarShadowShader_Register: registers class igPlanarShadowShader with the object system, derived from igAttrSet.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igPlanarShadowShader_GetVTable[];
extern char thunk_igPlanarShadowShader_GetMetaObject[];
extern char igAttrSet_GetPublishedMetaObject_0019c490[];
extern char igAttrSet_Register[];
extern char g_igPlanarShadowShader_callbackList_0048bb50[];
extern char s_igPlanarShadowShader_className_004e22a0[];
extern char g_igPlanarShadowShader_metaObject_005617a8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igPlanarShadowShader_InitFields();

void igPlanarShadowShader_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPlanarShadowShader_metaObject_005617a8, /* published MetaObject slot */
        igAttrSet_Register,                         /* base class registrar */
        igAttrSet_GetPublishedMetaObject_0019c490,  /* base class MetaObject accessor */
        thunk_igPlanarShadowShader_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igPlanarShadowShader_className_004e22a0,  /* class name */
        0x70,                                       /* instance size */
        igPlanarShadowShader_GetVTable,             /* vtable getter */
        &igPlanarShadowShader_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        g_igPlanarShadowShader_callbackList_0048bb50  /* callback list */
    );
}

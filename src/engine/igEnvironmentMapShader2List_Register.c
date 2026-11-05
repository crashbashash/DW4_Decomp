/* 0x001a14d0 igEnvironmentMapShader2List_Register: registers class igEnvironmentMapShader2List with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igEnvironmentMapShader2List_GetVTable[];
extern char thunk_igEnvironmentMapShader2List_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igEnvironmentMapShader2List_callbackList_0048c110[];
extern char s_igEnvironmentMapShader2List_className_004e27d0[];
extern char g_igEnvironmentMapShader2List_metaObject_00561a90[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igEnvironmentMapShader2List_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnvironmentMapShader2List_metaObject_00561a90, /* published MetaObject slot */
        igObjectList_Register,                             /* base class registrar */
        igObjectList_GetPublishedMetaObject,               /* base class MetaObject accessor */
        thunk_igEnvironmentMapShader2List_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEnvironmentMapShader2List_className_004e27d0,  /* class name */
        0x14,                                              /* instance size */
        igEnvironmentMapShader2List_GetVTable,             /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        g_igEnvironmentMapShader2List_callbackList_0048c110  /* callback list */
    );
}

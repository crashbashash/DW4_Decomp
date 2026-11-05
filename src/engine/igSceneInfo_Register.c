/* 0x0019b280 igSceneInfo_Register: registers class igSceneInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igSceneInfo_GetVTable[];
extern char thunk_igSceneInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igSceneInfo_callbackList_0048b760[];
extern char s_igSceneInfo_className_004e2018[];
extern char g_igSceneInfo_metaObject_005615e0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igSceneInfo_InitFields();

void igSceneInfo_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSceneInfo_metaObject_005615e0,      /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50, /* base class MetaObject accessor */
        thunk_igSceneInfo_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igSceneInfo_className_004e2018,       /* class name */
        0x40,                                   /* instance size */
        igSceneInfo_GetVTable,                  /* vtable getter */
        &igSceneInfo_InitFields,                /* field adder */
        0,                                      /* extra callback item */
        g_igSceneInfo_callbackList_0048b760     /* callback list */
    );
}

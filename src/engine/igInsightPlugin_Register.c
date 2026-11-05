/* 0x00232790 igInsightPlugin_Register: registers class igInsightPlugin with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInsightPlugin_GetMetaObject[];
extern char igObject_Register[];
extern char s_igInsightPlugin_className_004e85b0[];
extern char g_igInsightPlugin_metaObject_0056db58[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igInsightPlugin_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInsightPlugin_metaObject_0056db58, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igInsightPlugin_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igInsightPlugin_className_004e85b0,  /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}

/* 0x00452af0 igCharMetricsMetaField_Register: registers class igCharMetricsMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject_0014e530[];
extern char igCompoundMetaField_Register[];
extern char igCharMetricsMetaField_GetVTable[];
extern char thunk_igCharMetricsMetaField_GetMetaObject[];
extern char g_igCharMetricsMetaField_callbackList_004d0890[];
extern char s_igCharMetricsMetaField_className_0051e7a0[];
extern char g_igCharMetricsMetaField_metaObject_0058c648[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igCharMetricsMetaField_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharMetricsMetaField_metaObject_0058c648,        /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject_0014e530, /* base class MetaObject accessor */
        thunk_igCharMetricsMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igCharMetricsMetaField_className_0051e7a0,         /* class name */
        0x38,                                                /* instance size */
        igCharMetricsMetaField_GetVTable,                    /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igCharMetricsMetaField_callbackList_004d0890       /* callback list */
    );
}

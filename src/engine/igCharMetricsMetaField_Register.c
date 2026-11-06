/* 0x00452af0 igCharMetricsMetaField_Register: registers class igCharMetricsMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char igCharMetricsMetaField_GetVTable[];
extern char thunk_igCharMetricsMetaField_GetMetaObject[];
extern char g_igCharMetricsMetaField_callbackList[];
extern char igCharMetricsMetaField_className[];
extern char g_igCharMetricsMetaField_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igCharMetricsMetaField_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharMetricsMetaField_metaObject,        /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCharMetricsMetaField_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igCharMetricsMetaField_className,         /* class name */
        0x38,                                                /* instance size */
        igCharMetricsMetaField_GetVTable,                    /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igCharMetricsMetaField_callbackList       /* callback list */
    );
}

/* 0x00232790 igInsightPlugin_Register: registers class igInsightPlugin with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInsightPlugin_GetMetaObject[];
extern char igObject_Register[];
extern char igInsightPlugin_className[];
extern char g_igInsightPlugin_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInsightPlugin_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInsightPlugin_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igInsightPlugin_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igInsightPlugin_className,  /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}

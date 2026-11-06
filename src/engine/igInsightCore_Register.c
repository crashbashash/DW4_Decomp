/* 0x00232df0 igInsightCore_Register: registers class igInsightCore with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igInsightCore_GetVTable[];
extern char thunk_igInsightCore_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInsightCore_callbackList[];
extern char igInsightCore_className[];
extern char g_igInsightCore_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00236140[4];
int igInsightCore_InitFields();

void igInsightCore_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInsightCore_metaObject,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igInsightCore_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igInsightCore_className,    /* class name */
        0x70,                                  /* instance size */
        igInsightCore_GetVTable,               /* vtable getter */
        &igInsightCore_InitFields,             /* field adder */
        thunk_FUN_00236140,                    /* extra callback item */
        g_igInsightCore_callbackList  /* callback list */
    );
}

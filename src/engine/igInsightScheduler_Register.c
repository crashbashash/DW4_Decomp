/* 0x00232520 igInsightScheduler_Register: registers class igInsightScheduler with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
 * The post-init hook is a three-instruction stub that stores the entry point 0x00232320 in this
 * MetaObject's `_abstractProxy` (igMetaObject +0x3c). */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInsightScheduler_GetMetaObject[];
extern char igObject_Register[];
extern char s_igInsightScheduler_className_004e8570[];
extern char g_igInsightScheduler_metaObject_0056db48[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
extern int igInsightScheduler_SetAbstractProxy_002325a0[4];
void igInsightScheduler_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        1,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInsightScheduler_metaObject_0056db48,         /* published MetaObject slot */
        igObject_Register,                                /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,            /* base class MetaObject accessor */
        thunk_igInsightScheduler_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igInsightScheduler_className_004e8570,          /* class name */
        8,                                                /* instance size */
        0,                                                /* vtable getter */
        &igInsightScheduler_SetAbstractProxy_002325a0[0], /* post-init hook */
        0,                                                /* extra callback item */
        0                                                 /* callback list */
    );
}

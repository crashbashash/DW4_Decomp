/* 0x00232160 igMessageDispatcher_Register: registers class igMessageDispatcher with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
 * The post-init hook is a three-instruction stub: it stores the entry point 0x00231fd0
 * (thunk_igFilterMessageDispatcher_GetMetaObject) in this MetaObject's
 * `_abstractProxy` (igMetaObject +0x3c). */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMessageDispatcher_GetMetaObject[];
extern char igObject_Register[];
extern char igMessageDispatcher_className[];
extern char g_igMessageDispatcher_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igMessageDispatcher_SetAbstractProxy_002321e0[4];
void igMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageDispatcher_metaObject,         /* published MetaObject slot */
        igObject_Register,                                 /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,             /* base class MetaObject accessor */
        thunk_igMessageDispatcher_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igMessageDispatcher_className,          /* class name */
        8,                                                 /* instance size */
        0,                                                 /* vtable getter */
        &igMessageDispatcher_SetAbstractProxy_002321e0[0], /* post-init hook */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}

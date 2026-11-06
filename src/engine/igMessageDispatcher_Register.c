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
        1, /* abstract */
        g_igMessageDispatcher_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageDispatcher_GetMetaObject,
        igMessageDispatcher_className,
        8, /* instance size */
        0,
        &igMessageDispatcher_SetAbstractProxy_002321e0[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

extern char igObject_CreateEmptyInitCallbacks[];
extern char igObject_GetNoParentMetaObject[];
extern char igObject_GetVTable[];
extern char igObject_GetMetaObject[];
extern char igObject_className[];
extern char g_igObject_metaObject[];
void *igMetaObject_RegisterClass();
int igObject_InitFields();

void *igObject_Register(void) {
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObject_metaObject,
        igObject_CreateEmptyInitCallbacks,
        igObject_GetNoParentMetaObject,
        igObject_GetMetaObject,
        igObject_className,
        8, /* instance size */
        igObject_GetVTable,
        &igObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *g_igGenericAttrDefaultManager_metaObject;

void FUN_00137ab0(int arg0) {
    FUN_00137b80();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F1C0, (igMemoryPoolView *)arg0);
}

igMetaObject *igGenericAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137b80();
    return g_igGenericAttrDefaultManager_metaObject;
}

int igGenericAttrDefaultManager_GetVTable(void) {
    struct O_137b40 o;
    int pad[2];
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igGenericAttrDefaultManager_vtable;
    return *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00137b80(void)
{
    igMetaObject_RunStaticInit(igGenericAttrDefaultManager_Register);
}

CallbackArray *igGenericAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGenericAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        thunk_igGenericAttrDefaultManager_GetMetaObject,
        "igGenericAttrDefaultManager",
        8, /* instance size */
        igGenericAttrDefaultManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGenericAttrDefaultManager_GetMetaObject(void) {
    igGenericAttrDefaultManager_GetMetaObject();
}


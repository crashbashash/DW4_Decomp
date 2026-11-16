igMetaObject *g_igFieldChangeViewList_metaObject;

igMetaObject *FUN_00450c70(void) {
    if (g_igFieldChangeViewList_metaObject == 0) {
        g_igFieldChangeViewList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFieldChangeViewList_metaObject;
}

igMetaObject *igFieldChangeViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeViewList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeViewList_EnsureRegistered();
    return g_igFieldChangeViewList_metaObject;
}

int igFieldChangeViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFieldChangeViewList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void igFieldChangeViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeViewList_Register);
}

static igMetaObjectCallback g_igFieldChangeViewList_callbackList[] = { igFieldChangeView_EnsureRegistered, 0 };

CallbackArray *igFieldChangeViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFieldChangeViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFieldChangeViewList_GetMetaObject,
        "igFieldChangeViewList",
        0x14, /* instance size */
        igFieldChangeViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFieldChangeViewList_callbackList /* callback list */
    );
}

void thunk_igFieldChangeViewList_GetMetaObject(void) {
    igFieldChangeViewList_GetMetaObject();
}


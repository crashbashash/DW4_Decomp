igMetaObject *g_igMediaList_metaObject;

void * igMediaList_Create(int pool) {
    igMediaList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMediaList_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMediaList_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMediaList_EnsureRegistered();
    return g_igMediaList_metaObject;
}

int igMediaList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igMediaList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igMediaList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMediaList_Register);
}

static igMetaObjectCallback g_igMediaList_callbackList[] = { igMedia_EnsureRegistered, 0 };

CallbackArray *igMediaList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMediaList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMediaList_GetMetaObjectFunction,
        "igMediaList",
        0x14,
        igMediaList_GetVTable,
        0,
        0,
        g_igMediaList_callbackList
    );
}

void igMediaList_GetMetaObjectFunction(void) {
    igMediaList_GetMetaObject();
}


igMetaObject *g_igVertexDataList_metaObject;

int igVertexDataList_Create(int arg0) {
    igVertexDataList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igVertexDataList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexDataList_GetOrCreateMetaObject(void) {
    if (g_igVertexDataList_metaObject == 0) {
        g_igVertexDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexDataList_metaObject;
}

igMetaObject *igVertexDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexDataList_EnsureRegistered();
    return g_igVertexDataList_metaObject;
}

int igVertexDataList_GetVTable(void) {
    union U_14b260 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igVertexDataList_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igVertexDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexDataList_Register);
}

static igMetaObjectCallback g_igVertexDataList_callbackList[] = { igVertexData_EnsureRegistered, 0 };

CallbackArray *igVertexDataList_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igVertexDataList_GetMetaObjectFunction,
        "igVertexDataList",
        0x14, /* instance size */
        igVertexDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexDataList_callbackList /* callback list */
    );
}

void igVertexDataList_GetMetaObjectFunction(void) {
    igVertexDataList_GetMetaObject();
}


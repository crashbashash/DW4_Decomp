int FUN_0019f480(int arg0) {
    igGraphPathList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igGraphPathList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igGraphPathList_metaObject;

igMetaObject *igGraphPathList_GetOrCreateMetaObject(void) {
    if (g_igGraphPathList_metaObject == 0) {
        g_igGraphPathList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGraphPathList_metaObject;
}

igMetaObject *igGraphPathList_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPathList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGraphPathList_EnsureRegistered();
    return g_igGraphPathList_metaObject;
}

int igGraphPathList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igGraphPathList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igGraphPathList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGraphPathList_Register);
}

static igMetaObjectCallback g_igGraphPathList_callbackList[] = { igGraphPath_EnsureRegistered, 0 };

CallbackArray *igGraphPathList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGraphPathList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igGraphPathList_GetMetaObjectFunction,
        "igGraphPathList",
        0x14, /* instance size */
        igGraphPathList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGraphPathList_callbackList /* callback list */
    );
}

void igGraphPathList_GetMetaObjectFunction(void) {
    igGraphPathList_GetMetaObject();
}


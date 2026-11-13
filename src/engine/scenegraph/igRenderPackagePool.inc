igMetaObject *FUN_00197930(void) {
    if (g_igRenderPackagePool_metaObject[0] == 0) {
        g_igRenderPackagePool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRenderPackagePool_metaObject[0];
}

igMetaObject *igRenderPackagePool_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackagePool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00197a10();
    return g_igRenderPackagePool_metaObject[0];
}

int igRenderPackagePool_GetVTable(void) {
    struct Obj_1979d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b4e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00197a10(void)
{
    igMetaObject_RunStaticInit(igRenderPackagePool_Register);
}

void igRenderPackagePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRenderPackagePool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igRenderPackagePool_GetMetaObject,
        igRenderPackagePool_className,
        0x20, /* instance size */
        igRenderPackagePool_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackagePool_callbackList /* callback list */
    );
}

void thunk_igRenderPackagePool_GetMetaObject(void) {
    igRenderPackagePool_GetMetaObject();
}

igMetaObject *FUN_00197aa0(void) {
    return g_igObjectPool_metaObject[0];
}


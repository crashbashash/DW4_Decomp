igMetaObject *g_igAnimationStatePool_metaObject;

igAnimationStatePool *igAnimationStatePool_Create(int allocator) {
    igAnimationStatePool_RunStaticInit();
    return (igAnimationStatePool *)igMetaObject_CreateInstance(g_igAnimationStatePool_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igAnimationStatePool_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationStatePool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationStatePool_RunStaticInit();
    return g_igAnimationStatePool_metaObject;
}

int igAnimationStatePool_GetVTable(void) {
    union U u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igAnimationStatePool_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igAnimationStatePool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAnimationStatePool_Register);
}

static igMetaObjectCallback g_igAnimationStatePool_callbackList[] = { igAnimationState_EnsureRegistered, 0 };

CallbackArray *igAnimationStatePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationStatePool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igAnimationStatePool_GetMetaObject,
        "igAnimationStatePool",
        0x20, /* instance size */
        igAnimationStatePool_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationStatePool_callbackList /* callback list */
    );
}

void thunk_igAnimationStatePool_GetMetaObject(void) {
    igAnimationStatePool_GetMetaObject();
}


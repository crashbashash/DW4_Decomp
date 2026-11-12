int igAnimationStatePool_Create(int allocator) {
    igAnimationStatePool_RunStaticInit();
    return igMetaObject_CreateInstance(g_igAnimationStatePool_metaObject[0], allocator);
}

igMetaObject *igAnimationStatePool_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject * *)g_igAnimationStatePool_metaObject)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationStatePool_RunStaticInit();
    return ((igMetaObject * *)g_igAnimationStatePool_metaObject)[0];
}

int igAnimationStatePool_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052a020[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void igAnimationStatePool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAnimationStatePool_Register);
}

void igAnimationStatePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationStatePool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igAnimationStatePool_GetMetaObject,
        igAnimationStatePool_className,
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


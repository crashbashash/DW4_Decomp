igMetaObject *g_igTimeAttrPool_metaObject;

igMetaObject *FUN_0019a290(void) {
    if (g_igTimeAttrPool_metaObject == 0) {
        g_igTimeAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTimeAttrPool_metaObject;
}

igMetaObject *igTimeAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a370();
    return g_igTimeAttrPool_metaObject;
}

int igTimeAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&g_igTimeAttrPool_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_0019a370(void)
{
    igMetaObject_RunStaticInit(igTimeAttrPool_Register);
}

static igMetaObjectCallback g_igTimeAttrPool_callbackList[] = { FUN_00131040, 0 };

void igTimeAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTimeAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTimeAttrPool_GetMetaObject,
        "igTimeAttrPool",
        0x20, /* instance size */
        igTimeAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTimeAttrPool_callbackList /* callback list */
    );
}

void thunk_igTimeAttrPool_GetMetaObject(void) {
    igTimeAttrPool_GetMetaObject();
}


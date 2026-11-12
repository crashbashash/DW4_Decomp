int FUN_0019a290(void) {
    if (DAT_005615b0[0] == 0) {
        DAT_005615b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005615b0[0];
}

igMetaObject *igTimeAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a370();
    return g_igTimeAttrPool_metaObject[0];
}

int igTimeAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052aef0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_0019a370(void)
{
    igMetaObject_RunStaticInit(igTimeAttrPool_Register);
}

void igTimeAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTimeAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTimeAttrPool_GetMetaObject,
        igTimeAttrPool_className,
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


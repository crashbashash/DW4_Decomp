igMetaObject *FUN_0019a570(void) {
    if (g_igLightStateAttrPool_metaObject[0] == 0) {
        g_igLightStateAttrPool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igLightStateAttrPool_metaObject[0];
}

igMetaObject *igLightStateAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a650();
    return g_igLightStateAttrPool_metaObject[0];
}

int igLightStateAttrPool_GetVTable(void) {
    struct Obj_19a610 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ae10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0019a650(void)
{
    igMetaObject_RunStaticInit(igLightStateAttrPool_Register);
}

void igLightStateAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLightStateAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igLightStateAttrPool_GetMetaObject,
        igLightStateAttrPool_className,
        0x20, /* instance size */
        igLightStateAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrPool_callbackList /* callback list */
    );
}

void thunk_igLightStateAttrPool_GetMetaObject(void) {
    igLightStateAttrPool_GetMetaObject();
}


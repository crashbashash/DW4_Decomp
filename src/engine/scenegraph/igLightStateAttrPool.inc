int FUN_0019a570(void) {
    if (DAT_005615c0[0] == 0) {
        DAT_005615c0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005615c0[0];
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
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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


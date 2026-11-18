igMetaObject *g_igVolumeList_metaObject;

InstanceNode *FUN_00186c00(int arg0) {
    FUN_00186d20();
    return (InstanceNode *)igMetaObject_CreateInstance((igMetaObject *)g_igVolumeList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_00186c40(void) {
    if (g_igVolumeList_metaObject == 0) {
        g_igVolumeList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVolumeList_metaObject;
}

igMetaObject *igVolumeList_GetMetaObject(void)
{
    igMetaObject *g = g_igVolumeList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00186d20();
    return g_igVolumeList_metaObject;
}

int igVolumeList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVolumeList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00186d20(void)
{
    igMetaObject_RunStaticInit(igVolumeList_Register);
}

static igMetaObjectCallback g_igVolumeList_callbackList[] = { FUN_00186b20, 0 };

CallbackArray *igVolumeList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVolumeList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVolumeList_GetMetaObject,
        "igVolumeList",
        0x14, /* instance size */
        igVolumeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVolumeList_callbackList /* callback list */
    );
}

void thunk_igVolumeList_GetMetaObject(void) {
    igVolumeList_GetMetaObject();
}


InstanceNode *FUN_00186c00(int arg0) {
    FUN_00186d20();
    return (InstanceNode *)igMetaObject_CreateInstance(*(int *)0x560F10, arg0);
}

int FUN_00186c40(void) {
    if (DAT_00560f10[0] == 0) {
        DAT_00560f10[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00560f10[0];
}

igMetaObject *igVolumeList_GetMetaObject(void)
{
    igMetaObject *g = g_igVolumeList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00186d20();
    return g_igVolumeList_metaObject[0];
}

int igVolumeList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00528100[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00186d20(void)
{
    igMetaObject_RunStaticInit(igVolumeList_Register);
}

void igVolumeList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVolumeList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVolumeList_GetMetaObject,
        igVolumeList_className,
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


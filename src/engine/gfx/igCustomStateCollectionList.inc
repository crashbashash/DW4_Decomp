int FUN_0014ee00(int arg0) {
    FUN_0014ef20();
    return igMetaObject_CreateInstance(*(int *)0x55FE68, arg0);
}

int FUN_0014ee40(void) {
    if (DAT_0055fe68[0] == 0) {
        DAT_0055fe68[0] = (int)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fe68[0];
}

igMetaObject *igCustomStateCollectionList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollectionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ef20();
    return g_igCustomStateCollectionList_metaObject[0];
}

int igCustomStateCollectionList_GetVTable(void) {
    struct Obj_14eee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526d80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0014ef20(void)
{
    igMetaObject_RunStaticInit(igCustomStateCollectionList_Register);
}

void igCustomStateCollectionList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateCollectionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateCollectionList_GetMetaObject,
        igCustomStateCollectionList_className,
        0x14, /* instance size */
        igCustomStateCollectionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateCollectionList_callbackList /* callback list */
    );
}

void thunk_igCustomStateCollectionList_GetMetaObject(void) {
    igCustomStateCollectionList_GetMetaObject();
}


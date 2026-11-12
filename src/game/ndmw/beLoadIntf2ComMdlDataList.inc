int FUN_003c72c0(void) {
    if (((int *)DAT_0058be68)[0] == 0) {
        ((int *)DAT_0058be68)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058be68)[0];
}

void *beLoadIntf2ComMdlDataList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be68[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c73a0();
    }
    return DAT_0058be68[0];
}

int beLoadIntf2ComMdlDataList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c870[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003c73a0(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlDataList_Register);
}

void *beLoadIntf2ComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadIntf2ComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLoadIntf2ComMdlDataList_GetMetaObject,
        beLoadIntf2ComMdlDataList_className,
        0x14, /* instance size */
        beLoadIntf2ComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLoadIntf2ComMdlDataList_callbackList /* callback list */
    );
}

void beLoadIntf2ComMdlDataList_GetMetaObject(void)
{
    beLoadIntf2ComMdlDataList_GetReadyMetaObject();
}


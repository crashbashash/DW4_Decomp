int FUN_003c5910(void) {
    if (((int *)DAT_0058bc90)[0] == 0) {
        ((int *)DAT_0058bc90)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bc90)[0];
}

void *beNDMWMcSlotList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bc90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c59f0();
    }
    return DAT_0058bc90[0];
}

int beNDMWMcSlotList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cc60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003c59f0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotList_Register);
}

void *beNDMWMcSlotList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWMcSlotList_GetMetaObject,
        beNDMWMcSlotList_className,
        0x14, /* instance size */
        beNDMWMcSlotList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWMcSlotList_callbackList /* callback list */
    );
}

void beNDMWMcSlotList_GetMetaObject(void)
{
    beNDMWMcSlotList_GetReadyMetaObject();
}


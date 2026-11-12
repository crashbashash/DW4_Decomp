int FUN_003c5520(void) {
    if (((int *)DAT_0058bc10)[0] == 0) {
        ((int *)DAT_0058bc10)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bc10)[0];
}

void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void) {
    struct G *g = DAT_0058bc10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c5600();
    }
    return DAT_0058bc10[0];
}

int beNDMWLoadSavePlWorkList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cd30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003c5600(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWorkList_Register);
}

void *beNDMWLoadSavePlWorkList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSavePlWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSavePlWorkList_GetMetaObject,
        beNDMWLoadSavePlWorkList_className,
        0x14, /* instance size */
        beNDMWLoadSavePlWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWorkList_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWorkList_GetMetaObject(void)
{
    beNDMWLoadSavePlWorkList_ResolveMetaObject();
}


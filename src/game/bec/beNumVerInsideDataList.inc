int FUN_0034dcd0(void) {
    if (((int *)DAT_005886a8)[0] == 0) {
        ((int *)DAT_005886a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005886a8)[0];
}

void *FUN_0034dd20(void) {
    struct G *g = DAT_005886a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034ddb0();
    }
    return DAT_005886a8[0];
}

int beNumVerInsideDataList_GetVTable(void) {
    struct Obj_34dd70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538390[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034ddb0(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideDataList_Register);
}

void *beNumVerInsideDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerInsideDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerInsideDataList_GetMetaObject,
        beNumVerInsideDataList_className,
        0x14, /* instance size */
        beNumVerInsideDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerInsideDataList_callbackList /* callback list */
    );
}

void beNumVerInsideDataList_GetMetaObject(void)
{
    FUN_0034dd20();
}


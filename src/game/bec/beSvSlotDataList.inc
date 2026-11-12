int FUN_0034a4a0(void) {
    if (((int *)DAT_00588330)[0] == 0) {
        ((int *)DAT_00588330)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588330)[0];
}

void *FUN_0034a4f0(void) {
    struct G *g = DAT_00588330[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034a580();
    }
    return DAT_00588330[0];
}

int beSvSlotDataList_GetVTable(void) {
    struct Obj_34a540 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538a90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034a580(void)
{
    igMetaObject_RunStaticInit(beSvSlotDataList_Register);
}

void *beSvSlotDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSvSlotDataList_GetMetaObject,
        beSvSlotDataList_className,
        0x14, /* instance size */
        beSvSlotDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSvSlotDataList_callbackList /* callback list */
    );
}

void beSvSlotDataList_GetMetaObject(void)
{
    FUN_0034a4f0();
}


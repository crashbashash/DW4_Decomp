int FUN_00360360(void) {
    if (((int *)DAT_00589588)[0] == 0) {
        ((int *)DAT_00589588)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589588)[0];
}

void *FUN_003603b0(void) {
    struct G *g = DAT_00589588[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360440();
    }
    return DAT_00589588[0];
}

int beGeneraterItemDataList_GetVTable(void) {
    struct Obj_360400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535d70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00360440(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataList_Register);
}

void *beGeneraterItemDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterItemDataList_GetMetaObject,
        beGeneraterItemDataList_className,
        0x14, /* instance size */
        beGeneraterItemDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataList_callbackList /* callback list */
    );
}

void beGeneraterItemDataList_GetMetaObject(void)
{
    FUN_003603b0();
}


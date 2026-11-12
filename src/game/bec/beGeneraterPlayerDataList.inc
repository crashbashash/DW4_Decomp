int FUN_0035ff20(void) {
    if (((int *)DAT_00589558)[0] == 0) {
        ((int *)DAT_00589558)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589558)[0];
}

void *FUN_0035ff70(void) {
    struct G *g = DAT_00589558[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360000();
    }
    return DAT_00589558[0];
}

int beGeneraterPlayerDataList_GetVTable(void) {
    union U_35ffc0 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00535e40[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_00360000(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerDataList_Register);
}

void *beGeneraterPlayerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterPlayerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterPlayerDataList_GetMetaObject,
        beGeneraterPlayerDataList_className,
        0x14, /* instance size */
        beGeneraterPlayerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterPlayerDataList_callbackList /* callback list */
    );
}

void beGeneraterPlayerDataList_GetMetaObject(void)
{
    FUN_0035ff70();
}


int FUN_0034ccc0(void) {
    if (((int *)DAT_00588548)[0] == 0) {
        ((int *)DAT_00588548)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588548)[0];
}

void *FUN_0034cd10(void) {
    struct G *g = DAT_00588548[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034cda0();
    }
    return DAT_00588548[0];
}

int bePadDataList_GetVTable(void) {
    union U_34cd60 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00538600[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_0034cda0(void)
{
    igMetaObject_RunStaticInit(bePadDataList_Register);
}

void *bePadDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePadDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        bePadDataList_GetMetaObject,
        bePadDataList_className,
        0x14, /* instance size */
        bePadDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePadDataList_callbackList /* callback list */
    );
}

void bePadDataList_GetMetaObject(void)
{
    FUN_0034cd10();
}


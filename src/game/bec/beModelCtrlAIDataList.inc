int FUN_003546d0(void) {
    if (((int *)DAT_00588cf8)[0] == 0) {
        ((int *)DAT_00588cf8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588cf8)[0];
}

void *FUN_00354720(void) {
    struct G *g = DAT_00588cf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003547b0();
    }
    return DAT_00588cf8[0];
}

int beModelCtrlAIDataList_GetVTable(void) {
    union U_354770 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00537890[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_003547b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIDataList_Register);
}

void *beModelCtrlAIDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIDataList_GetMetaObject,
        beModelCtrlAIDataList_className,
        0x14, /* instance size */
        beModelCtrlAIDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIDataList_callbackList /* callback list */
    );
}

void beModelCtrlAIDataList_GetMetaObject(void)
{
    FUN_00354720();
}


int FUN_0035a2a0(void) {
    if (((int *)DAT_00589140)[0] == 0) {
        ((int *)DAT_00589140)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589140)[0];
}

void *FUN_0035a2f0(void) {
    struct G *g = DAT_00589140[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a380();
    }
    return DAT_00589140[0];
}

int beMatCtrlDataList_GetVTable(void) {
    struct Obj_35a340 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536a30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035a380(void)
{
    igMetaObject_RunStaticInit(beMatCtrlDataList_Register);
}

void *beMatCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlDataList_GetMetaObject,
        beMatCtrlDataList_className,
        0x14, /* instance size */
        beMatCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlDataList_callbackList /* callback list */
    );
}

void beMatCtrlDataList_GetMetaObject(void)
{
    FUN_0035a2f0();
}


int FUN_003541b0(void) {
    if (((int *)DAT_00588c98)[0] == 0) {
        ((int *)DAT_00588c98)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588c98)[0];
}

void *FUN_00354200(void) {
    struct G *g = DAT_00588c98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00354290();
    }
    return DAT_00588c98[0];
}

int beModelCtrlAIMapList_GetVTable(void) {
    struct Obj_354250 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00537960[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00354290(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMapList_Register);
}

void *beModelCtrlAIMapList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIMapList_GetMetaObject,
        beModelCtrlAIMapList_className,
        0x14, /* instance size */
        beModelCtrlAIMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIMapList_callbackList /* callback list */
    );
}

void beModelCtrlAIMapList_GetMetaObject(void)
{
    FUN_00354200();
}


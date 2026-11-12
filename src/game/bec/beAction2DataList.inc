int FUN_0036d860(void) {
    if (((int *)DAT_0058a008)[0] == 0) {
        ((int *)DAT_0058a008)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058a008)[0];
}

void *FUN_0036d8b0(void) {
    struct G *g = DAT_0058a008[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036d940();
    }
    return DAT_0058a008[0];
}

int beAction2DataList_GetVTable(void) {
    struct Obj_36d900 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534020[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0036d940(void)
{
    igMetaObject_RunStaticInit(beAction2DataList_Register);
}

void *beAction2DataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2DataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAction2DataList_GetMetaObject,
        beAction2DataList_className,
        0x14, /* instance size */
        beAction2DataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAction2DataList_callbackList /* callback list */
    );
}

void beAction2DataList_GetMetaObject(void)
{
    FUN_0036d8b0();
}


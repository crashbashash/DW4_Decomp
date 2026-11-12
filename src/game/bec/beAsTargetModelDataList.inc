igMetaObject *FUN_0036b600(void) {
    if (g_beAsTargetModelDataList_metaObject[0] == 0) {
        g_beAsTargetModelDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beAsTargetModelDataList_metaObject[0];
}

void *FUN_0036b650(void) {
    unsigned char b;
    if (((void * *)g_beAsTargetModelDataList_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beAsTargetModelDataList_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0036b6e0();
done:
    return ((void * *)g_beAsTargetModelDataList_metaObject)[0];
}

int beAsTargetModelDataList_GetVTable(void) {
    struct Obj_36b6a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005345a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0036b6e0(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelDataList_Register);
}

void *beAsTargetModelDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAsTargetModelDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAsTargetModelDataList_GetMetaObject,
        beAsTargetModelDataList_className,
        0x14, /* instance size */
        beAsTargetModelDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAsTargetModelDataList_callbackList /* callback list */
    );
}

void beAsTargetModelDataList_GetMetaObject(void)
{
    FUN_0036b650();
}


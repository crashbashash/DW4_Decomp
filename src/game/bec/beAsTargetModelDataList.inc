igMetaObject *g_beAsTargetModelDataList_metaObject;

igMetaObject *beAsTargetModelDataList_GetOrCreateMetaObject(void) {
    if (g_beAsTargetModelDataList_metaObject == 0) {
        g_beAsTargetModelDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beAsTargetModelDataList_metaObject;
}

void *beAsTargetModelDataList_GetMetaObject(void) {
    unsigned char b;
    if (((void * *)&g_beAsTargetModelDataList_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beAsTargetModelDataList_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beAsTargetModelDataList_EnsureRegistered();
done:
    return ((void * *)&g_beAsTargetModelDataList_metaObject)[0];
}

int beAsTargetModelDataList_GetVTable(void) {
    struct Obj_36b6a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beAsTargetModelDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beAsTargetModelDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelDataList_Register);
}

static igMetaObjectCallback g_beAsTargetModelDataList_callbackList[] = { beAsTargetModelData_EnsureRegistered, 0 };

void *beAsTargetModelDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAsTargetModelDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAsTargetModelDataList_GetMetaObjectFunction,
        "beAsTargetModelDataList",
        0x14, /* instance size */
        beAsTargetModelDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAsTargetModelDataList_callbackList /* callback list */
    );
}

void beAsTargetModelDataList_GetMetaObjectFunction(void)
{
    beAsTargetModelDataList_GetMetaObject();
}


igMetaObject *g_beBaseInfoDataList_metaObject;

beBaseInfoDataList *beBaseInfoDataList_Create(int allocator) {
    beBaseInfoDataList_EnsureRegistered();
    return (beBaseInfoDataList *)igMetaObject_CreateInstance(*(int *)0x589E00, allocator);
}

igMetaObject *beBaseInfoDataList_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoDataList_metaObject == 0) {
        g_beBaseInfoDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBaseInfoDataList_metaObject;
}

void *beBaseInfoDataList_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoDataList_metaObject;
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
    }
    beBaseInfoDataList_EnsureRegistered();
end:
    return g_beBaseInfoDataList_metaObject;
}

int beBaseInfoDataList_GetVTable(void) {
    beBaseInfoDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beBaseInfoDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoDataList_Register);
}

static igMetaObjectCallback g_beBaseInfoDataList_callbackList[] = { beBaseInfoData_EnsureRegistered, 0 };

void *beBaseInfoDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoDataList_GetMetaObjectFunction,
        "beBaseInfoDataList",
        0x14, /* instance size */
        beBaseInfoDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoDataList_callbackList /* callback list */
    );
}

void beBaseInfoDataList_GetMetaObjectFunction(void)
{
    beBaseInfoDataList_GetMetaObject();
}


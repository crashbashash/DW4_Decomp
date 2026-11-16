igMetaObject *g_bePadDataList_metaObject;

igMetaObject *bePadDataList_GetOrCreateMetaObject(void) {
    if (g_bePadDataList_metaObject == 0) {
        g_bePadDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_bePadDataList_metaObject;
}

void *bePadDataList_GetMetaObject(void) {
    igMetaObject *g = g_bePadDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadDataList_EnsureRegistered();
    }
    return g_bePadDataList_metaObject;
}

int bePadDataList_GetVTable(void) {
    bePadDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_bePadDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void bePadDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadDataList_Register);
}

static igMetaObjectCallback g_bePadDataList_callbackList[] = { bePadData_EnsureRegistered, 0 };

void *bePadDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        bePadDataList_GetMetaObjectFunction,
        "bePadDataList",
        0x14, /* instance size */
        bePadDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePadDataList_callbackList /* callback list */
    );
}

void bePadDataList_GetMetaObjectFunction(void)
{
    bePadDataList_GetMetaObject();
}


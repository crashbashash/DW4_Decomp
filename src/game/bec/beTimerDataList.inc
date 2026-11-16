igMetaObject *g_beTimerDataList_metaObject;

igMetaObject *beTimerDataList_GetOrCreateMetaObject(void) {
    if (g_beTimerDataList_metaObject == 0) {
        g_beTimerDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTimerDataList_metaObject;
}

void *beTimerDataList_GetMetaObject(void) {
    igMetaObject *g = g_beTimerDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTimerDataList_EnsureRegistered();
    }
    return g_beTimerDataList_metaObject;
}

int beTimerDataList_GetVTable(void) {
    beTimerDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beTimerDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beTimerDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTimerDataList_Register);
}

static igMetaObjectCallback g_beTimerDataList_callbackList[] = { beTimerData_EnsureRegistered, 0 };

void *beTimerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTimerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTimerDataList_GetMetaObjectFunction,
        "beTimerDataList",
        0x14, /* instance size */
        beTimerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTimerDataList_callbackList /* callback list */
    );
}

void beTimerDataList_GetMetaObjectFunction(void)
{
    beTimerDataList_GetMetaObject();
}


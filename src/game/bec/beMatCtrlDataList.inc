igMetaObject *g_beMatCtrlDataList_metaObject;

igMetaObject *beMatCtrlDataList_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlDataList_metaObject == 0) {
        g_beMatCtrlDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlDataList_metaObject;
}

void *beMatCtrlDataList_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlDataList_EnsureRegistered();
    }
    return g_beMatCtrlDataList_metaObject;
}

int beMatCtrlDataList_GetVTable(void) {
    beMatCtrlDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMatCtrlDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beMatCtrlDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlDataList_Register);
}

static igMetaObjectCallback g_beMatCtrlDataList_callbackList[] = { beMatCtrlData_EnsureRegistered, 0 };

void *beMatCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlDataList_GetMetaObjectFunction,
        "beMatCtrlDataList",
        0x14, /* instance size */
        beMatCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlDataList_callbackList /* callback list */
    );
}

void beMatCtrlDataList_GetMetaObjectFunction(void)
{
    beMatCtrlDataList_GetMetaObject();
}


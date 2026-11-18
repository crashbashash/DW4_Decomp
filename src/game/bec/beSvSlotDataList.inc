igMetaObject *g_beSvSlotDataList_metaObject;

igMetaObject *beSvSlotDataList_GetOrCreateMetaObject(void) {
    if (g_beSvSlotDataList_metaObject == 0) {
        g_beSvSlotDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSvSlotDataList_metaObject;
}

void *beSvSlotDataList_GetMetaObject(void) {
    igMetaObject *g = g_beSvSlotDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvSlotDataList_EnsureRegistered();
    }
    return g_beSvSlotDataList_metaObject;
}

int beSvSlotDataList_GetVTable(void) {
    beSvSlotDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvSlotDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beSvSlotDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvSlotDataList_Register);
}

static igMetaObjectCallback g_beSvSlotDataList_callbackList[] = { beSvSlotData_EnsureRegistered, 0 };

CallbackArray *beSvSlotDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvSlotDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSvSlotDataList_GetMetaObjectFunction,
        "beSvSlotDataList",
        0x14, /* instance size */
        beSvSlotDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSvSlotDataList_callbackList /* callback list */
    );
}

void beSvSlotDataList_GetMetaObjectFunction(void)
{
    beSvSlotDataList_GetMetaObject();
}


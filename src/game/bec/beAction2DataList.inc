igMetaObject *g_beAction2DataList_metaObject;

igMetaObject *beAction2DataList_GetOrCreateMetaObject(void) {
    if (g_beAction2DataList_metaObject == 0) {
        g_beAction2DataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beAction2DataList_metaObject;
}

void *beAction2DataList_GetMetaObject(void) {
    igMetaObject *g = g_beAction2DataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2DataList_EnsureRegistered();
    }
    return g_beAction2DataList_metaObject;
}

int beAction2DataList_GetVTable(void) {
    beAction2DataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beAction2DataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beAction2DataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2DataList_Register);
}

static igMetaObjectCallback g_beAction2DataList_callbackList[] = { beAction2Data_EnsureRegistered, 0 };

CallbackArray *beAction2DataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2DataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAction2DataList_GetMetaObjectFunction,
        "beAction2DataList",
        0x14, /* instance size */
        beAction2DataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAction2DataList_callbackList /* callback list */
    );
}

void beAction2DataList_GetMetaObjectFunction(void)
{
    beAction2DataList_GetMetaObject();
}


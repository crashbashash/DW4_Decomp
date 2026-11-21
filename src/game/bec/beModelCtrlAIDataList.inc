igMetaObject *g_beModelCtrlAIDataList_metaObject;

igMetaObject *beModelCtrlAIDataList_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlAIDataList_metaObject == 0) {
        g_beModelCtrlAIDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beModelCtrlAIDataList_metaObject;
}

void *beModelCtrlAIDataList_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlAIDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlAIDataList_EnsureRegistered();
    }
    return g_beModelCtrlAIDataList_metaObject;
}

int beModelCtrlAIDataList_GetVTable(void) {
    beModelCtrlAIDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlAIDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlAIDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIDataList_Register);
}

static igMetaObjectCallback g_beModelCtrlAIDataList_callbackList[] = { beModelCtrlAIData_EnsureRegistered, 0 };

CallbackArray *beModelCtrlAIDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beModelCtrlAIDataList_GetMetaObjectFunction,
        "beModelCtrlAIDataList",
        0x14, /* instance size */
        beModelCtrlAIDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIDataList_callbackList /* callback list */
    );
}

void beModelCtrlAIDataList_GetMetaObjectFunction(void)
{
    beModelCtrlAIDataList_GetMetaObject();
}


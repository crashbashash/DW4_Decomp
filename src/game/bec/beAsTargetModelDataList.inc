igMetaObject *g_beAsTargetModelDataList_metaObject;

igMetaObject *beAsTargetModelDataList_GetOrCreateMetaObject(void) {
    if (g_beAsTargetModelDataList_metaObject == 0) {
        g_beAsTargetModelDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beAsTargetModelDataList_metaObject;
}

void *beAsTargetModelDataList_GetMetaObject(void) {
    unsigned char b;
    if (g_beAsTargetModelDataList_metaObject != 0) {
        b = (g_beAsTargetModelDataList_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beAsTargetModelDataList_EnsureRegistered();
done:
    return g_beAsTargetModelDataList_metaObject;
}

int beAsTargetModelDataList_GetVTable(void) {
    beAsTargetModelDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beAsTargetModelDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beAsTargetModelDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelDataList_Register);
}

static igMetaObjectCallback g_beAsTargetModelDataList_callbackList[] = { beAsTargetModelData_EnsureRegistered, 0 };

CallbackArray *beAsTargetModelDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAsTargetModelDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
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


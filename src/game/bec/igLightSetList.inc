igMetaObject *g_igLightSetList_metaObject;

igMetaObject *igLightSetList_GetOrCreateMetaObject(void) {
    if (g_igLightSetList_metaObject == 0) {
        g_igLightSetList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightSetList_metaObject;
}

void *igLightSetList_GetMetaObject(void) {
    bool ok;
    if (g_igLightSetList_metaObject == 0) goto make;
    ok = !!(g_igLightSetList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    igLightSetList_EnsureRegistered();
done:;
    return g_igLightSetList_metaObject;
}

int igLightSetList_GetVTable(void) {
    igLightSetList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igLightSetList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igLightSetList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightSetList_Register);
}

static igMetaObjectCallback g_igLightSetList_callbackList[] = { Gap::Sg::igLightSet::arkRegister, 0 };

CallbackArray *igLightSetList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightSetList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igLightSetList_GetMetaObjectFunction,
        "igLightSetList",
        0x14, /* instance size */
        igLightSetList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightSetList_callbackList /* callback list */
    );
}

void igLightSetList_GetMetaObjectFunction(void)
{
    igLightSetList_GetMetaObject();
}


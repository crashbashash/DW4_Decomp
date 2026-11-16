igMetaObject *g_igLightSetList_metaObject;

igMetaObject *igLightSetList_GetOrCreateMetaObject(void) {
    if (g_igLightSetList_metaObject == 0) {
        g_igLightSetList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_35bc10 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igLightSetList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igLightSetList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightSetList_Register);
}

static igMetaObjectCallback g_igLightSetList_callbackList[] = { igLightSet_EnsureRegistered, 0 };

void *igLightSetList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightSetList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
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


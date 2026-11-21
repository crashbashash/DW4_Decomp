igMetaObject *g_bePlaySEList_metaObject;

igMetaObject *bePlaySEList_GetOrCreateMetaObject(void) {
    if (g_bePlaySEList_metaObject == 0) {
        g_bePlaySEList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_bePlaySEList_metaObject;
}

igMetaObject *bePlaySEList_GetMetaObject(void) {
    if (g_bePlaySEList_metaObject == 0 || !isValid(g_bePlaySEList_metaObject)) bePlaySEList_EnsureRegistered();
    return g_bePlaySEList_metaObject;
}

int bePlaySEList_GetVTable(void) {
    bePlaySEList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_bePlaySEList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void bePlaySEList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePlaySEList_Register);
}

static igMetaObjectCallback g_bePlaySEList_callbackList[] = { bePlaySE_EnsureRegistered, 0 };

CallbackArray *bePlaySEList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePlaySEList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        bePlaySEList_GetMetaObjectFunction,
        "bePlaySEList",
        0x14, /* instance size */
        bePlaySEList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePlaySEList_callbackList /* callback list */
    );
}

void bePlaySEList_GetMetaObjectFunction(void)
{
    bePlaySEList_GetMetaObject();
}


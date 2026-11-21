igMetaObject *g_beBaseInfoRamList_metaObject;

igMetaObject *beBaseInfoRamList_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoRamList_metaObject == 0) {
        g_beBaseInfoRamList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBaseInfoRamList_metaObject;
}

void *beBaseInfoRamList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beBaseInfoRamList_metaObject;
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
    }
    beBaseInfoRamList_EnsureRegistered();
end:
    return g_beBaseInfoRamList_metaObject;
}

int beBaseInfoRamList_GetVTable(void) {
    beBaseInfoRamList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoRamList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beBaseInfoRamList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamList_Register);
}

static igMetaObjectCallback g_beBaseInfoRamList_callbackList[] = { beBaseInfoRam_EnsureRegistered, 0 };

CallbackArray *beBaseInfoRamList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoRamList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)beBaseInfoRamList_GetMetaObject,
        "beBaseInfoRamList",
        0x14, /* instance size */
        beBaseInfoRamList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoRamList_callbackList /* callback list */
    );
}

void *beBaseInfoRamList_GetMetaObject(void)
{
    return beBaseInfoRamList_GetReadyMetaObject();
}


igMetaObject *g_beNDMWLoadIntf2DegiStateList_metaObject;

igMetaObject *beNDMWLoadIntf2DegiStateList_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2DegiStateList_metaObject == 0) {
        g_beNDMWLoadIntf2DegiStateList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadIntf2DegiStateList_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateList_ResolveMetaObject(void) {
    if (g_beNDMWLoadIntf2DegiStateList_metaObject == 0 || !isValid(g_beNDMWLoadIntf2DegiStateList_metaObject)) beNDMWLoadIntf2DegiStateList_EnsureRegistered();
    return g_beNDMWLoadIntf2DegiStateList_metaObject;
}

int beNDMWLoadIntf2DegiStateList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_beNDMWLoadIntf2DegiStateList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void beNDMWLoadIntf2DegiStateList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateList_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DegiStateList_callbackList[] = { beNDMWLoadIntf2DegiState_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2DegiStateList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DegiStateList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateList_GetMetaObject,
        "beNDMWLoadIntf2DegiStateList",
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateList_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiStateList_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiStateList_ResolveMetaObject();
}


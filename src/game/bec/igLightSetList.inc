igMetaObject *FUN_0035bb70(void) {
    if (g_igLightSetList_metaObject[0] == 0) {
        g_igLightSetList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igLightSetList_metaObject[0];
}

void *FUN_0035bbc0(void) {
    bool ok;
    if (g_igLightSetList_metaObject[0] == 0) goto make;
    ok = !!(g_igLightSetList_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0035bc50();
done:;
    return g_igLightSetList_metaObject[0];
}

int igLightSetList_GetVTable(void) {
    struct Obj_35bc10 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536750[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035bc50(void)
{
    igMetaObject_RunStaticInit(igLightSetList_Register);
}

void *igLightSetList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightSetList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igLightSetList_GetMetaObject,
        igLightSetList_className,
        0x14, /* instance size */
        igLightSetList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightSetList_callbackList /* callback list */
    );
}

void igLightSetList_GetMetaObject(void)
{
    FUN_0035bbc0();
}


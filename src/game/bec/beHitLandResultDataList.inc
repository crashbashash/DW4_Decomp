igMetaObject *g_beHitLandResultDataList_metaObject;

igMetaObject *beHitLandResultDataList_GetOrCreateMetaObject(void) {
    if (g_beHitLandResultDataList_metaObject == 0) {
        g_beHitLandResultDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandResultDataList_metaObject;
}

void *beHitLandResultDataList_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandResultDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandResultDataList_EnsureRegistered();
    }
    return g_beHitLandResultDataList_metaObject;
}

int beHitLandResultDataList_GetVTable(void) {
    beHitLandResultDataList obj;
    int off;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beHitLandResultDataList_vtable[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)&obj + off);
}

void beHitLandResultDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandResultDataList_Register);
}

static igMetaObjectCallback g_beHitLandResultDataList_callbackList[] = { beHitLandResultData_EnsureRegistered, 0 };

void *beHitLandResultDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandResultDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beHitLandResultDataList_GetMetaObjectFunction,
        "beHitLandResultDataList",
        0x14, /* instance size */
        beHitLandResultDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beHitLandResultDataList_callbackList /* callback list */
    );
}

void beHitLandResultDataList_GetMetaObjectFunction(void)
{
    beHitLandResultDataList_GetMetaObject();
}


igMetaObject *g_beBaseInfoList_metaObject;

igMetaObject *beBaseInfoList_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoList_metaObject == 0) {
        g_beBaseInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBaseInfoList_metaObject;
}

igMetaObject *beBaseInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beBaseInfoList_EnsureRegistered();
done:
    return g_beBaseInfoList_metaObject;
}

int beBaseInfoList_GetVTable(void) {
    struct Obj_36ab90 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beBaseInfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beBaseInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoList_Register);
}

static igMetaObjectCallback g_beBaseInfoList_callbackList[] = { beBaseInfo_EnsureRegistered, 0 };

void *beBaseInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoList_GetMetaObjectFunction,
        "beBaseInfoList",
        0x14, /* instance size */
        beBaseInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoList_callbackList /* callback list */
    );
}

void beBaseInfoList_GetMetaObjectFunction(void)
{
    beBaseInfoList_GetMetaObject();
}


igMetaObject *g_beGeneraterItemDataOneList_metaObject;

igMetaObject *beGeneraterItemDataOneList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterItemDataOneList_metaObject == 0) {
        g_beGeneraterItemDataOneList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterItemDataOneList_metaObject;
}

void *beGeneraterItemDataOneList_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterItemDataOneList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterItemDataOneList_EnsureRegistered();
    }
    return g_beGeneraterItemDataOneList_metaObject;
}

int beGeneraterItemDataOneList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&g_beGeneraterItemDataOneList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void beGeneraterItemDataOneList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOneList_Register);
}

static igMetaObjectCallback g_beGeneraterItemDataOneList_callbackList[] = { beGeneraterItemDataOne_EnsureRegistered, 0 };

void *beGeneraterItemDataOneList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemDataOneList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterItemDataOneList_GetMetaObjectFunction,
        "beGeneraterItemDataOneList",
        0x14, /* instance size */
        beGeneraterItemDataOneList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataOneList_callbackList /* callback list */
    );
}

void beGeneraterItemDataOneList_GetMetaObjectFunction(void)
{
    beGeneraterItemDataOneList_GetMetaObject();
}


igMetaObject *g_beShadow01InfoList_metaObject;

igMetaObject *beShadow01InfoList_GetOrCreateMetaObject(void) {
    if (g_beShadow01InfoList_metaObject == 0) {
        g_beShadow01InfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beShadow01InfoList_metaObject;
}

void *beShadow01InfoList_GetMetaObject(void) {
    igMetaObject *g = g_beShadow01InfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beShadow01InfoList_EnsureRegistered();
    }
    return g_beShadow01InfoList_metaObject;
}

int beShadow01InfoList_GetVTable(void) {
    beShadow01InfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beShadow01InfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beShadow01InfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beShadow01InfoList_Register);
}

static igMetaObjectCallback g_beShadow01InfoList_callbackList[] = { beShadow01Info_EnsureRegistered, 0 };

void *beShadow01InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beShadow01InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beShadow01InfoList_GetMetaObjectFunction,
        "beShadow01InfoList",
        0x14, /* instance size */
        beShadow01InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beShadow01InfoList_callbackList /* callback list */
    );
}

void beShadow01InfoList_GetMetaObjectFunction(void)
{
    beShadow01InfoList_GetMetaObject();
}


igMetaObject *g_beDemoManagerWorkList_metaObject;

igMetaObject *beDemoManagerWorkList_GetOrCreateMetaObject(void) {
    if (g_beDemoManagerWorkList_metaObject == 0) {
        g_beDemoManagerWorkList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDemoManagerWorkList_metaObject;
}

void *beDemoManagerWorkList_GetMetaObject(void) {
    igMetaObject *g = g_beDemoManagerWorkList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDemoManagerWorkList_EnsureRegistered();
    }
    return g_beDemoManagerWorkList_metaObject;
}

int beDemoManagerWorkList_GetVTable(void) {
    beDemoManagerWorkList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDemoManagerWorkList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beDemoManagerWorkList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWorkList_Register);
}

static igMetaObjectCallback g_beDemoManagerWorkList_callbackList[] = { beDemoManagerWork_EnsureRegistered, 0 };

void *beDemoManagerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoManagerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDemoManagerWorkList_GetMetaObjectFunction,
        "beDemoManagerWorkList",
        0x14, /* instance size */
        beDemoManagerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDemoManagerWorkList_callbackList /* callback list */
    );
}

void beDemoManagerWorkList_GetMetaObjectFunction(void)
{
    beDemoManagerWorkList_GetMetaObject();
}


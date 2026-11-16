igMetaObject *g_beGroupKeepList_metaObject;

igMetaObject *beGroupKeepList_GetOrCreateMetaObject(void) {
    if (g_beGroupKeepList_metaObject == 0) {
        g_beGroupKeepList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGroupKeepList_metaObject;
}

void *beGroupKeepList_GetMetaObject(void) {
    igMetaObject *g = g_beGroupKeepList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGroupKeepList_EnsureRegistered();
    }
    return g_beGroupKeepList_metaObject;
}

int beGroupKeepList_GetVTable(void) {
    beGroupKeepList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beGroupKeepList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beGroupKeepList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGroupKeepList_Register);
}

static igMetaObjectCallback g_beGroupKeepList_callbackList[] = { beGroupKeep_EnsureRegistered, 0 };

void *beGroupKeepList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGroupKeepList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGroupKeepList_GetMetaObjectFunction,
        "beGroupKeepList",
        0x14, /* instance size */
        beGroupKeepList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGroupKeepList_callbackList /* callback list */
    );
}

void beGroupKeepList_GetMetaObjectFunction(void)
{
    beGroupKeepList_GetMetaObject();
}


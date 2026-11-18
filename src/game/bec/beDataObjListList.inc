igMetaObject *g_beDataObjListList_metaObject;

beDataObjListList *beDataObjListList_Create(int allocator) {
    beDataObjListList_EnsureRegistered();
    return (beDataObjListList *)igMetaObject_CreateInstance(g_beDataObjListList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beDataObjListList_GetOrCreateMetaObject(void) {
    if (g_beDataObjListList_metaObject == 0) {
        g_beDataObjListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDataObjListList_metaObject;
}

igMetaObject *beDataObjListList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjListList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beDataObjListList_EnsureRegistered();
done:
    return g_beDataObjListList_metaObject;
}

int beDataObjListList_GetVTable(void) {
    beDataObjListList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDataObjListList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beDataObjListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjListList_Register);
}

static igMetaObjectCallback g_beDataObjListList_callbackList[] = { beDataObjList_EnsureRegistered, 0 };

CallbackArray *beDataObjListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjListList_GetMetaObjectFunction,
        "beDataObjListList",
        0x14, /* instance size */
        beDataObjListList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataObjListList_callbackList /* callback list */
    );
}

void beDataObjListList_GetMetaObjectFunction(void)
{
    beDataObjListList_GetMetaObject();
}


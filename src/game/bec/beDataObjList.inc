igMetaObject *g_beDataObjList_metaObject;

beDataObjList *beDataObjList_Create(int allocator) {
    beDataObjList_EnsureRegistered();
    return (beDataObjList *)igMetaObject_CreateInstance(g_beDataObjList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beDataObjList_GetOrCreateMetaObject(void) {
    if (g_beDataObjList_metaObject == 0) {
        g_beDataObjList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDataObjList_metaObject;
}

igMetaObject *beDataObjList_GetMetaObject(void) {
    if (g_beDataObjList_metaObject == 0 || !isValid(g_beDataObjList_metaObject)) beDataObjList_EnsureRegistered();
    return g_beDataObjList_metaObject;
}

int beDataObjList_GetVTable(void) {
    beDataObjList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDataObjList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beDataObjList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjList_Register);
}

static igMetaObjectCallback g_beDataObjList_callbackList[] = { Gap::Core::igNamedObject::arkRegister, 0 };

CallbackArray *beDataObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beDataObjList_GetMetaObjectFunction,
        "beDataObjList",
        0x14, /* instance size */
        beDataObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataObjList_callbackList /* callback list */
    );
}

void beDataObjList_GetMetaObjectFunction(void)
{
    beDataObjList_GetMetaObject();
}


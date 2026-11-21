igMetaObject *g_igCustomStateFieldList_metaObject;

int igCustomStateFieldList_Create(int arg0) {
    igCustomStateFieldList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igCustomStateFieldList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igCustomStateFieldList_GetOrCreateMetaObject(void) {
    if (g_igCustomStateFieldList_metaObject == 0) {
        g_igCustomStateFieldList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCustomStateFieldList_metaObject;
}

igMetaObject *igCustomStateFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateFieldList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCustomStateFieldList_EnsureRegistered();
    return g_igCustomStateFieldList_metaObject;
}

int igCustomStateFieldList_GetVTable(void) {
    struct Obj_14ea10 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCustomStateFieldList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCustomStateFieldList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCustomStateFieldList_Register);
}

static igMetaObjectCallback g_igCustomStateFieldList_callbackList[] = { igCustomStateField_EnsureRegistered, 0 };

CallbackArray *igCustomStateFieldList_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCustomStateFieldList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igCustomStateFieldList_GetMetaObjectFunction,
        "igCustomStateFieldList",
        0x14, /* instance size */
        igCustomStateFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateFieldList_callbackList /* callback list */
    );
}

void igCustomStateFieldList_GetMetaObjectFunction(void) {
    igCustomStateFieldList_GetMetaObject();
}


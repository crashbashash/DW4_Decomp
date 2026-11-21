igMetaObject *g_igAttrStackList_metaObject;

igMetaObject *igAttrStackList_GetOrCreateMetaObject(void) {
    if (g_igAttrStackList_metaObject == 0) {
        g_igAttrStackList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrStackList_metaObject;
}

igMetaObject *igAttrStackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrStackList_EnsureRegistered();
    return g_igAttrStackList_metaObject;
}

int igAttrStackList_GetVTable(void) {
    struct Obj_1a59a0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAttrStackList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAttrStackList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrStackList_Register);
}

static igMetaObjectCallback g_igAttrStackList_callbackList[] = { igAttrStack_EnsureRegistered, 0 };

CallbackArray *igAttrStackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrStackList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igAttrStackList_GetMetaObjectFunction,
        "igAttrStackList",
        0x14, /* instance size */
        igAttrStackList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrStackList_callbackList /* callback list */
    );
}

void igAttrStackList_GetMetaObjectFunction(void) {
    igAttrStackList_GetMetaObject();
}


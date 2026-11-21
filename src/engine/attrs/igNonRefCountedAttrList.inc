igMetaObject *g_igNonRefCountedAttrList_metaObject;

igMetaObject *igNonRefCountedAttrList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedAttrList_metaObject == 0) {
        g_igNonRefCountedAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedAttrList_metaObject;
}

igMetaObject *igNonRefCountedAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedAttrList_EnsureRegistered();
    return g_igNonRefCountedAttrList_metaObject;
}

int igNonRefCountedAttrList_GetVTable(void) {
    struct Obj_13ade0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedAttrList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedAttrList_Register);
}

static igMetaObjectCallback g_igNonRefCountedAttrList_callbackList[] = { Gap::Attrs::igAttr::arkRegister, 0 };

CallbackArray *igNonRefCountedAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedAttrList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedAttrList_GetMetaObjectFunction,
        "igNonRefCountedAttrList",
        0x14, /* instance size */
        igNonRefCountedAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrList_callbackList /* callback list */
    );
}

void igNonRefCountedAttrList_GetMetaObjectFunction(void) {
    igNonRefCountedAttrList_GetMetaObject();
}

int FUN_0013aeb0(void) {
    return (int)g_igNonRefCountedObjectList_metaObject;
}


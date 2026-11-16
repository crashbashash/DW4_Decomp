igMetaObject *g_igAttrList_metaObject;

void FUN_0013aec0(int arg0) {
    igAttrList_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F460, (igMemoryPoolView *)arg0);
}

igMetaObject *igAttrList_GetOrCreateMetaObject(void) {
    if (g_igAttrList_metaObject == 0) {
        g_igAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrList_metaObject;
}

igMetaObject *igAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrList_EnsureRegistered();
    return g_igAttrList_metaObject;
}

int igAttrList_GetVTable(void) {
    struct Obj_13afa0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAttrList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrList_Register);
}

static igMetaObjectCallback g_igAttrList_callbackList[] = { FUN_0013b110, 0 };

CallbackArray *igAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrList_GetMetaObject,
        "igAttrList",
        0x14, /* instance size */
        igAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrList_callbackList /* callback list */
    );
}

void thunk_igAttrList_GetMetaObject(void) {
    igAttrList_GetMetaObject();
}


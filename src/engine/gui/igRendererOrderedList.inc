igMetaObject *g_igRendererOrderedList_metaObject;

igRendererOrderedList *igRendererOrderedList_CreateInstance(int allocator) {
    igRendererOrderedList_EnsureRegistered();
    return (igRendererOrderedList *)igMetaObject_CreateInstance(g_igRendererOrderedList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igRendererOrderedList_GetOrCreateMetaObject(void) {
    if (g_igRendererOrderedList_metaObject == 0) {
        g_igRendererOrderedList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRendererOrderedList_metaObject;
}

igMetaObject *igRendererOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igRendererOrderedList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRendererOrderedList_EnsureRegistered();
    return g_igRendererOrderedList_metaObject;
}

int igRendererOrderedList_GetVTable(void) {
    struct Obj_44c570 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &g_igRendererOrderedList_vtable[0];
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igRendererOrderedList_vtable[0];
    FUN_0044c5e0((int **)&obj, 0);
    return r;
}

int **FUN_0044c5e0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541dd0[0];
        if (arg0 != 0) {
            *arg0 = &g_igDependencyOrderedList_vtable[0];
            igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 0x14), -1);
            igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 0x10), -1);
            igSmartPointer_igDependencyList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 0xC), -1);
            igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void igRendererOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRendererOrderedList_Register);
}

static igMetaObjectCallback g_igRendererOrderedList_callbackList[] = { igRenderer_EnsureRegistered, 0 };

CallbackArray *igRendererOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRendererOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        igRendererOrderedList_GetMetaObjectFunction,
        "igRendererOrderedList",
        0x1C, /* instance size */
        igRendererOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRendererOrderedList_callbackList /* callback list */
    );
}

void igRendererOrderedList_GetMetaObjectFunction(void) {
    igRendererOrderedList_GetMetaObject();
}


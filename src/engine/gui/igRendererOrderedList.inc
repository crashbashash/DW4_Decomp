igMetaObject *g_igRendererOrderedList_metaObject;

igRendererOrderedList *igRendererOrderedList_CreateInstance(int allocator) {
    igRendererOrderedList_EnsureRegistered();
    return (igRendererOrderedList *)igMetaObject_CreateInstance((int)g_igRendererOrderedList_metaObject, allocator);
}

igMetaObject *igRendererOrderedList_GetOrCreateMetaObject(void) {
    if (g_igRendererOrderedList_metaObject == 0) {
        g_igRendererOrderedList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &g_igRendererOrderedList_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igRendererOrderedList_vtable[0];
    FUN_0044c5e0((int **)&obj, 0);
    return r;
}

int **FUN_0044c5e0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541dd0[0];
        if (arg0 != 0) {
            *arg0 = &g_igDependencyOrderedList_vtable[0];
            igSmartPointer_igStringRefList_Destruct((int **)((char *)arg0 + 0x14), -1);
            igSmartPointer_igPointerList_Destruct((int **)((char *)arg0 + 0x10), -1);
            igSmartPointer_igDependencyList_Destruct((int **)((char *)arg0 + 0xC), -1);
            igSmartPointer_igObjectList_Destruct((int **)((char *)arg0 + 8), -1);
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

void igRendererOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRendererOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igRendererOrderedList_GetMetaObject,
        "igRendererOrderedList",
        0x1C, /* instance size */
        igRendererOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRendererOrderedList_callbackList /* callback list */
    );
}

void thunk_igRendererOrderedList_GetMetaObject(void) {
    igRendererOrderedList_GetMetaObject();
}


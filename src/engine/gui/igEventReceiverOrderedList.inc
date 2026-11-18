igMetaObject *g_igEventReceiverOrderedList_metaObject;

igMetaObject *igEventReceiverOrderedList_GetOrCreateMetaObject(void) {
    if (g_igEventReceiverOrderedList_metaObject == 0) {
        g_igEventReceiverOrderedList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEventReceiverOrderedList_metaObject;
}

igMetaObject *igEventReceiverOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiverOrderedList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiverOrderedList_EnsureRegistered();
    return g_igEventReceiverOrderedList_metaObject;
}

int igEventReceiverOrderedList_GetVTable(void) {
    union U_4510f0 u;
    int t;
    igObject_InitHeader((igObject *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&g_igEventReceiverOrderedList_vtable[0];
    t = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igEventReceiverOrderedList_vtable[0];
    FUN_00451160((int **)u.b, 0);
    return t;
}

int **FUN_00451160(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541970[0];
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

void igEventReceiverOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiverOrderedList_Register);
}

static igMetaObjectCallback g_igEventReceiverOrderedList_callbackList[] = { igEventReceiver_EnsureRegistered, 0 };

CallbackArray *igEventReceiverOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEventReceiverOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        igEventReceiverOrderedList_GetMetaObjectFunction,
        "igEventReceiverOrderedList",
        0x1C, /* instance size */
        igEventReceiverOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventReceiverOrderedList_callbackList /* callback list */
    );
}

void igEventReceiverOrderedList_GetMetaObjectFunction(void) {
    igEventReceiverOrderedList_GetMetaObject();
}


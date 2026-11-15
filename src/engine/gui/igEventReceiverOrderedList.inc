igMetaObject *g_igEventReceiverOrderedList_metaObject;

igMetaObject *FUN_00451050(void) {
    if (g_igEventReceiverOrderedList_metaObject == 0) {
        g_igEventReceiverOrderedList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&DAT_00541910[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00541910[0];
    FUN_00451160((int **)u.b, 0);
    return t;
}

int **FUN_00451160(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541970[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
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

void igEventReceiverOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiverOrderedList_Register);
}

static igMetaObjectCallback g_igEventReceiverOrderedList_callbackList[] = { igEventReceiver_EnsureRegistered, 0 };

void igEventReceiverOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEventReceiverOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igEventReceiverOrderedList_GetMetaObject,
        "igEventReceiverOrderedList",
        0x1C, /* instance size */
        igEventReceiverOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventReceiverOrderedList_callbackList /* callback list */
    );
}

void thunk_igEventReceiverOrderedList_GetMetaObject(void) {
    igEventReceiverOrderedList_GetMetaObject();
}


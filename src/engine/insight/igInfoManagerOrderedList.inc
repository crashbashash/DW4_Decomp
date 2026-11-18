igMetaObject *g_igInfoManagerOrderedList_metaObject;

igMetaObject *igInfoManagerOrderedList_GetOrCreateMetaObject(void) {
    if (g_igInfoManagerOrderedList_metaObject == 0) {
        g_igInfoManagerOrderedList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInfoManagerOrderedList_metaObject;
}

igMetaObject *igInfoManagerOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerOrderedList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInfoManagerOrderedList_EnsureRegistered();
    return g_igInfoManagerOrderedList_metaObject;
}

int igInfoManagerOrderedList_GetVTable(void) {
    Obj_233520 o;
    int r;

    igObject_InitHeader((igObject *)&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[4] = 0;
    o.vt = &g_igInfoManagerOrderedList_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igInfoManagerOrderedList_vtable[0];
    FUN_00233610((int **)&o, 0);
    return r;
}

igSmartPointer<igObject> *igSmartPointer_igDependencyList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int **FUN_00233610(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052cbc0[0];
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

void igInfoManagerOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInfoManagerOrderedList_Register);
}

static igMetaObjectCallback g_igInfoManagerOrderedList_callbackList[] = { igInfoManager_EnsureRegistered, 0 };

CallbackArray *igInfoManagerOrderedList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInfoManagerOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        igInfoManagerOrderedList_GetMetaObjectFunction,
        "igInfoManagerOrderedList",
        0x1C, /* instance size */
        igInfoManagerOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerOrderedList_callbackList /* callback list */
    );
}

void igInfoManagerOrderedList_GetMetaObjectFunction(void) {
    igInfoManagerOrderedList_GetMetaObject();
}

int FUN_00233740(void) {
    return (int)g_igDependencyOrderedList_metaObject;
}


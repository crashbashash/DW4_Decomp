igMetaObject *g_igBoolMetaField_metaObject;
void *g_igBoolMetaField_descriptor;

void **igBoolMetaField_Create(int pool) {
    void **instance;

    if (g_objectSystem->active != 0) {
        igBoolMetaField_EnsureRegistered();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igBoolMetaField_metaObject, (igMemoryPoolView *)pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igBoolMetaField_Construct((int **)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->InitDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return instance;
}

int igBoolMetaField_Clone(int source, int pool) {
    int copy;
    if (g_objectSystem->active) {
        igBoolMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, pool);
    }
    copy = (int)igObject_AllocateRawStorageDefault(0x34, 0);
    if (copy) copy = ((int)igBoolMetaField_CopyConstruct((int **)copy, source));
    return copy;
}

igMetaObject *igBoolMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolMetaField_EnsureRegistered();
    return g_igBoolMetaField_metaObject;
}

int igBoolMetaField_GetVTable(void) {
    igBoolMetaField prototype;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int refCount;

    igBoolMetaField_Init((int **)&prototype);
    vtable = *(int *)((char *)&prototype + g_objectSystem->vtableProbeOffset);
    prototype._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&prototype._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            refCount = text[-1] - 1;
            text[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igBoolMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoolMetaField_Register);
}

static igMetaObjectCallback g_igBoolMetaField_callbackList[] = { igBoolMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igBoolMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igBoolMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igBoolMetaField_GetMetaObjectFunction,
        "igBoolMetaField",
        0x34,
        igBoolMetaField_GetVTable,
        0,
        0,
        g_igBoolMetaField_callbackList
    );
}

void igBoolMetaField_GetMetaObjectFunction(void) {
    igBoolMetaField_GetMetaObject();
}


void igBoolMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igBoolMetaField_descriptor == 0) {
        g_igBoolMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igBoolMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igBoolMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igBoolMetaField_descriptor;
                held->_refCount = held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igBoolMetaField_descriptor) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igBoolMetaField_descriptor);
        }
    }
}

int igBoolMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igBoolMetaField_descriptor) == 0) {
        igBoolMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igBoolMetaField_descriptor);
}


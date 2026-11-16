igMetaObject *g_igUnsignedShortMetaField_metaObject;
void *g_igUnsignedShortMetaField_descriptor;

void **igUnsignedShortMetaField_Create(int allocator) {
    void **field;

    if (g_objectSystem->active != 0) {
        igUnsignedShortMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortMetaField_metaObject, (igMemoryPoolView *)allocator)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)allocator)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedShortMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return field;
}

int igUnsignedShortMetaField_Clone(int source, int flags) {
    int copy;

    if (g_objectSystem->active != 0) {
        igUnsignedShortMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, flags);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (copy != 0) {
        copy = ((int)igUnsignedShortMetaField_CopyConstruct((int **)copy, source));
    }
    return copy;
}

igMetaObject *igUnsignedShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortMetaField_EnsureRegistered();
    return g_igUnsignedShortMetaField_metaObject;
}

int igUnsignedShortMetaField_GetVTable(void) {
    igUnsignedShortMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igUnsignedShortMetaField_Init((int **)&o);
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (StringTokenHeader *)hdr);
            }
        }
    }
    return r;
}

void igUnsignedShortMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedShortMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedShortMetaField_callbackList[] = { igUnsignedShortMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedShortMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedShortMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igUnsignedShortMetaField_GetMetaObjectFunction,
        "igUnsignedShortMetaField",
        0x34,
        igUnsignedShortMetaField_GetVTable,
        0,
        0,
        g_igUnsignedShortMetaField_callbackList
    );
}

void igUnsignedShortMetaField_GetMetaObjectFunction(void) {
    igUnsignedShortMetaField_GetMetaObject();
}


void igUnsignedShortMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igUnsignedShortMetaField_descriptor == 0) {
        g_igUnsignedShortMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igUnsignedShortMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igUnsignedShortMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igUnsignedShortMetaField_descriptor)->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedShortMetaField_descriptor);
        }
    }
}

int igUnsignedShortMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igUnsignedShortMetaField_descriptor) == 0) {
        igUnsignedShortMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igUnsignedShortMetaField_descriptor);
}


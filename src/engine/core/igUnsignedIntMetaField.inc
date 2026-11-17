igMetaObject *g_igUnsignedIntMetaField_metaObject;
void *g_igUnsignedIntMetaField_descriptor;

igMetaField *igUnsignedIntMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)((int)g_igUnsignedIntMetaField_metaObject), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedIntMetaField_Construct((igMetaField *)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

int igUnsignedIntMetaField_Clone(int source, int pool) {
    int copy;

    if (g_objectSystem->active != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, pool);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (copy != 0) {
        copy = ((int)igUnsignedIntMetaField_CopyConstruct((int **)copy, source));
    }
    return copy;
}

igMetaObject *igUnsignedIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntMetaField_EnsureRegistered();
    return g_igUnsignedIntMetaField_metaObject;
}

int igUnsignedIntMetaField_GetVTable(void) {
    igUnsignedIntMetaField field;
    int *header;
    int vtable;
    int refCount;
    void *chars;

    igUnsignedIntMetaField_Init((igMetaField *)&field);
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    if ((void **)&field._fieldName != 0) {
        chars = (void *)((void *)field._fieldName);
        if (chars != 0) {
            header = (int *)((char *)chars - 8);
            refCount = *(int *)((char *)(chars) - 4) - 1;
            *(int *)((char *)(chars) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igUnsignedIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedIntMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedIntMetaField_callbackList[] = { igUnsignedIntMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedIntMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedIntMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igUnsignedIntMetaField_GetMetaObjectFunction,
        "igUnsignedIntMetaField",
        0x34,
        igUnsignedIntMetaField_GetVTable,
        0,
        0,
        g_igUnsignedIntMetaField_callbackList
    );
}

void igUnsignedIntMetaField_GetMetaObjectFunction(void) {
    igUnsignedIntMetaField_GetMetaObject();
}


void igUnsignedIntMetaField_CreateDefaultDescriptor(void) {
    void *created;

    if (g_igUnsignedIntMetaField_descriptor == 0) {
        g_igUnsignedIntMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedIntMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        created = (void *)(g_igUnsignedIntMetaField_descriptor);
        if (created != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)created);
            {
                igMetaField *held = (igMetaField *)g_igUnsignedIntMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long) (int) held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igUnsignedIntMetaField_descriptor) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedIntMetaField_descriptor);
        }
    }
}

int igUnsignedIntMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igUnsignedIntMetaField_descriptor) == 0) {
        igUnsignedIntMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igUnsignedIntMetaField_descriptor);
}


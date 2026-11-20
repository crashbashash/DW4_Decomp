igMetaObject *g_igUnsignedLongMetaField_metaObject;
void *g_igUnsignedLongMetaField_descriptor;

igMetaField *igUnsignedLongMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        igUnsignedLongMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongMetaField_metaObject, pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedLongMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

int igUnsignedLongMetaField_Clone(int source, int flags) {
    int copy;

    if (g_objectSystem->active != 0) {
        igUnsignedLongMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, flags);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x34, 0));
    if (copy != 0) {
        copy = ((int)igUnsignedLongMetaField_CopyConstruct((int **)copy, source));
    }
    return copy;
}

igMetaObject *igUnsignedLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedLongMetaField_EnsureRegistered();
    return g_igUnsignedLongMetaField_metaObject;
}

int igUnsignedLongMetaField_GetVTable(void) {
    igUnsignedLongMetaField field;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int count;

    igUnsignedLongMetaField_Init((int **)&field);
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&field._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igUnsignedLongMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedLongMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedLongMetaField_callbackList[] = { igUnsignedLongMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedLongMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedLongMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igUnsignedLongMetaField_GetMetaObjectFunction,
        "igUnsignedLongMetaField",
        0x34,
        igUnsignedLongMetaField_GetVTable,
        0,
        0,
        g_igUnsignedLongMetaField_callbackList
    );
}

void igUnsignedLongMetaField_GetMetaObjectFunction(void) {
    igUnsignedLongMetaField_GetMetaObject();
}


void igUnsignedLongMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igUnsignedLongMetaField_descriptor == 0) {
        g_igUnsignedLongMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igUnsignedLongMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igUnsignedLongMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igUnsignedLongMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igUnsignedLongMetaField_descriptor)->validate();
        }
    }
}

int igUnsignedLongMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igUnsignedLongMetaField_descriptor) == 0) {
        igUnsignedLongMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igUnsignedLongMetaField_descriptor);
}


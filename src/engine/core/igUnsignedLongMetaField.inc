void **igUnsignedLongMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igUnsignedLongMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongMetaField_metaObject[0], (igMemoryPoolView *)allocator)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)allocator)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedLongMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->initDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return field;
}

int igUnsignedLongMetaField_Clone(int source, int flags) {
    int copy;

    if (*g_objectSystem[0] != 0) {
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
    igMetaObject *g = g_igUnsignedLongMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedLongMetaField_EnsureRegistered();
    return g_igUnsignedLongMetaField_metaObject[0];
}

int igUnsignedLongMetaField_GetVTable(void) {
    igUnsignedLongMetaField field;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int count;

    igUnsignedLongMetaField_Init((int **)&field);
    vtable = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    field._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&field._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igUnsignedLongMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedLongMetaField_Register);
}

void igUnsignedLongMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedLongMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igUnsignedLongMetaField_GetMetaObjectFunction,
        igUnsignedLongMetaField_className,
        0x34,
        igUnsignedLongMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igUnsignedLongMetaField_callbackList
    );
}

void igUnsignedLongMetaField_GetMetaObjectFunction(void) {
    igUnsignedLongMetaField_GetMetaObject();
}

void igUnsignedLongMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igUnsignedLongMetaField_descriptor[0] == 0) {
        g_igUnsignedLongMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igUnsignedLongMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igUnsignedLongMetaField_descriptor[0];
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igUnsignedLongMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedLongMetaField_descriptor[0]);
        }
    }
}

int igUnsignedLongMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igUnsignedLongMetaField_descriptor)[0] == 0) {
        igUnsignedLongMetaField_EnsureRegistered();
    }
    return ((int *)g_igUnsignedLongMetaField_descriptor)[0];
}


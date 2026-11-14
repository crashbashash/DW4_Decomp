/* Same factory shape for an igIntMetaField (52-byte instance). */
void **igIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igIntMetaField_metaObject)[0]), (igMemoryPoolView *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)allocator));
        if (field != 0) {
            field = ((void **)igIntMetaField_Construct((igMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->initDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return field;
}

void *igIntMetaField_Clone(void *self, void *src) {
    void *o;
    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_AllocateRawStorageDefault(0x34, 0);
    if (o != 0) {
        o = ((void *)igIntMetaField_CopyConstruct((int **)o, (int)self));
    }
    return o;
}

igMetaObject *igIntMetaField_GetOrCreateMetaObject(void) {
    if (g_igIntMetaField_metaObject[0] == 0) {
        g_igIntMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igIntMetaField_metaObject[0];
}

igMetaObject *igIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntMetaField_EnsureRegistered();
    return g_igIntMetaField_metaObject[0];
}

int igIntMetaField_GetVTable(void) {
    igIntMetaField field;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int count;

    FUN_002ea420((char *)&field);
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

void igIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntMetaField_Register);
}

void igIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igIntMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igIntMetaField_GetMetaObjectFunction,
        igIntMetaField_className,
        0x34,
        igIntMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igIntMetaField_callbackList
    );
}

void igIntMetaField_GetMetaObjectFunction(void) {
    igIntMetaField_GetMetaObject();
}

void igIntMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igIntMetaField_descriptor[0] == 0) {
        g_igIntMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igIntMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igIntMetaField_descriptor[0];
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igIntMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igIntMetaField_descriptor[0]);
        }
    }
}

int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor[0] == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return (int)g_igIntMetaField_descriptor[0];
}


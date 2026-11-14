void **igRawRefMetaField_Create(int pool) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefMetaField_metaObject[0], (igMemoryPoolView *)pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, (igMemoryPoolView *)pool)));
        if (field != 0) {
            field = (void **)(((void **)igRawRefMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->initDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return field;
}

int igRawRefMetaField_Clone(int source, int copyMode) {
    int clone;

    if (*g_objectSystem[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    clone = ((int)igObject_AllocateRawStorageDefault(0x38, 0));
    if (clone != 0) {
        clone = ((int)igRawRefMetaField_CopyConstruct((int **)clone, source));
    }
    return clone;
}

igMetaObject *igRawRefMetaField_GetOrCreateMetaObject(void) {
    if (g_igRawRefMetaField_metaObject[0] == 0) {
        g_igRawRefMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRawRefMetaField_metaObject[0];
}

igMetaObject *igRawRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefMetaField_EnsureRegistered();
    return g_igRawRefMetaField_metaObject[0];
}

int igRawRefMetaField_GetVTable(void) {
    igRawRefMetaField o;
    int r;
    int *header;
    int refs;
    void *name;

    igRawRefMetaField_Init((int **)&o);
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        name = (char *)o._fieldName;
        if (name != 0) {
            header = (int *)((char *)name - 8);
            refs = *(int *)((char *)(name) - 4) - 1;
            *(int *)((char *)(name) - 4) = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return r;
}

void igRawRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRawRefMetaField_Register);
}

void igRawRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igRawRefMetaField_metaObject,
        (igMetaObjectRegisterFunction)igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        igRawRefMetaField_GetMetaObjectFunction,
        igRawRefMetaField_className,
        0x38,
        igRawRefMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igRawRefMetaField_callbackList
    );
}

void igRawRefMetaField_GetMetaObjectFunction(void) {
    igRawRefMetaField_GetMetaObject();
}

void igRawRefMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igRawRefMetaField_descriptor[0] == 0) {
        g_igRawRefMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igRawRefMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                void *held = (void *)g_igRawRefMetaField_descriptor[0];
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igRawRefMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRawRefMetaField_descriptor[0]);
        }
    }
}

int igRawRefMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igRawRefMetaField_descriptor)[0] == 0) {
        igRawRefMetaField_EnsureRegistered();
    }
    return ((int *)g_igRawRefMetaField_descriptor)[0];
}


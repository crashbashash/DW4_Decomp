igMetaObject *g_igObjectRefMetaField_metaObject;
igObjectRefMetaField *g_igObjectRefMetaField_descriptor;
igMetaField *g_igObjectRefMetaField_metaObjectMetaField;
igMetaField *g_igObjectRefMetaField_refCountedMetaField;
igMetaField *g_igObjectRefMetaField_poolNameMetaField;

/* Same factory shape for an igObjectRefMetaField (68-byte instance). */
void **igObjectRefMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem != 0) {
        igObjectRefMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)g_igObjectRefMetaField_metaObject), (igMemoryPoolView *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x44, 0, (igMemoryPoolView *)allocator));
        if (field != 0) {
            field = ((void **)igObjectRefMetaField_Construct((igObjectRefMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return field;
}

int igObjectRefMetaField_Clone(int source, int flags) {
    int copy;

    if (*g_objectSystem != 0) {
        igObjectRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, flags);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x44, 0));
    if (copy != 0) {
        copy = ((int)igObjectRefMetaField_CopyConstruct((igObjectRefMetaField *)copy, (void *)source));
    }
    return copy;
}

igMetaObject *igObjectRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectRefMetaField_EnsureRegistered();
    return g_igObjectRefMetaField_metaObject;
}

int igObjectRefMetaField_GetVTable(void) {
    igObjectRefMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    r = *(int *)((char *)&o + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    o._vtable = (int)&g_igObjectRefMetaField_vtable[0];
    if (&o._poolName != 0) {
        p = (char *)o._poolName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void igObjectRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectRefMetaField_Register);
}

static igMetaObjectCallback g_igObjectRefMetaField_callbackList[] = { igMetaObject_EnsureRegistered, igObjectRefMetaField_CreateDefaultDescriptor, 0 };

void igObjectRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        &g_igObjectRefMetaField_metaObject,
        (igMetaObjectRegisterFunction)igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        igObjectRefMetaField_GetMetaObjectFunction,
        "igObjectRefMetaField",
        0x44,
        igObjectRefMetaField_GetVTable,
        igObjectRefMetaField_InitFields,
        0,
        g_igObjectRefMetaField_callbackList
    );
}

void igObjectRefMetaField_GetMetaObjectFunction(void) {
    igObjectRefMetaField_GetMetaObject();
}

static FieldFactory g_igObjectRefMetaField_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igObjectRefMetaField_fieldTable[] = {
    "_metaObject",
    "_refCounted",
    "_poolName",
};
static igMetaField **g_igObjectRefMetaField_fieldDescriptors[] = {
    &g_igObjectRefMetaField_metaObjectMetaField,
    &g_igObjectRefMetaField_refCountedMetaField,
    &g_igObjectRefMetaField_poolNameMetaField,
};
static int g_igObjectRefMetaField_fieldOffsets[] = {
    56,
    60,
    64,
};

void igObjectRefMetaField_InitFields(void) {
    int base;
    void *metaObjectField;
    void *meta;

    meta = (void *)g_igObjectRefMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igObjectRefMetaField_ctorTable, 3);
    metaObjectField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)metaObjectField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)metaObjectField)->_refCounted = 0;
    ((igMetaField *)metaObjectField)->_deepCopyMethod = 1;
    ((igMetaField *)metaObjectField)->_shallowCopyMethod = 1;
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1))), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igObjectRefMetaField_fieldTable, g_igObjectRefMetaField_fieldDescriptors, g_igObjectRefMetaField_fieldOffsets, base);
}


void igObjectRefMetaField_CreateDefaultDescriptor(void) {
    igObjectRefMetaField *descriptor;
    igObjectRefMetaField *held;
    int len;

    if (g_igObjectRefMetaField_descriptor == 0) {
        g_igObjectRefMetaField_descriptor = ((igObjectRefMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igObjectRefMetaField_metaObject, (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igObjectRefMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igObjectRefMetaField_descriptor;
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            len = igMetaField_GetMetaFieldList()->_count;
            g_igObjectRefMetaField_descriptor->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igObjectRefMetaField_descriptor);
        }
    }
}

int igObjectRefMetaField_GetDefaultDescriptor(void) {
    if (g_igObjectRefMetaField_descriptor == 0) {
        igObjectRefMetaField_EnsureRegistered();
    }
    return (int)g_igObjectRefMetaField_descriptor;
}


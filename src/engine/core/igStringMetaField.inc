igMetaObject *g_igStringMetaField_metaObject;
int *g_igStringMetaField_descriptor;
int g_igStringMetaField_shallowCopyMethodCell;
int g_igStringMetaField_destructCell;
igMetaField *g_igStringMetaField_refCountedMetaField;

/* Factory for an igStringMetaField (60-byte instance). Once the object system is live, ensure the
 * class is registered and let its MetaObject create the instance with the given allocator. Before
 * that, allocate by hand, construct in place (second argument 1 is the flag retail passes) and run
 * the post-construction hooks, vfunc_09 then vfunc_07(0). */
void **igStringMetaField_Create(int allocator) {
    void **field;

    if (g_objectSystem->active != 0) {
        igStringMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)g_igStringMetaField_metaObject), (igMemoryPoolView *)allocator));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x3C, 0, (igMemoryPoolView *)allocator));
        if (field != 0) {
            field = ((void **)igStringMetaField_Construct((igStringMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return field;
}

int igStringMetaField_Clone(int source, int pool) {
    int copy;
    if (g_objectSystem->active != 0) {
        igStringMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, pool);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x3C, 0));
    if (copy != 0) {
        copy = ((int)igStringMetaField_CopyConstruct((void *)copy, (void *)source));
    }
    return copy;
}

igMetaObject *igStringMetaField_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igStringMetaField_metaObject != 0) {
        ready = (g_igStringMetaField_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igStringMetaField_EnsureRegistered();
done:
    return g_igStringMetaField_metaObject;
}

int igStringMetaField_GetVTable(void) {
    igStringMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igStringMetaField_Init((igStringMetaField *)&o);
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

void igStringMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringMetaField_Register);
}

static igMetaObjectCallback g_igStringMetaField_callbackList[] = { igStringMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igStringMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igStringMetaField_metaObject,
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        igStringMetaField_GetMetaObjectFunction,
        "igStringMetaField",
        0x3C,
        igStringMetaField_GetVTable,
        igStringMetaField_InitFields,
        0,
        g_igStringMetaField_callbackList
    );
}

void igStringMetaField_GetMetaObjectFunction(void) {
    igStringMetaField_GetMetaObject();
}

igMetaObject *g_igRefMetaField_metaObject;
void *g_igRefMetaField_descriptor;
igMetaField *g_igRefMetaField_constructMetaField;
igMetaField *g_igRefMetaField_destructMetaField;

igMetaObject *igRefMetaField_GetPublishedMetaObject(void) {
    return g_igRefMetaField_metaObject;
}

static FieldFactory g_igStringMetaField_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igStringMetaField_fieldTable[] = {
    "_refCounted",
};
static igMetaField **g_igStringMetaField_fieldDescriptors[] = {
    &g_igStringMetaField_refCountedMetaField,
};
static int g_igStringMetaField_fieldOffsets[] = {
    56,
};


void igStringMetaField_InitFields(void) {
    int first;
    int index;
    void **found;
    igMetaObject *meta;
    igMetaField *shallowCopyField;
    igMetaField *destructField;

    meta = (igMetaObject *)((void *)g_igStringMetaField_metaObject);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStringMetaField_ctorTable, 1);
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, (const char *)&text_shallowCopyMethod[0])));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    shallowCopyField = (igMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    igCharMetaField_SetDefaultValue((void **)shallowCopyField, 2);
    shallowCopyField->_externalEnumStorage = (int)(&g_igStringMetaField_shallowCopyMethodCell);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)shallowCopyField);
    shallowCopyField->_refCount = shallowCopyField->_refCount - 1;
    if (((unsigned long long)(long long)shallowCopyField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(shallowCopyField);
    }
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, (const char *)&text_destruct[0])));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    destructField = (igMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    igBoolMetaField_SetDefaultValue((void **)destructField, 1);
    destructField->_externalEnumStorage = (int)(&g_igStringMetaField_destructCell);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)destructField);
    destructField->_refCount = destructField->_refCount - 1;
    if (((unsigned long long)(long long)destructField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(destructField);
    }
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first))), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igStringMetaField_fieldTable, g_igStringMetaField_fieldDescriptors, g_igStringMetaField_fieldOffsets, first);
}


void igStringMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *o;

    if (g_igStringMetaField_descriptor == 0) {
        g_igStringMetaField_descriptor = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igStringMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        s0 = g_igStringMetaField_descriptor;
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            o = g_igStringMetaField_descriptor;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
            *(short *)((char *)g_igStringMetaField_descriptor + 18) = *(int *)((char *)((void *)igMetaField_GetMetaFieldList()) + 12) - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igStringMetaField_descriptor);
        }
    }
}

int igStringMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igStringMetaField_descriptor) == 0) {
        igStringMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igStringMetaField_descriptor);
}


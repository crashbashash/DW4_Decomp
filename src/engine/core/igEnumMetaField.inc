igMetaObject *g_igEnumMetaField_metaObject;
int *g_igEnumMetaField_descriptor;
igMetaField *g_igEnumMetaField_getMetaEnumFunctionMetaField;

void **igEnumMetaField_Create(int pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        igEnumMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igEnumMetaField_metaObject, (igMemoryPoolView *)pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, (igMemoryPoolView *)pool)));
        if (field != 0) {
            field = (void **)(((void **)igEnumMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return field;
}

int igEnumMetaField_Clone(int source, int pool) {
    int copy;

    if (g_objectSystem->active != 0) {
        igEnumMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, pool);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x38, 0));
    if (copy != 0) {
        copy = ((int)igEnumMetaField_CopyConstruct((int **)copy, source));
    }
    return copy;
}

igMetaObject *igEnumMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumMetaField_EnsureRegistered();
    return g_igEnumMetaField_metaObject;
}

int igEnumMetaField_GetVTable(void) {
    igEnumMetaField o;
    int *header;
    int vtable;
    int refCount;
    void *chars;

    igEnumMetaField_Init((int **)&o);
    vtable = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        chars = (void *)((char *)o._fieldName);
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

void igEnumMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnumMetaField_Register);
}

static igMetaObjectCallback g_igEnumMetaField_callbackList[] = { igEnumMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igEnumMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igEnumMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igEnumMetaField_GetMetaObjectFunction,
        "igEnumMetaField",
        0x38,
        igEnumMetaField_GetVTable,
        igEnumMetaField_InitFields,
        0,
        g_igEnumMetaField_callbackList
    );
}

void igEnumMetaField_GetMetaObjectFunction(void) {
    igEnumMetaField_GetMetaObject();
}

static FieldFactory g_igEnumMetaField_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igEnumMetaField_fieldTable[] = {
    "_getMetaEnumFunction",
};
static igMetaField **g_igEnumMetaField_fieldDescriptors[] = {
    &g_igEnumMetaField_getMetaEnumFunctionMetaField,
};
static int g_igEnumMetaField_fieldOffsets[] = {
    52,
};

void igEnumMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igEnumMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igEnumMetaField_ctorTable, 1);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igEnumMetaField_fieldTable, g_igEnumMetaField_fieldDescriptors, g_igEnumMetaField_fieldOffsets, first);
}


void igEnumMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *o;
    int count;

    if (g_igEnumMetaField_descriptor == 0) {
        g_igEnumMetaField_descriptor = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igEnumMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        s0 = g_igEnumMetaField_descriptor;
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            o = g_igEnumMetaField_descriptor;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            count = *(int *)((char *)((void *)igMetaField_GetMetaFieldList()) + 12); /* Read as a whole word first; a direct `short = int - 1` store would be narrowed to an lh. */
            *(short *)((char *)g_igEnumMetaField_descriptor + 18) = count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igEnumMetaField_descriptor);
        }
    }
}

int igEnumMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igEnumMetaField_descriptor) == 0) {
        igEnumMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igEnumMetaField_descriptor);
}


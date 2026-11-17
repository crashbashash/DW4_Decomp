igMetaObject *g_igUnsignedLongArrayMetaField_metaObject;
igUnsignedLongArrayMetaField *g_igUnsignedLongArrayMetaField_descriptor;
igMetaField *g_igUnsignedLongArrayMetaField_numMetaField;

igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedLongArrayMetaField_EnsureRegistered();
    return g_igUnsignedLongArrayMetaField_metaObject;
}

int igUnsignedLongArrayMetaField_GetVTable(void) {
    igUnsignedLongArrayMetaField obj;
    char *chars;
    int *header;
    int refCount;
    int vtable;
    igUnsignedLongMetaField_Init((int **)&obj);
    obj._vtable = (int)&g_igUnsignedLongArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        chars = (char *)obj._fieldName;
        if (chars != 0) {
            header = (int *)(chars - 8);
            refCount = *(int *)(chars - 4) - 1;
            *(int *)(chars - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igUnsignedLongArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedLongArrayMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedLongArrayMetaField_callbackList[] = { igUnsignedLongArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedLongArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedLongArrayMetaField_metaObject,
        igUnsignedLongMetaField_Register,
        igUnsignedLongMetaField_GetPublishedMetaObject,
        igUnsignedLongArrayMetaField_GetMetaObjectFunction,
        "igUnsignedLongArrayMetaField",
        0x38,
        igUnsignedLongArrayMetaField_GetVTable,
        igUnsignedLongArrayMetaField_InitFields,
        0,
        g_igUnsignedLongArrayMetaField_callbackList
    );
}

void igUnsignedLongArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedLongArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedLongMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedLongMetaField_metaObject;
}

static FieldFactory g_igUnsignedLongArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igUnsignedLongArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igUnsignedLongArrayMetaField_fieldDescriptors[] = {
    &g_igUnsignedLongArrayMetaField_numMetaField,
};
static int g_igUnsignedLongArrayMetaField_fieldOffsets[] = {
    52,
};

void igUnsignedLongArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igUnsignedLongArrayMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igUnsignedLongArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, first), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igUnsignedLongArrayMetaField_fieldTable, g_igUnsignedLongArrayMetaField_fieldDescriptors, g_igUnsignedLongArrayMetaField_fieldOffsets, first);
}


void igUnsignedLongArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedLongArrayMetaField *created;
    igUnsignedLongArrayMetaField *p;

    if (g_igUnsignedLongArrayMetaField_descriptor == 0) {
        g_igUnsignedLongArrayMetaField_descriptor = ((igUnsignedLongArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        created = g_igUnsignedLongArrayMetaField_descriptor;
        if (created != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)created);
            p = g_igUnsignedLongArrayMetaField_descriptor;
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedLongArrayMetaField_descriptor->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedLongArrayMetaField_descriptor);
        }
    }
}


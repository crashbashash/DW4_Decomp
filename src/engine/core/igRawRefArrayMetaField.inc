igMetaObject *g_igRawRefArrayMetaField_metaObject;
igRawRefArrayMetaField *g_igRawRefArrayMetaField_descriptor;
igMetaField *g_igRawRefArrayMetaField_numMetaField;

igMetaObject *igRawRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefArrayMetaField_EnsureRegistered();
    return g_igRawRefArrayMetaField_metaObject;
}

int igRawRefArrayMetaField_GetVTable(void) {
    igRawRefArrayMetaField f;
    int result;
    int *header;
    int refs;

    igRawRefMetaField_Init((int **)&f);
    f._vtable = (int)&g_igRawRefArrayMetaField_vtable[0];
    result = *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            header = ((int *)f._fieldName) - 2;
            refs = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return result;
}

void igRawRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRawRefArrayMetaField_Register);
}

static igMetaObjectCallback g_igRawRefArrayMetaField_callbackList[] = { igRawRefArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igRawRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igRawRefArrayMetaField_metaObject,
        igRawRefMetaField_Register,
        igRawRefMetaField_GetPublishedMetaObject,
        igRawRefArrayMetaField_GetMetaObjectFunction,
        "igRawRefArrayMetaField",
        0x3C,
        igRawRefArrayMetaField_GetVTable,
        igRawRefArrayMetaField_InitFields,
        0,
        g_igRawRefArrayMetaField_callbackList
    );
}

void igRawRefArrayMetaField_GetMetaObjectFunction(void) {
    igRawRefArrayMetaField_GetMetaObject();
}

igMetaObject *igRawRefMetaField_GetPublishedMetaObject(void) {
    return g_igRawRefMetaField_metaObject;
}

static FieldFactory g_igRawRefArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igRawRefArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igRawRefArrayMetaField_fieldDescriptors[] = {
    &g_igRawRefArrayMetaField_numMetaField,
};
static int g_igRawRefArrayMetaField_fieldOffsets[] = {
    56,
};

void igRawRefArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igRawRefArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igRawRefArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igRawRefArrayMetaField_fieldTable, g_igRawRefArrayMetaField_fieldDescriptors, g_igRawRefArrayMetaField_fieldOffsets, base);
}


void igRawRefArrayMetaField_CreateDefaultDescriptor(void) {
    igRawRefArrayMetaField *descriptor;
    igRawRefArrayMetaField *p;

    if (g_igRawRefArrayMetaField_descriptor == 0) {
        g_igRawRefArrayMetaField_descriptor = ((igRawRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igRawRefArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igRawRefArrayMetaField_descriptor;
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igRawRefArrayMetaField_descriptor->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRawRefArrayMetaField_descriptor);
        }
    }
}


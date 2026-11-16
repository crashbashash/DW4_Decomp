igMetaObject *g_igShortArrayMetaField_metaObject;
igShortArrayMetaField *g_igShortArrayMetaField_descriptor;
igMetaField *g_igShortArrayMetaField_numMetaField;

void igShortArrayMetaField_Create(int pool) {
    igShortArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance(g_igShortArrayMetaField_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortArrayMetaField_EnsureRegistered();
    return g_igShortArrayMetaField_metaObject;
}

int igShortArrayMetaField_GetVTable(void) {
    igShortArrayMetaField field;
    int vtable;
    char *ps;
    int *chars;
    int *header;
    int refCount;

    igShortMetaField_Init((int **)&field);
    field._vtable = (int)&g_igShortArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    ps = (char *)&field._fieldName;
    if (ps != 0) {
        chars = *(int **)ps;
        if (chars != 0) {
            header = chars - 2;
            refCount = chars[-1] - 1;
            chars[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igShortArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShortArrayMetaField_Register);
}

static igMetaObjectCallback g_igShortArrayMetaField_callbackList[] = { igShortArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igShortArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igShortArrayMetaField_metaObject,
        igShortMetaField_Register,
        igShortMetaField_GetPublishedMetaObject,
        igShortArrayMetaField_GetMetaObjectFunction,
        "igShortArrayMetaField",
        0x38,
        igShortArrayMetaField_GetVTable,
        igShortArrayMetaField_InitFields,
        0,
        g_igShortArrayMetaField_callbackList
    );
}

void igShortArrayMetaField_GetMetaObjectFunction(void) {
    igShortArrayMetaField_GetMetaObject();
}

igMetaObject *igShortMetaField_GetPublishedMetaObject(void) {
    return g_igShortMetaField_metaObject;
}

static FieldFactory g_igShortArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igShortArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igShortArrayMetaField_fieldDescriptors[] = {
    &g_igShortArrayMetaField_numMetaField,
};
static int g_igShortArrayMetaField_fieldOffsets[] = {
    52,
};

void igShortArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igShortArrayMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igShortArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igShortArrayMetaField_fieldTable, g_igShortArrayMetaField_fieldDescriptors, g_igShortArrayMetaField_fieldOffsets, first);
}


void igShortArrayMetaField_CreateDefaultDescriptor(void) {
    igShortArrayMetaField *created;
    igShortArrayMetaField *p;

    if (g_igShortArrayMetaField_descriptor == 0) {
        g_igShortArrayMetaField_descriptor = ((igShortArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igShortArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        created = g_igShortArrayMetaField_descriptor;
        if (created != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)created);
            p = g_igShortArrayMetaField_descriptor;
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igShortArrayMetaField_descriptor->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igShortArrayMetaField_descriptor);
        }
    }
}


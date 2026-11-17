igMetaObject *g_igEnumArrayMetaField_metaObject;
int *g_igEnumArrayMetaField_descriptor;
igMetaField *g_igEnumArrayMetaField_numMetaField;
int g_sectionOverrideModeMetaEnum;

igMetaField *igEnumArrayMetaField_Create(igMemoryPoolView *pool) {
    igEnumArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igEnumArrayMetaField_metaObject, pool);
}

igMetaObject *igEnumArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumArrayMetaField_EnsureRegistered();
    return g_igEnumArrayMetaField_metaObject;
}

int igEnumArrayMetaField_GetVTable(void) {
    igEnumArrayMetaField field;
    int result;
    char *fieldName;
    int *name;
    int *header;
    int refs;

    igEnumMetaField_Init((int **)&field);
    field._vtable = (int)&g_igEnumArrayMetaField_vtable[0];
    result = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    fieldName = (char *)&field._fieldName;
    if (fieldName != 0) {
        name = *(int **)fieldName;
        if (name != 0) {
            header = name - 2;
            refs = name[-1] - 1;
            name[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return result;
}

void igEnumArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnumArrayMetaField_Register);
}

static igMetaObjectCallback g_igEnumArrayMetaField_callbackList[] = { igEnumArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igEnumArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igEnumArrayMetaField_metaObject,
        igEnumMetaField_Register,
        igEnumMetaField_GetPublishedMetaObject,
        igEnumArrayMetaField_GetMetaObjectFunction,
        "igEnumArrayMetaField",
        0x3C,
        igEnumArrayMetaField_GetVTable,
        igEnumArrayMetaField_InitFields,
        0,
        g_igEnumArrayMetaField_callbackList
    );
}

void igEnumArrayMetaField_GetMetaObjectFunction(void) {
    igEnumArrayMetaField_GetMetaObject();
}

igMetaObject *igEnumMetaField_GetPublishedMetaObject(void) {
    return g_igEnumMetaField_metaObject;
}

static FieldFactory g_igEnumArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igEnumArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igEnumArrayMetaField_fieldDescriptors[] = {
    &g_igEnumArrayMetaField_numMetaField,
};
static int g_igEnumArrayMetaField_fieldOffsets[] = {
    56,
};

void igEnumArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igEnumArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igEnumArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igEnumArrayMetaField_fieldTable, g_igEnumArrayMetaField_fieldDescriptors, g_igEnumArrayMetaField_fieldOffsets, base);
}


void igEnumArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (g_igEnumArrayMetaField_descriptor == 0) {
        g_igEnumArrayMetaField_descriptor = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igEnumArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        s0 = g_igEnumArrayMetaField_descriptor;
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = g_igEnumArrayMetaField_descriptor;
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)g);
            }
            *(short *)((char *)g_igEnumArrayMetaField_descriptor + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igEnumArrayMetaField_descriptor);
        }
    }
}


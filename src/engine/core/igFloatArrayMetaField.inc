igMetaObject *g_igFloatArrayMetaField_metaObject;
igFloatArrayMetaField *g_igFloatArrayMetaField_descriptor;
igMetaField *g_igFloatArrayMetaField_numMetaField;
int g_igFile_readModeMetaEnum;
int g_igFile_openModeMetaEnum;

igMetaField *igFloatArrayMetaField_Create(igMemoryPoolView *pool) {
    igFloatArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igFloatArrayMetaField_metaObject, pool);
}

igMetaObject *igFloatArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatArrayMetaField_EnsureRegistered();
    return g_igFloatArrayMetaField_metaObject;
}

int igFloatArrayMetaField_GetVTable(void) {
    igFloatArrayMetaField prototype;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int refCount;

    igMetaField_Init((igMetaField *)&prototype);
    prototype._vtable = (int)&g_igFloatArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&prototype + g_objectSystem->vtableProbeOffset);
    prototype._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&prototype._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            refCount = text[-1] - 1;
            text[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igFloatArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFloatArrayMetaField_Register);
}

static igMetaObjectCallback g_igFloatArrayMetaField_callbackList[] = { igFloatArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igFloatArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igFloatArrayMetaField_metaObject,
        igFloatMetaField_Register,
        igFloatMetaField_GetPublishedMetaObject,
        igFloatArrayMetaField_GetMetaObjectFunction,
        "igFloatArrayMetaField",
        0x38,
        igFloatArrayMetaField_GetVTable,
        igFloatArrayMetaField_InitFields,
        0,
        g_igFloatArrayMetaField_callbackList
    );
}

void igFloatArrayMetaField_GetMetaObjectFunction(void) {
    igFloatArrayMetaField_GetMetaObject();
}

igMetaObject *igFloatMetaField_GetPublishedMetaObject(void) {
    return g_igFloatMetaField_metaObject;
}

static FieldFactory g_igFloatArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igFloatArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igFloatArrayMetaField_fieldDescriptors[] = {
    &g_igFloatArrayMetaField_numMetaField,
};
static int g_igFloatArrayMetaField_fieldOffsets[] = {
    52,
};

void igFloatArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igFloatArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igFloatArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igFloatArrayMetaField_fieldTable, g_igFloatArrayMetaField_fieldDescriptors, g_igFloatArrayMetaField_fieldOffsets, base);
}


void igFloatArrayMetaField_CreateDefaultDescriptor(void) {
    igFloatArrayMetaField *descriptor;
    igFloatArrayMetaField *held;
    int n;

    if (g_igFloatArrayMetaField_descriptor == 0) {
        g_igFloatArrayMetaField_descriptor = ((igFloatArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igFloatArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igFloatArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igFloatArrayMetaField_descriptor;
            held->_refCount = (int)((int) (held->_refCount - 1));
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            n = igMetaField_GetMetaFieldList()->_count - 1;
            g_igFloatArrayMetaField_descriptor->_internalIndex = n;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igFloatArrayMetaField_descriptor);
        }
    }
}


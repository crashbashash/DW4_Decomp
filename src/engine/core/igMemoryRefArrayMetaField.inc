igMetaObject *g_igMemoryRefArrayMetaField_metaObject;
igMemoryRefArrayMetaField *g_igMemoryRefArrayMetaField_descriptor;
igMetaField *g_igMemoryRefArrayMetaField_numMetaField;

igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryRefArrayMetaField_EnsureRegistered();
    return g_igMemoryRefArrayMetaField_metaObject;
}

int igMemoryRefArrayMetaField_GetVTable(void) {
    igMemoryRefArrayMetaField obj;
    int vtable;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)&obj);
    obj._vtable = (int)&g_igMemoryRefArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igMemoryRefArrayMetaField_vtable[0];
    igMemoryRefMetaField_Destroy((igMemoryRefMetaField *)&obj, (long long)0);
    return vtable;
}

void igMemoryRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryRefArrayMetaField_Register);
}

static igMetaObjectCallback g_igMemoryRefArrayMetaField_callbackList[] = { igMemoryRefArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igMemoryRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryRefArrayMetaField_metaObject,
        igMemoryRefMetaField_Register,
        (igMetaObjectGetFunction)igMemoryRefMetaField_GetPublishedMetaObject,
        igMemoryRefArrayMetaField_GetMetaObjectFunction,
        "igMemoryRefArrayMetaField",
        0x54,
        igMemoryRefArrayMetaField_GetVTable,
        igMemoryRefArrayMetaField_InitFields,
        0,
        g_igMemoryRefArrayMetaField_callbackList
    );
}

void igMemoryRefArrayMetaField_GetMetaObjectFunction(void) {
    igMemoryRefArrayMetaField_GetMetaObject();
}

int igMemoryRefMetaField_GetPublishedMetaObject(void) {
    return (int)g_igMemoryRefMetaField_metaObject;
}

static FieldFactory g_igMemoryRefArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMemoryRefArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igMemoryRefArrayMetaField_fieldDescriptors[] = {
    &g_igMemoryRefArrayMetaField_numMetaField,
};
static int g_igMemoryRefArrayMetaField_fieldOffsets[] = {
    80,
};

void igMemoryRefArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igMemoryRefArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryRefArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryRefArrayMetaField_fieldTable, g_igMemoryRefArrayMetaField_fieldDescriptors, g_igMemoryRefArrayMetaField_fieldOffsets, base);
}


void igMemoryRefArrayMetaField_CreateDefaultDescriptor(void) {
    igMemoryRefArrayMetaField *descriptor;
    igMemoryRefArrayMetaField *held;
    if (g_igMemoryRefArrayMetaField_descriptor == 0) {
        g_igMemoryRefArrayMetaField_descriptor = ((igMemoryRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igMemoryRefArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igMemoryRefArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igMemoryRefArrayMetaField_descriptor;
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            g_igMemoryRefArrayMetaField_descriptor->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igMemoryRefArrayMetaField_descriptor);
        }
    }
}


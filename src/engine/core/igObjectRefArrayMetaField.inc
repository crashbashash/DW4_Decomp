igMetaObject *g_igObjectRefArrayMetaField_metaObject;
igObjectRefArrayMetaField *g_igObjectRefArrayMetaField_descriptor;
igMetaField *g_igObjectRefArrayMetaField_numMetaField;

void igObjectRefArrayMetaField_Create(int pool) {
    igObjectRefArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance(g_igObjectRefArrayMetaField_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectRefArrayMetaField_EnsureRegistered();
    return g_igObjectRefArrayMetaField_metaObject;
}

int igObjectRefArrayMetaField_GetVTable(void) {
    igObjectRefArrayMetaField o;
    int r;
    int *header;
    int refCount;
    void *text;
    int *nameHeader;
    int nameRefCount;
    void *nameText;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    o._vtable = (int)&g_igObjectRefArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    o._vtable = (int)&g_igObjectRefMetaField_vtable[0];
    if (&o._poolName != 0) {
        text = (char *)o._poolName;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            refCount = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        nameText = (char *)o._fieldName;
        if (nameText != 0) {
            nameHeader = (int *)((char *)nameText - 8);
            nameRefCount = *(int *)((char *)(nameText) - 4) - 1;
            *(int *)((char *)(nameText) - 4) = nameRefCount;
            if (nameRefCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*nameHeader), (int)nameHeader);
            }
        }
    }
    return r;
}

void igObjectRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectRefArrayMetaField_Register);
}

static igMetaObjectCallback g_igObjectRefArrayMetaField_callbackList[] = { igObjectRefArrayMetaField_CreateDefaultDescriptor, 0 };

void igObjectRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igObjectRefArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igObjectRefMetaField_Register,
        igObjectRefMetaField_GetPublishedMetaObject,
        igObjectRefArrayMetaField_GetMetaObjectFunction,
        "igObjectRefArrayMetaField",
        0x48,
        igObjectRefArrayMetaField_GetVTable,
        igObjectRefArrayMetaField_InitFields,
        0,
        g_igObjectRefArrayMetaField_callbackList
    );
}

void igObjectRefArrayMetaField_GetMetaObjectFunction(void) {
    igObjectRefArrayMetaField_GetMetaObject();
}

igMetaObject *igObjectRefMetaField_GetPublishedMetaObject(void) {
    return g_igObjectRefMetaField_metaObject;
}

static FieldFactory g_igObjectRefArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igObjectRefArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igObjectRefArrayMetaField_fieldDescriptors[] = {
    &g_igObjectRefArrayMetaField_numMetaField,
};
static int g_igObjectRefArrayMetaField_fieldOffsets[] = {
    68,
};

void igObjectRefArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igObjectRefArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igObjectRefArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igObjectRefArrayMetaField_fieldTable, g_igObjectRefArrayMetaField_fieldDescriptors, g_igObjectRefArrayMetaField_fieldOffsets, base);
}


void igObjectRefArrayMetaField_CreateDefaultDescriptor(void) {
    igObjectRefArrayMetaField *descriptor;
    igObjectRefArrayMetaField *o;
    int t;

    if (g_igObjectRefArrayMetaField_descriptor == 0) {
        g_igObjectRefArrayMetaField_descriptor = ((igObjectRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igObjectRefArrayMetaField_metaObject, (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igObjectRefArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            o = g_igObjectRefArrayMetaField_descriptor;
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = igMetaField_GetMetaFieldList()->_count - 1;
            g_igObjectRefArrayMetaField_descriptor->_internalIndex = t;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igObjectRefArrayMetaField_descriptor);
        }
    }
}


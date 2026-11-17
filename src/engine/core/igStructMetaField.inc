igMetaObject *g_igStructMetaField_metaObject;
igStructMetaField *g_igStructMetaField_descriptor;
int g_igStructMetaField_sizeDescriptorCell;
igMetaField *g_igStructMetaField_alignmentMetaField;
igMetaField *g_igStructMetaField_cppConstructorMetaField;
igMetaField *g_igStructMetaField_cppDestructorMetaField;

igMetaField *igStructMetaField_Create(igMemoryPoolView *pool) {
    igStructMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igStructMetaField_metaObject, pool);
}

igMetaObject *igStructMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStructMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStructMetaField_EnsureRegistered();
    return g_igStructMetaField_metaObject;
}

int igStructMetaField_GetVTable(void) {
    igStructMetaField o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&g_igStructMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        s = (int *)o._fieldName;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
        }
    }
    return r;
}

void igStructMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStructMetaField_Register);
}

static igMetaObjectCallback g_igStructMetaField_callbackList[] = { igStructMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igStructMetaField_Register(void) {
    CoreLibrary_MarkRegistered();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    return igMetaObject_RegisterClass(
        0,
        &g_igStructMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igStructMetaField_GetMetaObjectFunction,
        "igStructMetaField",
        0x40,
        igStructMetaField_GetVTable,
        igStructMetaField_InitFields,
        0,
        g_igStructMetaField_callbackList
    );
}

void igStructMetaField_GetMetaObjectFunction(void) {
    igStructMetaField_GetMetaObject();
}

static inline void releaseField(igMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}

static FieldFactory g_igStructMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igStructMetaField_fieldTable[] = {
    "_alignment",
    "_cppConstructor",
    "_cppDestructor",
};
static igMetaField **g_igStructMetaField_fieldDescriptors[] = {
    &g_igStructMetaField_alignmentMetaField,
    &g_igStructMetaField_cppConstructorMetaField,
    &g_igStructMetaField_cppDestructorMetaField,
};
static int g_igStructMetaField_fieldOffsets[] = {
    52,
    56,
    60,
};


void igStructMetaField_InitFields(void) {
    igMetaObject *meta = g_igStructMetaField_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    igMetaObject_CreateFields(meta, g_igStructMetaField_ctorTable, 3);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_size));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    igUnsignedShortMetaField_SetDefaultValue((igMetaField *)field, (short)1);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)&g_igStructMetaField_sizeDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base));
    igIntMetaField_SetDefault((igMetaField *)field, 1);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, g_igStructMetaField_fieldTable, g_igStructMetaField_fieldDescriptors, g_igStructMetaField_fieldOffsets, base);
}


void igStructMetaField_CreateDefaultDescriptor(void) {
    igStructMetaField *descriptor;
    igStructMetaField *held;
    int n;

    if (g_igStructMetaField_descriptor == 0) {
        g_igStructMetaField_descriptor = ((igStructMetaField *)igMetaObject_CreateInstance((igMetaObject *)((int)g_igStructMetaField_metaObject), Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igStructMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igStructMetaField_descriptor;
            held->_refCount = (int)((int) (held->_refCount - 1));
            if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
            n = igMetaField_GetMetaFieldList()->_count - 1;
            g_igStructMetaField_descriptor->_internalIndex = n;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igStructMetaField_descriptor);
        }
    }
}


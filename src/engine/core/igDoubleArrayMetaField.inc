igMetaObject *g_igDoubleArrayMetaField_metaObject;
igDoubleArrayMetaField *g_igDoubleArrayMetaField_descriptor;
igMetaField *g_igDoubleArrayMetaField_numMetaField;

igMetaObject *igDoubleArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleArrayMetaField_EnsureRegistered();
    return g_igDoubleArrayMetaField_metaObject;
}

int igDoubleArrayMetaField_GetVTable(void) {
    igDoubleArrayMetaField o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&g_igDoubleArrayMetaField_vtable[0];
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

void igDoubleArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDoubleArrayMetaField_Register);
}

static igMetaObjectCallback g_igDoubleArrayMetaField_callbackList[] = { igDoubleArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igDoubleArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDoubleArrayMetaField_metaObject,
        Gap::Core::igDoubleMetaField::arkRegisterInternal,
        Gap::Core::igDoubleMetaField::getClassMeta,
        igDoubleArrayMetaField_GetMetaObjectFunction,
        "igDoubleArrayMetaField",
        0x38,
        igDoubleArrayMetaField_GetVTable,
        igDoubleArrayMetaField_InitFields,
        0,
        g_igDoubleArrayMetaField_callbackList
    );
}

void igDoubleArrayMetaField_GetMetaObjectFunction(void) {
    igDoubleArrayMetaField_GetMetaObject();
}

static FieldFactory g_igDoubleArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igDoubleArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igDoubleArrayMetaField_fieldDescriptors[] = {
    &g_igDoubleArrayMetaField_numMetaField,
};
static int g_igDoubleArrayMetaField_fieldOffsets[] = {
    52,
};

void igDoubleArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igDoubleArrayMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDoubleArrayMetaField_ctorTable, 1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igDoubleArrayMetaField_fieldTable, g_igDoubleArrayMetaField_fieldDescriptors, g_igDoubleArrayMetaField_fieldOffsets, first);
}


void igDoubleArrayMetaField_CreateDefaultDescriptor(void) {
    igDoubleArrayMetaField *descriptor;
    igDoubleArrayMetaField *p;
    int len;

    if (g_igDoubleArrayMetaField_descriptor == 0) {
        g_igDoubleArrayMetaField_descriptor = ((igDoubleArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igDoubleArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igDoubleArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            p = g_igDoubleArrayMetaField_descriptor;
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = Gap::Core::igMetaField::getMetaFieldTypes()->_count;
            g_igDoubleArrayMetaField_descriptor->_internalIndex = len - 1;
            ((Gap::Core::igMetaField *)g_igDoubleArrayMetaField_descriptor)->validate();
        }
    }
}


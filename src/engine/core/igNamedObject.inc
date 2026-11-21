igMetaObject *g_igNamedObject_metaObject;
igMetaField *g_propertyNameField;

void * igNamedObject_Create(int pool) {
    igNamedObject_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igNamedObject_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igNamedObject_GetOrCreateMetaObject(void) {
    if (g_igNamedObject_metaObject == 0) {
        g_igNamedObject_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNamedObject_metaObject;
}

igMetaObject *igNamedObject_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObject_EnsureRegistered();
    return g_igNamedObject_metaObject;
}

int igNamedObject_GetVTable(void) {
    igNamedObject object;
    int vtable;
    int *ps;
    int *chars;
    int *header;
    int refCount;

    igObject_InitHeader((igObject *)&object);
    ps = &object._name;
    object._vtable = (int)&g_igNamedObject_vtable[0];
    *ps = 0;
    vtable = *(int *)((char *)&object + g_objectSystem->vtableProbeOffset);
    object._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        chars = (int *)*ps;
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

void igNamedObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNamedObject_Register);
}

CallbackArray *igNamedObject_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igNamedObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igNamedObject_GetMetaObjectFunction,
        "igNamedObject",
        0xC,
        igNamedObject_GetVTable,
        igNamedObject_InitFields,
        0,
        0
    );
}

void igNamedObject_GetMetaObjectFunction(void) {
    igNamedObject_GetMetaObject();
}

static FieldFactory g_igNamedObject_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igNamedObject_fieldTable[] = {
    "_name",
};
static igMetaField **g_igNamedObject_fieldDescriptors[] = {
    &g_propertyNameField,
};
static int g_igNamedObject_fieldOffsets[] = {
    8,
};

void igNamedObject_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igNamedObject_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igNamedObject_ctorTable, 1);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)))->setDefault(0);
    igMetaObject_NameFields((igMetaObject *)meta, g_igNamedObject_fieldTable, g_igNamedObject_fieldDescriptors, g_igNamedObject_fieldOffsets, first);
}


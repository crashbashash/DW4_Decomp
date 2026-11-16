static const char *g_locationTypeNames[] = {
    "ABSOLUTE_BASE", "ALCHEMY_BASE", "APPLICATION_BASE",
};
static int g_locationTypeValues[] = {
    0, 1, 2,
};


int igPluginRepository_GetLocationTypeMetaEnum(void) {
    if (g_locationTypeMetaEnum == 0) {
        g_locationTypeMetaEnum = ((int)igMetaEnum_Create((char *)"LOCATION_TYPE", g_locationTypeNames, g_locationTypeValues, 3));
    }
    return g_locationTypeMetaEnum;
}

igMetaObject *g_igPluginRepository_metaObject;
igMetaField *g_igPluginRepository_locationMetaField;
igMetaField *g_igPluginRepository_locationTypeMetaField;

int igPluginRepository_Create(int pool) {
    igPluginRepository_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igPluginRepository_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPluginRepository_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepository_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginRepository_EnsureRegistered();
    return g_igPluginRepository_metaObject;
}

int igPluginRepository_GetVTable(void) {
    igPluginRepository repository;
    int vtable;
    int *location;
    int *name;
    int *text;
    int *header;
    int references;

    igObject_InitHeader((igObject *)&repository);
    name = &repository._name;
    *(int *)name = 0;
    repository._vtable = (int)&g_igPluginRepository_vtable[0];
    location = &repository._location;
    *(int *)location = 0;
    vtable = *(int *)((char *)&repository + g_objectSystem->vtableProbeOffset);
    repository._vtable = (int)&g_igPluginRepository_vtable[0];
    if (location != 0) {
        text = *(int **)location;
        if (text != 0) {
            header = text - 2;
            references = text[-1] - 1;
            text[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    repository._vtable = (int)&g_igNamedObject_vtable[0];
    if (name != 0) {
        text = *(int **)name;
        if (text != 0) {
            header = text - 2;
            references = text[-1] - 1;
            text[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igPluginRepository_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPluginRepository_Register);
}

CallbackArray *igPluginRepository_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPluginRepository_metaObject,
        igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igPluginRepository_GetMetaObjectFunction,
        "igPluginRepository",
        0x14,
        igPluginRepository_GetVTable,
        igPluginRepository_InitFields,
        0,
        0
    );
}

void igPluginRepository_GetMetaObjectFunction(void) {
    igPluginRepository_GetMetaObject();
}

static FieldFactory g_igPluginRepository_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igPluginRepository_fieldTable[] = {
    "_location",
    "_locationType",
};
static igMetaField **g_igPluginRepository_fieldDescriptors[] = {
    &g_igPluginRepository_locationMetaField,
    &g_igPluginRepository_locationTypeMetaField,
};
static int g_igPluginRepository_fieldOffsets[] = {
    12,
    16,
};

void igPluginRepository_InitFields(void) {
    igMetaObject *meta = g_igPluginRepository_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaObject_CreateFields(meta, g_igPluginRepository_ctorTable, 2);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1));
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)igPluginRepository_GetLocationTypeMetaEnum;
    igMetaObject_NameFields(meta, g_igPluginRepository_fieldTable, g_igPluginRepository_fieldDescriptors, g_igPluginRepository_fieldOffsets, base);
}


int igPluginRepository_GetLocationTypeMetaEnum(void) {
    if (g_locationTypeMetaEnum[0] == 0) {
        g_locationTypeMetaEnum[0] = ((int)igMetaEnum_Create((char *)&LOCATION_TYPE[0], (char **)&g_locationTypeNames[0], &g_locationTypeValues[0], 3));
    }
    return g_locationTypeMetaEnum[0];
}

int igPluginRepository_Create(int pool) {
    igPluginRepository_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AF0), (igMemoryPoolView *)pool);
}

igMetaObject *igPluginRepository_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepository_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginRepository_EnsureRegistered();
    return g_igPluginRepository_metaObject[0];
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
    vtable = *(int *)((char *)&repository + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    repository._vtable = (int)&g_igPluginRepository_vtable[0];
    if (location != 0) {
        text = *(int **)location;
        if (text != 0) {
            header = text - 2;
            references = text[-1] - 1;
            text[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
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
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igPluginRepository_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepository_Register);
}

void igPluginRepository_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPluginRepository_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igPluginRepository_GetMetaObjectFunction,
        igPluginRepository_className,
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

void igPluginRepository_InitFields(void) {
    igMetaObject *meta = g_igPluginRepository_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igPluginRepository_ctorTable, 2);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1));
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)igPluginRepository_GetLocationTypeMetaEnum;
    igMetaObject_NameFields(meta, (const char **)g_igPluginRepository_fieldTable, (igMetaField ***)g_igPluginRepository_fieldDescriptors, (int *)g_igPluginRepository_fieldOffsets, base);
}


igMetaObject *g_igExternalInfoEntry_metaObject;
igMetaField *g_igExternalInfoEntry_keyMetaField;
igMetaField *g_igExternalInfoEntry_directoryIndexMetaField;
igMetaField *g_igExternalInfoEntry_infoNameMetaField;

void *igExternalInfoEntry_Create(int pool) {
    igExternalInfoEntry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igExternalInfoEntry_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igExternalInfoEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalInfoEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalInfoEntry_EnsureRegistered();
    return g_igExternalInfoEntry_metaObject;
}

int igExternalInfoEntry_GetVTable(void) {
    igExternalInfoEntry entry;
    int vtable;
    int *p;
    int *q;

    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)&g_igExternalInfoEntry_vtable[0];
    p = &entry._key;
    q = &entry._infoName;
    *p = 0;
    *q = 0;
    vtable = *(int *)((char *)&entry + g_objectSystem->vtableProbeOffset);
    entry._vtable = (int)&g_igExternalInfoEntry_vtable[0];
    igStringRef_Destruct((igStringRef *)q, -1);
    igStringRef_Destruct((igStringRef *)p, -1);
    igDirEntry_Destroy((igDirEntry *)&entry, 0);
    return vtable;
}

void igExternalInfoEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExternalInfoEntry_Register);
}

CallbackArray *igExternalInfoEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igExternalInfoEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalInfoEntry_GetMetaObjectFunction,
        "igExternalInfoEntry",
        0x28,
        igExternalInfoEntry_GetVTable,
        igExternalInfoEntry_InitFields,
        0,
        0
    );
}

void igExternalInfoEntry_GetMetaObjectFunction(void) {
    igExternalInfoEntry_GetMetaObject();
}

static FieldFactory g_igExternalInfoEntry_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igExternalInfoEntry_fieldTable[] = {
    "_key",
    "_directoryIndex",
    "_infoName",
};
static igMetaField **g_igExternalInfoEntry_fieldDescriptors[] = {
    &g_igExternalInfoEntry_keyMetaField,
    &g_igExternalInfoEntry_directoryIndexMetaField,
    &g_igExternalInfoEntry_infoNameMetaField,
};
static int g_igExternalInfoEntry_fieldOffsets[] = {
    28,
    32,
    36,
};

void igExternalInfoEntry_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igExternalInfoEntry_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igExternalInfoEntry_ctorTable, 3);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, first), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1), -1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2), 0);
    igMetaObject_NameFields((igMetaObject *)meta, g_igExternalInfoEntry_fieldTable, g_igExternalInfoEntry_fieldDescriptors, g_igExternalInfoEntry_fieldOffsets, first);
}


igMetaObject *g_igMemoryPoolInfo_metaObject;
igMetaField *g_igMemoryPoolInfo_handleNameMetaField;
igMetaField *g_igMemoryPoolInfo_aliasedToMetaField;
igMetaField *g_igMemoryPoolInfo_sizeMetaField;
igMetaField *g_igMemoryPoolInfo_maxSizeMetaField;
igMetaField *g_igMemoryPoolInfo_addressMetaField;
igMetaField *g_igMemoryPoolInfo_classMetaField;
igMetaField *g_igMemoryPoolInfo_arenaTypeMetaField;
igMetaField *g_igMemoryPoolInfo_sourceMetaField;
igMetaField *g_igMemoryPoolInfo_scopeMetaField;
igMetaField *g_igMemoryPoolInfo_debugOptionsMetaField;
igMetaField *g_igMemoryPoolInfo_releaseOptionsMetaField;
igMetaField *g_igMemoryPoolInfo_debugCheckingMetaField;
igMetaField *g_igMemoryPoolInfo_releaseCheckingMetaField;
igMetaField *g_igMemoryPoolInfo_debugMessagesMetaField;
igMetaField *g_igMemoryPoolInfo_releaseMessagesMetaField;
igMetaField *g_igMemoryPoolInfo_eventTrackerCapacityMetaField;

void * igMemoryPoolInfo_Create(int pool) {
    igMemoryPoolInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMemoryPoolInfo_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMemoryPoolInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolInfo_EnsureRegistered();
    return g_igMemoryPoolInfo_metaObject;
}

int igMemoryPoolInfo_GetVTable(void) {
    igMemoryPoolInfo info;
    int t;
    igObject_InitHeader((igObject *)&info);
    info._name = 0;
    info._vtable = (int)&g_igMemoryPoolInfo_vtable[0];
    info._handleName = 0;
    info._aliasedTo = 0;
    info._class = 0;
    info._arenaType = 0;
    info._source = 0;
    info._scope = 0;
    info._debugOptions = 0;
    info._releaseOptions = 0;
    info._debugChecking = 0;
    info._releaseChecking = 0;
    info._debugMessages = 0;
    info._releaseMessages = 0;
    t = *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
    info._vtable = (int)&g_igMemoryPoolInfo_vtable[0];
    igStringRef_Destruct((igStringRef *)&info._releaseMessages, -1);
    igStringRef_Destruct((igStringRef *)&info._debugMessages, -1);
    igStringRef_Destruct((igStringRef *)&info._releaseChecking, -1);
    igStringRef_Destruct((igStringRef *)&info._debugChecking, -1);
    igStringRef_Destruct((igStringRef *)&info._releaseOptions, -1);
    igStringRef_Destruct((igStringRef *)&info._debugOptions, -1);
    igStringRef_Destruct((igStringRef *)&info._scope, -1);
    igStringRef_Destruct((igStringRef *)&info._source, -1);
    igStringRef_Destruct((igStringRef *)&info._arenaType, -1);
    igStringRef_Destruct((igStringRef *)&info._class, -1);
    igStringRef_Destruct((igStringRef *)&info._aliasedTo, -1);
    igStringRef_Destruct((igStringRef *)&info._handleName, -1);
    igInfo_Destroy((igInfo *)&info, 0);
    return t;
}

void igMemoryPoolInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryPoolInfo_Register);
}

CallbackArray *igMemoryPoolInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryPoolInfo_metaObject,
        igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMemoryPoolInfo_GetMetaObjectFunction,
        "igMemoryPoolInfo",
        0x54,
        igMemoryPoolInfo_GetVTable,
        igMemoryPoolInfo_InitFields,
        0,
        0
    );
}

void igMemoryPoolInfo_GetMetaObjectFunction(void) {
    igMemoryPoolInfo_GetMetaObject();
}

static FieldFactory g_igMemoryPoolInfo_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMemoryPoolInfo_fieldTable[] = {
    "_handleName",
    "_aliasedTo",
    "_size",
    "_maxSize",
    "_address",
    "_class",
    "_arenaType",
    "_source",
    "_scope",
    "_debugOptions",
    "_releaseOptions",
    "_debugChecking",
    "_releaseChecking",
    "_debugMessages",
    "_releaseMessages",
    "_eventTrackerCapacity",
};
static igMetaField **g_igMemoryPoolInfo_fieldDescriptors[] = {
    &g_igMemoryPoolInfo_handleNameMetaField,
    &g_igMemoryPoolInfo_aliasedToMetaField,
    &g_igMemoryPoolInfo_sizeMetaField,
    &g_igMemoryPoolInfo_maxSizeMetaField,
    &g_igMemoryPoolInfo_addressMetaField,
    &g_igMemoryPoolInfo_classMetaField,
    &g_igMemoryPoolInfo_arenaTypeMetaField,
    &g_igMemoryPoolInfo_sourceMetaField,
    &g_igMemoryPoolInfo_scopeMetaField,
    &g_igMemoryPoolInfo_debugOptionsMetaField,
    &g_igMemoryPoolInfo_releaseOptionsMetaField,
    &g_igMemoryPoolInfo_debugCheckingMetaField,
    &g_igMemoryPoolInfo_releaseCheckingMetaField,
    &g_igMemoryPoolInfo_debugMessagesMetaField,
    &g_igMemoryPoolInfo_releaseMessagesMetaField,
    &g_igMemoryPoolInfo_eventTrackerCapacityMetaField,
};
static int g_igMemoryPoolInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
};

void igMemoryPoolInfo_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igMemoryPoolInfo_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryPoolInfo_ctorTable, 0x10);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryPoolInfo_fieldTable, g_igMemoryPoolInfo_fieldDescriptors, g_igMemoryPoolInfo_fieldOffsets, base);
}


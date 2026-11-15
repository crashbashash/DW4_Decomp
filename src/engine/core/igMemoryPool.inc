igMetaObject *g_igMemoryPool_metaObject;
igMetaField *g_igMemoryPool_localAllocatedMetaField;
igMetaField *g_igMemoryPool_localFreedMetaField;
igMetaField *g_igMemoryPool_localNetAllocatedMetaField;
igMetaField *g_igMemoryPool_localNetAllocatedHighMetaField;
igMetaField *g_igMemoryPool_localAllocatedWithOverheadMetaField;
igMetaField *g_igMemoryPool_localFreedWithOverheadMetaField;
igMetaField *g_igMemoryPool_localNetAllocatedWithOverheadMetaField;
igMetaField *g_igMemoryPool_localNetAllocatedWithOverheadHighMetaField;
igMetaField *g_igMemoryPool_localAllocationCountMetaField;
igMetaField *g_igMemoryPool_localFreeCountMetaField;
igMetaField *g_igMemoryPool_localNetAllocationCountMetaField;
igMetaField *g_igMemoryPool_localNetAllocationCountHighMetaField;
igMetaField *g_igMemoryPool_updateStatisticsMetaField;
igMetaField *g_igMemoryPool_updateGlobalStatisticsMetaField;

igMetaObject *igMemoryPool_GetOrCreateMetaObject(void) {
    if (g_igMemoryPool_metaObject == 0) {
        g_igMemoryPool_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMemoryPool_metaObject;
}

igMetaObject *igMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPool_EnsureRegistered();
    return g_igMemoryPool_metaObject;
}

void igMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPool_Register);
}

void igMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        1,
        &g_igMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMemoryPool_GetMetaObjectFunction,
        "igMemoryPool",
        0x70,
        0,
        igMemoryPool_InitFields,
        0,
        0
    );
}

void igMemoryPool_GetMetaObjectFunction(void) {
    igMemoryPool_GetMetaObject();
}

static FieldFactory g_igMemoryPool_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igMemoryPool_fieldTable[] = {
    "_localAllocated",
    "_localFreed",
    "_localNetAllocated",
    "_localNetAllocatedHigh",
    "_localAllocatedWithOverhead",
    "_localFreedWithOverhead",
    "_localNetAllocatedWithOverhead",
    "_localNetAllocatedWithOverheadHigh",
    "_localAllocationCount",
    "_localFreeCount",
    "_localNetAllocationCount",
    "_localNetAllocationCountHigh",
    "_updateStatistics",
    "_updateGlobalStatistics",
};
static igMetaField **g_igMemoryPool_fieldDescriptors[] = {
    &g_igMemoryPool_localAllocatedMetaField,
    &g_igMemoryPool_localFreedMetaField,
    &g_igMemoryPool_localNetAllocatedMetaField,
    &g_igMemoryPool_localNetAllocatedHighMetaField,
    &g_igMemoryPool_localAllocatedWithOverheadMetaField,
    &g_igMemoryPool_localFreedWithOverheadMetaField,
    &g_igMemoryPool_localNetAllocatedWithOverheadMetaField,
    &g_igMemoryPool_localNetAllocatedWithOverheadHighMetaField,
    &g_igMemoryPool_localAllocationCountMetaField,
    &g_igMemoryPool_localFreeCountMetaField,
    &g_igMemoryPool_localNetAllocationCountMetaField,
    &g_igMemoryPool_localNetAllocationCountHighMetaField,
    &g_igMemoryPool_updateStatisticsMetaField,
    &g_igMemoryPool_updateGlobalStatisticsMetaField,
};
static int g_igMemoryPool_fieldOffsets[] = {
    8,
    16,
    24,
    32,
    40,
    48,
    56,
    64,
    72,
    80,
    88,
    96,
    104,
    105,
};

void igMemoryPool_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)((void *)g_igMemoryPool_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryPool_ctorTable, 0xE);
    igBoolMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)), 1);
    igBoolMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryPool_fieldTable, g_igMemoryPool_fieldDescriptors, g_igMemoryPool_fieldOffsets, base);
    *(int *)((char *)((void *)g_igMemoryPool_metaObject) + 60) = (int)igArenaMemoryPool_GetMetaObjectFunction;
}


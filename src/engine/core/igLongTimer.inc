igMetaObject *g_igLongTimer_metaObject;
igMetaField *g_igLongTimer_startTimeMetaField;
igMetaField *g_igLongTimer_additionalTimeMetaField;
igMetaField *g_igLongTimer_resetTimeMetaField;
igMetaField *g_igLongTimer_isStoppedMetaField;

igMetaObject *igLongTimer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igLongTimer_metaObject != 0) {
        ready = (g_igLongTimer_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igLongTimer_EnsureRegistered();
done:
    return g_igLongTimer_metaObject;
}

void igLongTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLongTimer_Register);
}

CallbackArray *igLongTimer_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igLongTimer_metaObject,
        igTimer_Register,
        igTimer_GetPublishedMetaObject,
        igLongTimer_GetMetaObjectFunction,
        "igLongTimer",
        0x28,
        0,
        igLongTimer_InitFields,
        0,
        0
    );
}

igMetaObject *igTimer_GetPublishedMetaObject(void) {
    return g_igTimer_metaObject;
}

static FieldFactory g_igLongTimer_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igLongTimer_fieldTable[] = {
    "_startTime",
    "_additionalTime",
    "_resetTime",
    "_isStopped",
};
static igMetaField **g_igLongTimer_fieldDescriptors[] = {
    &g_igLongTimer_startTimeMetaField,
    &g_igLongTimer_additionalTimeMetaField,
    &g_igLongTimer_resetTimeMetaField,
    &g_igLongTimer_isStoppedMetaField,
};
static int g_igLongTimer_fieldOffsets[] = {
    8,
    16,
    24,
    32,
};

void igLongTimer_InitFields(void) {
    int base;
    void *meta;
    meta = (void *)((void *)g_igLongTimer_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igLongTimer_ctorTable, 4);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igLongTimer_fieldTable, g_igLongTimer_fieldDescriptors, g_igLongTimer_fieldOffsets, base);
    *(int *)((char *)((void *)g_igLongTimer_metaObject) + 60) = (int)igPsx2LongTimer_GetMetaObjectFunction;
}

